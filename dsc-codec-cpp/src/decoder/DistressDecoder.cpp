#include <vector>

#include "entities/Code.h"
#include "entities/Coordinates.h"
#include "entities/TimeUTC.h"
#include "structure/FirstTelecommand.h"
#include "distress/Distress.h"
#include "safety/SafetyAllShips.h"
#include "urgency/UrgencyAllShips.h"
#include "decoder/CodesDecoder.h"
#include "DigitalSelectiveCall.h"
#include "decoder/DistressDecoder.h"

DigitalSelectiveCall *DistressDecoder::decodeCodes(std::vector<Code> codes)
{
	Mmsi selfMmsi = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 2, codes.begin() + 7));

	DistressNature nature = DistressNature::fromSymbol(codes[7].getSymbol());
	Coordinates coordinates = Coordinates::fromCodes(std::vector<Code>(codes.begin() + 8, codes.begin() + 13));
	TimeUTC timeUTC = TimeUTC::fromCodes(std::vector<Code>(codes.begin() + 13, codes.begin() + 15));
	FirstTelecommand subsequentTransmissions = FirstTelecommand::fromSymbol(codes[15].getSymbol());

	if (isExpanded(codes)) {
		ExpansionPosition expansionPosition = ExpansionPosition::fromCodes(std::vector<Code>(codes.begin() + 19, codes.begin() + 23));
		return new Distress(selfMmsi, nature, coordinates, timeUTC, subsequentTransmissions, expansionPosition);
	}

	return new Distress(selfMmsi, nature, coordinates, timeUTC, subsequentTransmissions);
}

bool DistressDecoder::isMatches(Code code)
{
	return (code.getSymbol() == FormatSpecifier::Symbol_DISTRESS);
}