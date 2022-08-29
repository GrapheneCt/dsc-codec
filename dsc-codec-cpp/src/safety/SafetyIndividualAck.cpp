#include <string>

#include "entities/Frequency.h"
#include "entities/Mmsi.h"
#include "IndividualCall.h"
#include "safety/SafetyIndividualAck.h"

SafetyIndividualAck::SafetyIndividualAck(Mmsi selfId, Mmsi address,
	FirstTelecommand firstTelecommand,
	SecondTelecommand secondTelecommand,
	Frequency frequencyRx,
	Frequency frequencyTx,
	Coordinates coordinates,
	TimeUTC time) :
	IndividualCall(Phasing(Code(Phasing::Symbol_EOS_ACK_BQ)), selfId, address, Category(Code(Category::Symbol_SAFETY)),
		firstTelecommand, secondTelecommand, frequencyRx, frequencyTx,
		coordinates, time)
{

}

std::string SafetyIndividualAck::toString()
{
	std::string ret("SafetyAllShips{");
	ret += "\nformatSpecifier=" + getFormatSpecifier().toString();
	ret += "\nselfId=" + getSelfId().toString();
	ret += "\naddress=" + getAddress().toString();
	ret += "\ncategory=" + getCategory().toString();
	ret += "\nfirstTelecommand=" + getFirstTelecommand().toString();
	ret += "\nsecondTelecommand=" + getSecondTelecommand().toString();
	ret += "\nfrequencyRx=" + getFrequencyRx().toString();
	ret += "\nfrequencyTx=" + getFrequencyTx().toString();
	ret += "\ncoordinates=" + getCoordinates().toString();
	ret += "\ntime=" + getTime().toString();
	ret += "\neos=" + getEos().toString();
	ret += "\n}";

	return ret;
}