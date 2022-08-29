#include <vector>

#include "entities/Code.h"
#include "entities/Coordinates.h"
#include "entities/TimeUTC.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/DistressNature.h"
#include "structure/Phasing.h"
#include "distress/DistressRelay.h"
#include "distress/DistressRelayRq.h"
#include "distress/DistressRelayAck.h"
#include "routine/RoutineIndividual.h"
#include "routine/RoutineIndividualAck.h"
#include "urgency/UrgencyIndividual.h"
#include "urgency/UrgencyIndividualAck.h"
#include "safety/SafetyIndividual.h"
#include "safety/SafetyIndividualAck.h"
#include "structure/Phasing.h"
#include "safety/SafetyAllShips.h"
#include "urgency/UrgencyAllShips.h"
#include "decoder/CodesDecoder.h"
#include "DigitalSelectiveCall.h"
#include "decoder/IndividualDecoder.h"

DigitalSelectiveCall *IndividualDecoder::decodeCodes(std::vector<Code> codes)
{
	Mmsi address = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 2, codes.begin() + 7));
	Category category = Category::fromSymbol(codes[7].getSymbol());
	Mmsi selfId = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 8, codes.begin() + 13));

	int catSym = category.getCode().getSymbol();

	if (catSym == Category::Symbol_SAFETY || catSym == Category::Symbol_URGENCY) {
		return decodeUrgOrSafety(codes, address, category, selfId);
	}
	else if (catSym == Category::Symbol_DISTRESS) {
		return decodeDistressRelay(codes, address, selfId);
	}

	return decodeRoutine(codes, address, selfId);
}

bool IndividualDecoder::isMatches(Code code)
{
	return (code.getSymbol() == FormatSpecifier::Symbol_INDIVIDUAL);
}

DigitalSelectiveCall *IndividualDecoder::decodeDistressRelay(std::vector<Code> codes,
	Mmsi address,
	Mmsi selfId)
{
	Mmsi distressMmsi = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 14, codes.begin() + 19));
	DistressNature nature = DistressNature::fromSymbol(codes[19].getSymbol());
	Coordinates coordinates = Coordinates::fromCodes(std::vector<Code>(codes.begin() + 20, codes.begin() + 25));
	TimeUTC time = TimeUTC::fromCodes(std::vector<Code>(codes.begin() + 25, codes.begin() + 27));
	FirstTelecommand subsequentTelecommunications = FirstTelecommand::fromSymbol(codes[27].getSymbol());
	Phasing eos = getEos(codes);

	FormatSpecifier allShipsSpec = FormatSpecifier(Code(FormatSpecifier::Symbol_ALL_SHIPS));

	if (isExpanded(codes)) {
		ExpansionPosition expPos = ExpansionPosition::fromCodes(std::vector<Code>(codes.begin() + 31, codes.begin() + 35));
		switch (eos.getCode().getSymbol()) {
		case Phasing::Symbol_EOS:
			return new DistressRelay(allShipsSpec, selfId, distressMmsi,
				nature, coordinates, time, subsequentTelecommunications, expPos);
		case Phasing::Symbol_EOS_ACK_RQ:
			return new DistressRelayRq(allShipsSpec, selfId, distressMmsi,
				nature, coordinates, time, subsequentTelecommunications, expPos);
		case Phasing::Symbol_EOS_ACK_BQ:
			return new DistressRelayAck(allShipsSpec, selfId, distressMmsi,
				nature, coordinates, time, subsequentTelecommunications, expPos);
		default:
			printf("Unknown EOS! %d\n", eos.getCode().getSymbol());
			abort();
			break;
		}
	}

	switch (eos.getCode().getSymbol()) {
	case Phasing::Symbol_EOS:
		return new DistressRelay(allShipsSpec, selfId, distressMmsi,
			nature, coordinates, time, subsequentTelecommunications);
	case Phasing::Symbol_EOS_ACK_RQ:
		return new DistressRelayRq(allShipsSpec, selfId, distressMmsi,
			nature, coordinates, time, subsequentTelecommunications);
	case Phasing::Symbol_EOS_ACK_BQ:
		return new DistressRelayAck(allShipsSpec, selfId, distressMmsi,
			nature, coordinates, time, subsequentTelecommunications);
	default:
		printf("Unknown EOS! %d\n", eos.getCode().getSymbol());
		abort();
		break;
	}

	return new DistressRelay(allShipsSpec, selfId, distressMmsi,
		nature, coordinates, time, subsequentTelecommunications);
}

DigitalSelectiveCall *IndividualDecoder::decodeRoutine(std::vector<Code> codes,
	Mmsi addr,
	Mmsi id)
{
	FirstTelecommand ft = FirstTelecommand::fromSymbol(codes[13].getSymbol());

	SecondTelecommand st = SecondTelecommand::fromSymbol(codes[14].getSymbol());

	Phasing eos = getEos(codes);
	int eosSymbol = eos.getCode().getSymbol();

	if (isPosMarker(codes[15])) {
		Coordinates pos = Coordinates::fromCodes(std::vector<Code>(codes.begin() + 16, codes.begin() + 21));
		if (eosSymbol == Phasing::Symbol_EOS_ACK_RQ) {
			return new RoutineIndividual(id, addr, ft, st, pos);
		}
		else {
			return new RoutineIndividualAck(id, addr, ft, st, pos);
		}
	}
	else {
		Frequency freqRx = Frequency::fromCodes(std::vector<Code>(codes.begin() + 15, codes.begin() + 18));

		if (hasFrequency(std::vector<Code>(codes.begin() + 18, codes.begin() + 21))) {
			Frequency freqTx = Frequency::fromCodes(std::vector<Code>(codes.begin() + 18, codes.begin() + 21));
			if (eosSymbol == Phasing::Symbol_EOS_ACK_RQ) {
				return new RoutineIndividual(id, addr, ft, st, freqRx, freqTx);
			}
			else {
				return new RoutineIndividualAck(id, addr, ft, st, freqRx, freqTx);
			}
		}

		if (eosSymbol == Phasing::Symbol_EOS_ACK_RQ) {
			return new RoutineIndividual(id, addr, ft, st, freqRx);
		}
		else {
			return new RoutineIndividualAck(id, addr, ft, st, freqRx);
		}
	}

	return new RoutineIndividualAck(id, addr, ft, st, Frequency(0));
}

DigitalSelectiveCall *IndividualDecoder::decodeUrgOrSafety(std::vector<Code> codes,
	Mmsi address,
	Category cat,
	Mmsi selfId)
{
	FirstTelecommand ft = FirstTelecommand::fromSymbol(codes[13].getSymbol());

	SecondTelecommand st = SecondTelecommand::fromSymbol(codes[14].getSymbol());

	Coordinates pos;
	TimeUTC time;
	Frequency freqRx;
	Frequency freqTx;
	Phasing eos = getEos(codes);
	int eosSym = eos.getCode().getSymbol();

	if (isPosMarker(codes[15])) {
		pos = Coordinates::fromCodes(std::vector<Code>(codes.begin() + 16, codes.begin() + 21));

		bool withTime = std::vector<Code>(codes.begin() + 21, codes.begin() + codes.size()).size() > 2;
		if (withTime) {
			time = TimeUTC::fromCodes(std::vector<Code>(codes.begin() + 21, codes.begin() + 23));
		}
	}
	else {
		freqRx = Frequency::fromCodes(std::vector<Code>(codes.begin() + 15, codes.begin() + 18));

		if (hasFrequency(std::vector<Code>(codes.begin() + 15, codes.begin() + 21))) {
			freqTx = Frequency::fromCodes(std::vector<Code>(codes.begin() + 18, codes.begin() + 21));
		}
	}

	switch (cat.getCode().getSymbol()) {
	case Category::Symbol_URGENCY:
		if (eosSym == Phasing::Symbol_EOS_ACK_RQ) {
			return new UrgencyIndividual(selfId, address, ft, st, freqRx, freqTx, pos, time);
		}
		else {
			return new UrgencyIndividualAck(selfId, address, ft, st, freqRx, freqTx, pos, time);
		}
	case Category::Symbol_SAFETY:
		if (eosSym == Phasing::Symbol_EOS_ACK_RQ) {
			return new SafetyIndividual(selfId, address, ft, st, freqRx, freqTx, pos, time);
		}
		else {
			return new SafetyIndividualAck(selfId, address, ft, st, freqRx, freqTx, pos, time);
		}
	default:
		printf("Unknown category %d\n", cat.getCode().getSymbol());
		abort();
		break;
	}
}