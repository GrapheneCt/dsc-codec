#include <string>
#include <vector>

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "IndividualCall.h"
#include "routine/RoutineIndividualAck.h"

RoutineIndividualAck::RoutineIndividualAck(Mmsi selfId, Mmsi address,
	FirstTelecommand firstTelecommand,
	SecondTelecommand secondTelecommand,
	Frequency frequencyRx) :
	IndividualCall(Phasing(Code(Phasing::Symbol_EOS_ACK_BQ)), selfId, address, Category(Code(Category::Symbol_ROUTINE)),
		firstTelecommand, secondTelecommand, frequencyRx, Frequency(0),
		Coordinates())
{

}

RoutineIndividualAck::RoutineIndividualAck(Mmsi selfId, Mmsi address,
	FirstTelecommand firstTelecommand,
	SecondTelecommand secondTelecommand,
	Frequency frequencyRx,
	Frequency frequencyTx) :
	IndividualCall(Phasing(Code(Phasing::Symbol_EOS_ACK_BQ)), selfId, address, Category(Code(Category::Symbol_ROUTINE)),
		firstTelecommand, secondTelecommand, frequencyRx, frequencyTx,
		Coordinates())
{

}

RoutineIndividualAck::RoutineIndividualAck(Mmsi selfId, Mmsi address,
	FirstTelecommand firstTelecommand,
	SecondTelecommand secondTelecommand,
	Coordinates coordinates) :
	IndividualCall(Phasing(Code(Phasing::Symbol_EOS_ACK_BQ)), selfId, address, Category(Code(Category::Symbol_ROUTINE)),
		firstTelecommand, secondTelecommand, Frequency(0), Frequency(0),
		coordinates)
{

}

RoutineIndividualAck::RoutineIndividualAck(Mmsi selfId, Mmsi address,
	FirstTelecommand firstTelecommand,
	SecondTelecommand secondTelecommand,
	Frequency frequencyRx,
	Frequency frequencyTx,
	Coordinates coordinates) :
	IndividualCall(Phasing(Code(Phasing::Symbol_EOS_ACK_BQ)), selfId, address, Category(Code(Category::Symbol_ROUTINE)),
		firstTelecommand, secondTelecommand, frequencyRx, frequencyTx,
		coordinates)
{

}

std::string RoutineIndividualAck::toString()
{
	std::string ret("RoutineIndividual{");
	ret += "\nformatSpecifier=" + getFormatSpecifier().toString();
	ret += "\nselfId=" + getSelfId().toString();
	ret += "\naddress=" + getAddress().toString();
	ret += "\ncategory=" + getCategory().toString();
	ret += "\nfirstTelecommand=" + getFirstTelecommand().toString();
	ret += "\nsecondTelecommand=" + getSecondTelecommand().toString();
	ret += "\nfrequencyRx=" + getFrequencyRx().toString();
	ret += "\nfrequencyTx=" + getFrequencyTx().toString();
	ret += "\ncoordinates=" + getCoordinates().toString();
	ret += "\neos=" + getEos().toString();
	ret += "\n}";

	return ret;
}