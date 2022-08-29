#pragma once

#include "entities/Code.h"
#include "entities/Coordinates.h"
#include "entities/TimeUTC.h"
#include "structure/FirstTelecommand.h"
#include "distress/Distress.h"
#include "safety/SafetyAllShips.h"
#include "urgency/UrgencyAllShips.h"
#include "decoder/CodesDecoder.h"
#include "DigitalSelectiveCall.h"

/**
 * Decoder of "Distress" messages.
 *
 * @author AlexeyVorobyev
 */
class DistressDecoder : public CodesDecoder
{
	DigitalSelectiveCall *decodeCodes(std::vector<Code> codes);

	bool isMatches(Code code);
};
