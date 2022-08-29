#pragma once

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "entities/Mmsi.h"
#include "entities/TimeUTC.h"
#include "structure/Category.h"
#include "structure/DistressNature.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "DigitalSelectiveCall.h"

/** @author AlexeyVorobyev */
class DistressAck : public DigitalSelectiveCall
{
public:

	DistressAck(Mmsi selfId, Mmsi distressMmsi,
		DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications);

	DistressAck(Mmsi selfId, Mmsi distressMmsi,
		DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications,
		ExpansionPosition expansionPosition);

	Category getCategory();
	FirstTelecommand getTelecommand();
	Mmsi getDistressMmsi();
	DistressNature getNature();
	Coordinates getDistressCoordinates();
	TimeUTC getTime();
	FirstTelecommand getSubsequentCommunications();
	ExpansionPosition getExpansionPosition();

	/** @see DigitalSelectiveCall#toCodes() */
	std::vector<Code> toCodes();

	ExpansionPosition getExpansion();

	std::string toString();

private:

	Category category;
	FirstTelecommand telecommand;
	Mmsi distressMmsi;
	DistressNature nature;
	Coordinates distressCoordinates;
	TimeUTC time;
	FirstTelecommand subsequentCommunications;
	ExpansionPosition expansionPosition;
	bool hasExpansionPosition;
};
