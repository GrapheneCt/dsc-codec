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
class AbstractDistressRelay : public DigitalSelectiveCall
{
public:

	AbstractDistressRelay(FormatSpecifier formatSpecifier, Phasing eos,
		Mmsi selfId, Mmsi distressMmsi,
		DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications,
		Address address,
		ExpansionPosition expansionPosition);

	AbstractDistressRelay(FormatSpecifier formatSpecifier, Phasing eos,
		Mmsi selfId, Mmsi distressMmsi,
		DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications,
		Address address);

	AbstractDistressRelay(FormatSpecifier formatSpecifier, Phasing eos,
		Mmsi selfId, Mmsi distressMmsi,
		DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications,
		ExpansionPosition expansionPosition);

	AbstractDistressRelay(FormatSpecifier formatSpecifier, Phasing eos,
		Mmsi selfId, Mmsi distressMmsi,
		DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications);

	Address getAddress();

	Category getCategory();

	FirstTelecommand getTelecommand();

	Mmsi getDistressMmsi();

	DistressNature getNature();

	Coordinates getDistressCoordinates();

	TimeUTC getTime();

	FirstTelecommand getSubsequentCommunications();

	ExpansionPosition getExpansion();

	/** @see DigitalSelectiveCall#toCodes() */
	std::vector<Code> toCodes();

private:

	Category category;
	FirstTelecommand telecommand;
	Address address;
	Mmsi distressMmsi;
	DistressNature nature;
	Coordinates distressCoordinates;
	TimeUTC time;
	FirstTelecommand subsequentCommunications;
	ExpansionPosition expansionPosition;
	bool hasExpansionPosition;
	bool hasAddress;
};