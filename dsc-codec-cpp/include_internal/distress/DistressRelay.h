#pragma once

#include "distress/AbstractDistressRelay.h"

/** @author AlexeyVorobyev */
class DistressRelay : public AbstractDistressRelay
{
public:

	DistressRelay(FormatSpecifier formatSpecifier, Mmsi selfId,
		Mmsi distressMmsi, DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications,
		Address address,
		ExpansionPosition expansionPosition);

	DistressRelay(FormatSpecifier formatSpecifier, Mmsi selfId,
		Mmsi distressMmsi, DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications,
		Address address);

	DistressRelay(FormatSpecifier formatSpecifier, Mmsi selfId,
		Mmsi distressMmsi, DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications,
		ExpansionPosition expansionPosition);

	DistressRelay(FormatSpecifier formatSpecifier, Mmsi selfId,
		Mmsi distressMmsi, DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications);

	std::string toString();
};