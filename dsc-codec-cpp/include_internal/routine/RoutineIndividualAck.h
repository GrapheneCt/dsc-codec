#pragma once

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "IndividualCall.h"

/** @author AlexeyVorobyev */
class RoutineIndividualAck : public IndividualCall
{
public:

	RoutineIndividualAck(Mmsi selfId, Mmsi address,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Frequency frequencyRx);

	RoutineIndividualAck(Mmsi selfId, Mmsi address,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Frequency frequencyRx,
		Frequency frequencyTx);

	RoutineIndividualAck(Mmsi selfId, Mmsi address,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Coordinates coordinates);

	RoutineIndividualAck(Mmsi selfId, Mmsi address,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Frequency frequencyRx,
		Frequency frequencyTx,
		Coordinates coordinates);

	std::string toString();
};