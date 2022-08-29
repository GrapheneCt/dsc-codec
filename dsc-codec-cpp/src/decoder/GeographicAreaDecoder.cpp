#include <vector>

#include "entities/Code.h"
#include "entities/Coordinates.h"
#include "entities/TimeUTC.h"
#include "entities/Area.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/DistressNature.h"
#include "structure/Phasing.h"
#include "safety/SafetyGeographicArea.h"
#include "urgency/UrgencyGeographicArea.h"
#include "distress/DistressAck.h"
#include "distress/DistressRelay.h"
#include "distress/DistressRelayAck.h"
#include "distress/DistressRelayRq.h"
#include "structure/Phasing.h"
#include "safety/SafetyAllShips.h"
#include "urgency/UrgencyAllShips.h"
#include "decoder/CodesDecoder.h"
#include "decoder/GeographicAreaDecoder.h"
#include "DigitalSelectiveCall.h"

DigitalSelectiveCall *GeographicAreaDecoder::decodeCodes(std::vector<Code> codes)
{
	Area area = Area::fromCodes(std::vector<Code>(codes.begin() + 2, codes.begin() + 7));
	Category category = Category::fromSymbol(codes[7].getSymbol());
	Mmsi selfId = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 8, codes.begin() + 13));

	int catSym = category.getCode().getSymbol();

	if (catSym == Category::Symbol_SAFETY || catSym == Category::Symbol_URGENCY) {
		return decodeSafetyOrUrgency(selfId, area, category, codes);
	}

	return decodeDistressRelay(selfId, area, codes);
}

DigitalSelectiveCall *GeographicAreaDecoder::decodeSafetyOrUrgency(
	Mmsi selfId,
	Area area,
	Category category,
	std::vector<Code> codes)
{
	FirstTelecommand ft = FirstTelecommand::fromSymbol(codes[13].getSymbol());
	SecondTelecommand st = SecondTelecommand::fromSymbol(codes[14].getSymbol());
	Frequency freqRx = Frequency::fromCodes(std::vector<Code>(codes.begin() + 15, codes.begin() + 18));

	int catSym = category.getCode().getSymbol();

	if (hasFrequency(std::vector<Code>(codes.begin() + 18, codes.begin() + 21))) {
		Frequency freqTx = Frequency::fromCodes(std::vector<Code>(codes.begin() + 18, codes.begin() + 21));
		if (catSym == Category::Symbol_SAFETY) {
			return new SafetyGeographicArea(selfId, area, ft, st, freqRx, freqTx);
		}
		else {
			return new UrgencyGeographicArea(selfId, area, ft, st, freqRx, freqTx);
		}
	}

	if (catSym == Category::Symbol_SAFETY) {
		return new SafetyGeographicArea(selfId, area, ft, st, freqRx);
	}

	return new UrgencyGeographicArea(selfId, area, ft, st, freqRx);
}

DigitalSelectiveCall *GeographicAreaDecoder::decodeDistressRelay(Mmsi selfId, Area area, std::vector<Code> codes)
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

bool GeographicAreaDecoder::isMatches(Code code)
{
	return (code.getSymbol() == FormatSpecifier::Symbol_GEOGRAPHICAL_AREA);
}