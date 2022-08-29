#include <string>

#include "distress/AbstractDistressRelay.h"
#include "distress/DistressRelayAck.h"

DistressRelayAck::DistressRelayAck(FormatSpecifier formatSpecifier, Mmsi  selfId,
	Mmsi distressMmsi, DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications,
	Address address,
	ExpansionPosition expansionPosition) :
	AbstractDistressRelay(formatSpecifier, Phasing(Code(Phasing::Symbol_EOS_ACK_BQ)), selfId, distressMmsi, nature,
		distressCoordinates, time, subsequentCommunications, address,
		expansionPosition)
{

}

DistressRelayAck::DistressRelayAck(FormatSpecifier formatSpecifier, Mmsi  selfId,
	Mmsi distressMmsi, DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications,
	Address address) :
	AbstractDistressRelay(formatSpecifier, Phasing(Code(Phasing::Symbol_EOS_ACK_BQ)), selfId, distressMmsi, nature,
		distressCoordinates, time, subsequentCommunications, address)
{

}

DistressRelayAck::DistressRelayAck(FormatSpecifier formatSpecifier, Mmsi  selfId,
	Mmsi distressMmsi, DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications,
	ExpansionPosition expansionPosition) :
	AbstractDistressRelay(formatSpecifier, Phasing(Code(Phasing::Symbol_EOS_ACK_BQ)), selfId, distressMmsi, nature,
		distressCoordinates, time, subsequentCommunications, expansionPosition)
{

}

DistressRelayAck::DistressRelayAck(FormatSpecifier formatSpecifier, Mmsi  selfId,
	Mmsi distressMmsi, DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications) :
	AbstractDistressRelay(formatSpecifier, Phasing(Code(Phasing::Symbol_EOS_ACK_BQ)), selfId, distressMmsi, nature,
		distressCoordinates, time, subsequentCommunications)
{

}

std::string DistressRelayAck::toString()
{
	std::string ret("DistressRelayAck{");
	ret += "\nformatSpecifier=" + getFormatSpecifier().toString();
	ret += "\nselfId=" + getSelfId().toString();
	//ret += ", address=" + getAddress().toString();
	ret += "\ncategory=" + getCategory().toString();
	ret += "\ntelecommand=" + getTelecommand().toString();
	ret += "\ndistressMmsi=" + getDistressMmsi().toString();
	ret += "\nnature=" + getNature().toString();
	ret += "\ndistressCoordinates=" + getDistressCoordinates().toString();
	ret += "\ntime=" + getTime().toString();
	ret += "\nsubsequentCommunications=" + getSubsequentCommunications().toString();
	ret += "\nexpansion=" + getExpansion().toString();
	ret += "\neos=" + getEos().toString();
	ret += "\n}";

	return ret;
}