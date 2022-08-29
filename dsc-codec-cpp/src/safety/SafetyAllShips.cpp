#include <string>

#include "entities/Frequency.h"
#include "entities/Mmsi.h"
#include "AllShipsCall.h"
#include "safety/SafetyAllShips.h"

SafetyAllShips::SafetyAllShips(Mmsi selfId, FirstTelecommand ft,
	SecondTelecommand st, Frequency freqRx,
	Frequency freqTx) :
	AllShipsCall(selfId, Category(Code(Category::Symbol_SAFETY)), ft, st, freqRx, freqTx)
{

}

SafetyAllShips::SafetyAllShips(Mmsi selfId, FirstTelecommand ft,
	SecondTelecommand st, Frequency freqRx) :
	AllShipsCall(selfId, Category(Code(Category::Symbol_SAFETY)), ft, st, freqRx)
{

}

std::string SafetyAllShips::toString()
{
	std::string ret("SafetyAllShips{");
	ret += "\nformatSpecifier=" + getFormatSpecifier().toString();
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