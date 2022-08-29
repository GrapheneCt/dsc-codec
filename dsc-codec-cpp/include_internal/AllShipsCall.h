#pragma once

#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "entities/PstnNumber.h"
#include "entities/Frequency.h"
#include "DigitalSelectiveCall.h"

/**
 * "All ships" type of call.
 *
 * Used for "Safety" and "Urgency" calls.
 *
 * @author AlexeyVorobyev
 */
class AllShipsCall : public DigitalSelectiveCall
{
public:

	AllShipsCall(Mmsi selfId, Category category,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Frequency frequencyRx,
		Frequency frequencyTx = Frequency(0));

	std::vector<Code> toCodes();

	Category getCategory();
	FirstTelecommand getFirstTelecommand();
	SecondTelecommand getSecondTelecommand();
	Frequency getFrequencyRx();
	Frequency getFrequencyTx();
	bool getHasFrequencyTx();

private:

	Category category;
	FirstTelecommand firstTelecommand;
	SecondTelecommand secondTelecommand;
	Frequency frequencyRx;
	Frequency frequencyTx;
	bool hasFrequencyTx;
};