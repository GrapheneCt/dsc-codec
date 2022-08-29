#pragma once

#include "entities/Code.h"
#include "entities/Coordinates.h"
#include "entities/TimeUTC.h"
#include "entities/DscNumber.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/DistressNature.h"
#include "structure/Phasing.h"
#include "routine/RoutineGroup.h"
#include "semiAuto/SemiAutoVhf.h"
#include "semiAuto/SemiAutoVhfAck.h"
#include "semiAuto/SemiAutoMfHf.h"
#include "semiAuto/SemiAutoMfHfAck.h"
#include "structure/Phasing.h"
#include "safety/SafetyAllShips.h"
#include "urgency/UrgencyAllShips.h"
#include "decoder/CodesDecoder.h"
#include "DigitalSelectiveCall.h"

/**
 * Decoder of "Semi-auto" DSCs.
 *
 * @author AlexeyVorobyev
 */
class SemiAutoDecoder : public CodesDecoder
{
	DigitalSelectiveCall *decodeCodes(std::vector<Code> codes);

	bool isMatches(Code code);
};