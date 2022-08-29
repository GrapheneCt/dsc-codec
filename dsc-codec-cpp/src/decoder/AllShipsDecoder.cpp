#include <vector>
#include <string>

#include "entities/Code.h"
#include "entities/Coordinates.h"
#include "entities/TimeUTC.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/DistressNature.h"
#include "structure/Phasing.h"
#include "distress/DistressAck.h"
#include "distress/DistressRelay.h"
#include "distress/DistressRelayAck.h"
#include "distress/DistressRelayRq.h"
#include "structure/Phasing.h"
#include "safety/SafetyAllShips.h"
#include "urgency/UrgencyAllShips.h"
#include "DigitalSelectiveCall.h"
#include "decoder/CodesDecoder.h"
#include "decoder/AllShipsDecoder.h"

DigitalSelectiveCall *AllShipsDecoder::decodeCodes(std::vector<Code> codes)
{
	int symbol = codes[2].getSymbol();
	if (symbol == Category::Symbol_SAFETY || symbol == Category::Symbol_URGENCY) {
		return decodeSafetyOrUrgency(codes, Category::fromSymbol(symbol));
	}

	return decodeDistress(codes);
}

bool AllShipsDecoder::isMatches(Code code)
{
	return (code.getSymbol() == FormatSpecifier::Symbol_ALL_SHIPS);
}

DigitalSelectiveCall *AllShipsDecoder::decodeDistress(std::vector<Code> codes)
{
	// Телекомманда должна быть обязательно связана с бедствием
	int symbol = codes[8].getSymbol();
	if (symbol == FirstTelecommand::Symbol_DISTRESS_ACK)
		return decodeDistressAck(codes);
	else if (symbol == FirstTelecommand::Symbol_DISTRESS_RELAY)
		return decodeDistressRelay(codes);

	printf("Invalid first telecommand!\n");
	abort();

	return decodeDistressRelay(codes);
}

/** Decodes retranslation of distress (with acknowledge) */
DigitalSelectiveCall *AllShipsDecoder::decodeDistressRelay(std::vector<Code> codes)
{
	Mmsi selfId = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 3, codes.begin() + 8));
	Mmsi distressMmsi = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 9, codes.begin() + 14));
	DistressNature nature = DistressNature::fromSymbol(codes[14].getSymbol());
	Coordinates coordinates = Coordinates::fromCodes(std::vector<Code>(codes.begin() + 15, codes.begin() + 20));
	TimeUTC time = TimeUTC::fromCodes(std::vector<Code>(codes.begin() + 20, codes.begin() + 22));
	FirstTelecommand subsequentTelecommunications = FirstTelecommand::fromSymbol(codes[22].getSymbol());
	Phasing eos = getEos(codes);

	bool expanded = isExpanded(codes);

	switch (eos.getCode().getSymbol()) {
	case Phasing::Symbol_EOS:
		if (expanded) {
			return new DistressRelay(FormatSpecifier(Code(FormatSpecifier::Symbol_ALL_SHIPS)),
				selfId, distressMmsi, nature, coordinates, time, subsequentTelecommunications,
				ExpansionPosition::fromCodes(std::vector<Code>(codes.begin() + 26, codes.begin() + 30)));
		}
		else {
			return new DistressRelay(FormatSpecifier(Code(FormatSpecifier::Symbol_ALL_SHIPS)),
				selfId, distressMmsi, nature, coordinates, time, subsequentTelecommunications);
		}
	case Phasing::Symbol_EOS_ACK_RQ:
		if (expanded) {
			return new DistressRelayRq(FormatSpecifier(Code(FormatSpecifier::Symbol_ALL_SHIPS)),
				selfId, distressMmsi, nature, coordinates, time, subsequentTelecommunications,
				ExpansionPosition::fromCodes(std::vector<Code>(codes.begin() + 26, codes.begin() + 30)));
		}
		else {
			return new DistressRelayRq(FormatSpecifier(Code(FormatSpecifier::Symbol_ALL_SHIPS)),
				selfId, distressMmsi, nature, coordinates, time, subsequentTelecommunications);
		}
	case Phasing::Symbol_EOS_ACK_BQ:
		if (expanded) {
			return new DistressRelayAck(FormatSpecifier(Code(FormatSpecifier::Symbol_ALL_SHIPS)),
				selfId, distressMmsi, nature, coordinates, time, subsequentTelecommunications,
				ExpansionPosition::fromCodes(std::vector<Code>(codes.begin() + 26, codes.begin() + 30)));
		}
		else {
			return new DistressRelayAck(FormatSpecifier(Code(FormatSpecifier::Symbol_ALL_SHIPS)),
				selfId, distressMmsi, nature, coordinates, time, subsequentTelecommunications);
		}
	default:
		printf("Unknown EOS! %d\n", eos.getCode().getSymbol());
		abort();
		break;
	}

	return new DistressRelayAck(FormatSpecifier(Code(FormatSpecifier::Symbol_ALL_SHIPS)),
		selfId, distressMmsi, nature, coordinates, time, subsequentTelecommunications);
}

/** Decodes distress acknowledge */
DigitalSelectiveCall *AllShipsDecoder::decodeDistressAck(std::vector<Code> codes)
{
	Mmsi selfId = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 3, codes.begin() + 8));
	Mmsi distressMmsi = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 9, codes.begin() + 14));
	DistressNature nature = DistressNature::fromSymbol(codes[14].getSymbol());
	Coordinates distressCoordinates = Coordinates::fromCodes(std::vector<Code>(codes.begin() + 15, codes.begin() + 20));
	TimeUTC time = TimeUTC::fromCodes(std::vector<Code>(codes.begin() + 20, codes.begin() + 22));
	FirstTelecommand subsequentCommunications = FirstTelecommand::fromSymbol(codes[22].getSymbol());

	bool expanded = isExpanded(codes);

	if (expanded) {
		return new DistressAck(
			selfId, distressMmsi, nature,
			distressCoordinates, time, subsequentCommunications,
			ExpansionPosition::fromCodes(std::vector<Code>(codes.begin() + 26, codes.begin() + 30)));
	}

	return new DistressAck(selfId, distressMmsi, nature,
		distressCoordinates, time, subsequentCommunications);
}

/** Decodes "Safety" and "Urgency" calls */
DigitalSelectiveCall *AllShipsDecoder::decodeSafetyOrUrgency(std::vector<Code> codes, Category category)
{
	Mmsi selfId = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 3, codes.begin() + 8));
	FirstTelecommand ft = FirstTelecommand::fromSymbol(codes[8].getSymbol());
	SecondTelecommand st = SecondTelecommand::fromSymbol(codes[9].getSymbol());
	Frequency rxFreq = Frequency::fromCodes(std::vector<Code>(codes.begin() + 10, codes.begin() + 13));

	bool hasTxFreq = hasFrequency(std::vector<Code>(codes.begin() + 13, codes.begin() + 16));

	if (hasTxFreq) {
		Frequency txFreq = Frequency::fromCodes(std::vector<Code>(codes.begin() + 13, codes.begin() + 16));
		if (category.getCode().getSymbol() == Category::Symbol_SAFETY)
			return new SafetyAllShips(selfId, ft, st, rxFreq, txFreq);

		return new UrgencyAllShips(selfId, ft, st, rxFreq, txFreq);
	}

	if (category.getCode().getSymbol() == Category::Symbol_SAFETY)
		return new SafetyAllShips(selfId, ft, st, rxFreq);

	return new UrgencyAllShips(selfId, ft, st, rxFreq);
}