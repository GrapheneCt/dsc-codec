#pragma once

#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "entities/PstnNumber.h"
#include "entities/Frequency.h"
#include "entities/Area.h"
#include "DigitalSelectiveCall.h"

/**
 * Geographical area calls.
 *
 * @author AlexeyVorobyev
 */
class GeographicArea : public DigitalSelectiveCall
{
public:

	GeographicArea(Mmsi selfId, Area area, Category category,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Frequency frequencyRx,
		Frequency frequencyTx = Frequency(0));

	std::vector<Code> toCodes();

	Area getArea();
	Category getCategory();
	FirstTelecommand getFirstTelecommand();
	SecondTelecommand getSecondTelecommand();
	Frequency getFrequencyRx();
	Frequency getFrequencyTx();
	bool getHasFrequencyTx();

private:

	Area area;
	Category category;
	FirstTelecommand firstTelecommand;
	SecondTelecommand secondTelecommand;
	Frequency frequencyRx;
	Frequency frequencyTx;
	bool hasFrequencyTx;
};