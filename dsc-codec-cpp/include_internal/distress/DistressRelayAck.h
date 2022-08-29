#pragma once

#include "distress/AbstractDistressRelay.h"

/** @author AlexeyVorobyev */
class DistressRelayAck : public AbstractDistressRelay
{
public:

	DistressRelayAck(FormatSpecifier formatSpecifier, Mmsi  selfId,
		Mmsi distressMmsi, DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications,
		Address address,
		ExpansionPosition expansionPosition);

	DistressRelayAck(FormatSpecifier formatSpecifier, Mmsi  selfId,
		Mmsi distressMmsi, DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications,
		Address address);

	DistressRelayAck(FormatSpecifier formatSpecifier, Mmsi  selfId,
		Mmsi distressMmsi, DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications,
		ExpansionPosition expansionPosition);

	DistressRelayAck(FormatSpecifier formatSpecifier, Mmsi  selfId,
		Mmsi distressMmsi, DistressNature nature,
		Coordinates distressCoordinates, TimeUTC time,
		FirstTelecommand subsequentCommunications);

	std::string toString();
};