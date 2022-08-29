#include <string>

#include "distress/AbstractDistressRelay.h"
#include "distress/DistressRelay.h"

DistressRelay::DistressRelay(FormatSpecifier formatSpecifier, Mmsi selfId,
	Mmsi distressMmsi, DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications,
	Address address,
	ExpansionPosition expansionPosition) :
	AbstractDistressRelay(formatSpecifier, Phasing(Code(Phasing::Symbol_EOS)), selfId, distressMmsi, nature,
		distressCoordinates, time, subsequentCommunications, address,
		expansionPosition)
{

}

DistressRelay::DistressRelay(FormatSpecifier formatSpecifier, Mmsi selfId,
	Mmsi distressMmsi, DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications,
	Address address) :
	AbstractDistressRelay(formatSpecifier, Phasing(Code(Phasing::Symbol_EOS)), selfId, distressMmsi, nature,
		distressCoordinates, time, subsequentCommunications, address)
{

}

DistressRelay::DistressRelay(FormatSpecifier formatSpecifier, Mmsi selfId,
	Mmsi distressMmsi, DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications,
	ExpansionPosition expansionPosition) :
	AbstractDistressRelay(formatSpecifier, Phasing(Code(Phasing::Symbol_EOS)), selfId, distressMmsi, nature,
		distressCoordinates, time, subsequentCommunications, expansionPosition)
{

}

DistressRelay::DistressRelay(FormatSpecifier formatSpecifier, Mmsi selfId,
	Mmsi distressMmsi, DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications) :
	AbstractDistressRelay(formatSpecifier, Phasing(Code(Phasing::Symbol_EOS)), selfId, distressMmsi, nature,
		distressCoordinates, time, subsequentCommunications)
{

}

std::string DistressRelay::toString()
{
	std::string ret("DistressRelay{");
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