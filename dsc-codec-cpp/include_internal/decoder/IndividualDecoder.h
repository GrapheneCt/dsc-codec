#pragma once

#include "entities/Code.h"
#include "entities/Coordinates.h"
#include "entities/TimeUTC.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/DistressNature.h"
#include "structure/Phasing.h"
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

/**
 * Decoder for "Individual" DSCs.
 *
 * @author AlexeyVorobyev
 */
class IndividualDecoder : public CodesDecoder
{
	DigitalSelectiveCall *decodeCodes(std::vector<Code> codes);

	bool isMatches(Code code);

private:

	DigitalSelectiveCall *decodeDistressRelay(std::vector<Code> codes,
		Mmsi address,
		Mmsi selfId);

	DigitalSelectiveCall *decodeRoutine(std::vector<Code> codes,
		Mmsi addr,
		Mmsi id);

	DigitalSelectiveCall *decodeUrgOrSafety(std::vector<Code> codes,
		Mmsi address,
		Category cat,
		Mmsi selfId);
};