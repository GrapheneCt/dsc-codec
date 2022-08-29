#include <string>

#include "distress/AbstractDistressRelay.h"
#include "distress/DistressRelayRq.h"

DistressRelayRq::DistressRelayRq(FormatSpecifier formatSpecifier, Mmsi selfId,
	Mmsi distressMmsi, DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications,
	Address address,
	ExpansionPosition expansionPosition) :
	AbstractDistressRelay(formatSpecifier, Phasing(Code(Phasing::Symbol_EOS_ACK_RQ)), selfId, distressMmsi, nature,
		distressCoordinates, time, subsequentCommunications, address,
		expansionPosition)
{

}

DistressRelayRq::DistressRelayRq(FormatSpecifier formatSpecifier, Mmsi selfId,
	Mmsi distressMmsi, DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications,
	ExpansionPosition expansionPosition) :
	AbstractDistressRelay(formatSpecifier, Phasing(Code(Phasing::Symbol_EOS_ACK_RQ)), selfId, distressMmsi, nature,
		distressCoordinates, time, subsequentCommunications, expansionPosition)
{

}

DistressRelayRq::DistressRelayRq(FormatSpecifier formatSpecifier, Mmsi selfId,
	Mmsi distressMmsi, DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications) :
	AbstractDistressRelay(formatSpecifier, Phasing(Code(Phasing::Symbol_EOS_ACK_RQ)), selfId, distressMmsi, nature,
		distressCoordinates, time, subsequentCommunications)
{

}

std::string DistressRelayRq::toString()
{
	std::string ret("DistressRelayRq{");
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