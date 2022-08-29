#pragma once

#include "distress/AbstractDistressRelay.h"

/** @author AlexeyVorobyev */
class DistressRelayRq : public AbstractDistressRelay
{
public:

	DistressRelayRq(FormatSpecifier formatSpecifier, Mmsi selfId,
		Mmsi distressMmsi, DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications,
		Address address,
		ExpansionPosition expansionPosition);

	DistressRelayRq(FormatSpecifier formatSpecifier, Mmsi selfId,
		Mmsi distressMmsi, DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications,
		ExpansionPosition expansionPosition);

	DistressRelayRq(FormatSpecifier formatSpecifier, Mmsi selfId,
		Mmsi distressMmsi, DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications);

	std::string toString();
};