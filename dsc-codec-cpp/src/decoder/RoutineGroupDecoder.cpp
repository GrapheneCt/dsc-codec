#include <vector>

#include "entities/Code.h"
#include "entities/Coordinates.h"
#include "entities/TimeUTC.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/DistressNature.h"
#include "structure/Phasing.h"
#include "routine/RoutineGroup.h"
#include "structure/Phasing.h"
#include "safety/SafetyAllShips.h"
#include "urgency/UrgencyAllShips.h"
#include "decoder/CodesDecoder.h"
#include "DigitalSelectiveCall.h"
#include "decoder/RoutineGroupDecoder.h"

DigitalSelectiveCall *RoutineGroupDecoder::decodeCodes(std::vector<Code> codes)
{
	Mmsi address = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 2, codes.begin() + 7));
	Mmsi selfId = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 8, codes.begin() + 13));
	FirstTelecommand firstTelecommand = FirstTelecommand::fromSymbol(codes[13].getSymbol());
	Frequency freqRx = Frequency::fromCodes(std::vector<Code>(codes.begin() + 15, codes.begin() + 18));
	Frequency freqTx = Frequency::fromCodes(std::vector<Code>(codes.begin() + 15, codes.begin() + 21));

	return new RoutineGroup(selfId, address, firstTelecommand, freqRx, freqTx);
}

bool RoutineGroupDecoder::isMatches(Code code)
{
	return (code.getSymbol() == FormatSpecifier::Symbol_COMMON_INTEREST);
}