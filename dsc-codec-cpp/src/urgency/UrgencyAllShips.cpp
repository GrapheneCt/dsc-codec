#include <string>
#include <vector>

#include "entities/Mmsi.h"
#include "entities/Frequency.h"
#include "DigitalSelectiveCall.h"
#include "AllShipsCall.h"
#include "urgency/UrgencyAllShips.h"

UrgencyAllShips::UrgencyAllShips(Mmsi selfId, FirstTelecommand ft,
	SecondTelecommand st, Frequency freqRx,
	Frequency freqTx) :
	AllShipsCall(selfId, Category(Code(Category::Symbol_URGENCY)), ft, st, freqRx, freqTx)
{

}

UrgencyAllShips::UrgencyAllShips(Mmsi selfId, FirstTelecommand ft,
	SecondTelecommand st, Frequency freqRx) :
	AllShipsCall(selfId, Category(Code(Category::Symbol_URGENCY)), ft, st, freqRx)
{

}

std::string UrgencyAllShips::toString()
{
	std::string ret("UrgencyAllShips{");
	ret += "\nformatSpecifier = " + getFormatSpecifier().toString();
	ret += "\nselfId=" + getSelfId().toString();
	ret += "\ncategory=" + getCategory().toString();
	ret += "\nfirstTelecommand=" + getFirstTelecommand().toString();
	ret += "\nsecondTelecommand=" + getSecondTelecommand().toString();
	ret += "\nfrequencyRx=" + getFrequencyRx().toString();
	ret += "\nfrequencyTx=" + getFrequencyTx().toString();
	ret += "\neos=" + getEos().toString();
	ret += "\n}";

	return ret;
}