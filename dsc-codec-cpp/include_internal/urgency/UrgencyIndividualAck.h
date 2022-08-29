#pragma once

#include "entities/Mmsi.h"
#include "entities/Frequency.h"
#include "DigitalSelectiveCall.h"
#include "IndividualCall.h"

/** @author AlexeyVorobyev */
class UrgencyIndividualAck : public IndividualCall
{
public:

	UrgencyIndividualAck(Mmsi selfId, Mmsi address,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Frequency frequencyRx = Frequency(0),
		Frequency frequencyTx = Frequency(0),
		Coordinates coordinates = Coordinates(),
		TimeUTC time = TimeUTC());

	std::string toString();
};