#pragma once

#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "entities/PstnNumber.h"
#include "entities/Frequency.h"
#include "entities/Area.h"
#include "entities/TimeUTC.h"
#include "DigitalSelectiveCall.h"

/**
 * Individual call.
 *
 * This call may be call with request for acknowledge or acknowledge-call.
 * Difference in EOS symbol.
 *
 * @author AlexeyVorobyev
 */
class IndividualCall : public DigitalSelectiveCall
{
public:

	IndividualCall(Phasing eos, Mmsi selfId, Mmsi address,
		Category category,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		Frequency frequencyRx = Frequency(0),
		Frequency frequencyTx = Frequency(0),
		Coordinates coordinates = Coordinates(),
		TimeUTC time = TimeUTC());

	std::vector<Code> toCodes();

	Frequency getFrequencyTx();
	Mmsi getAddress();
	Category getCategory();
	FirstTelecommand getFirstTelecommand();
	SecondTelecommand getSecondTelecommand();
	Frequency getFrequencyRx();
	Coordinates getCoordinates();
	TimeUTC getTime();

	bool getHasFrequencyTx();
	bool getHasFrequencyRx();
	bool getHasCoordinates();
	bool getHasTime();

private:

	/** Address of receiver */
	Mmsi address;
	/** May be Safety, Urgency è Routine */
	Category category;
	FirstTelecommand firstTelecommand;
	SecondTelecommand secondTelecommand;
	Frequency frequencyRx;
	Coordinates coordinates;
	TimeUTC time;
	Frequency frequencyTx;

	bool hasFrequencyRx;
	bool hasCoordinates;
	bool hasTime;
	bool hasFrequencyTx;
};