#pragma once

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "IndividualCall.h"

/** @author AlexeyVorobyev */
class RoutineIndividual : public IndividualCall
{
public:

	RoutineIndividual(Mmsi selfId, Mmsi address,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Coordinates coordinates);

	RoutineIndividual(Mmsi selfId, Mmsi address,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Frequency frequencyRx);

	RoutineIndividual(Mmsi selfId, Mmsi address,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Frequency frequencyRx,
		Frequency frequencyTx);

	RoutineIndividual(Mmsi selfId, Mmsi address,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Frequency frequencyRx,
		Frequency frequencyTx,
		Coordinates coordinates);

	std::string toString();
};