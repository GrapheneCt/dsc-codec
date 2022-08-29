#pragma once

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "DigitalSelectiveCall.h"

/** @author AlexeyVorobyev */
class RoutineGroup : public DigitalSelectiveCall
{
public:

	RoutineGroup(Mmsi selfId, Mmsi address,
		FirstTelecommand firstTelecommand,
		Frequency frequencyRx,
		Frequency frequencyTx = Frequency(0));

	std::vector<Code> toCodes();

	Mmsi getAddress();
	Category getCategory();
	FirstTelecommand getFirstTelecommand();
	SecondTelecommand getSecondTelecommand();
	Frequency getFrequencyRx();
	Frequency getFrequencyTx();

	std::string toString();

private:

	Category category;
	SecondTelecommand secondTelecommand;
	Mmsi address;
	FirstTelecommand firstTelecommand;
	Frequency frequencyRx;
	Frequency frequencyTx;
	bool hasFrequencyTx;
};