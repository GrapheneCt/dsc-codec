#pragma once

#include "entities/Frequency.h"
#include "entities/Mmsi.h"
#include "IndividualCall.h"

/** @author AlexeyVorobyev */
class SafetyIndividual : public IndividualCall
{
public:

	SafetyIndividual(Mmsi selfId, Mmsi address,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Frequency frequencyRx = Frequency(0),
		Frequency frequencyTx = Frequency(0),
		Coordinates coordinates = Coordinates(),
		TimeUTC time = TimeUTC());

	std::string toString();
};