#include <string>

#include "entities/Frequency.h"
#include "entities/Mmsi.h"
#include "GeographicArea.h"
#include "safety/SafetyGeographicArea.h"

SafetyGeographicArea::SafetyGeographicArea(Mmsi selfId, Area area,
	FirstTelecommand ft,
	SecondTelecommand st,
	Frequency freqRx,
	Frequency freqTx) :
	GeographicArea(selfId, area, Category(Code(Category::Symbol_SAFETY)), ft, st, freqRx, freqTx)
{

}

SafetyGeographicArea::SafetyGeographicArea(Mmsi selfId, Area area,
	FirstTelecommand ft,
	SecondTelecommand st,
	Frequency freqRx) :
	GeographicArea(selfId, area, Category(Code(Category::Symbol_SAFETY)), ft, st, freqRx)
{

}

std::string SafetyGeographicArea::toString()
{
	std::string ret("SafetyGeographicArea{");
	ret += "\nformatSpecifier=" + getFormatSpecifier().toString();
	ret += "\nselfId=" + getSelfId().toString();
	ret += "\narea=" + getArea().toString();
	ret += "\ncategory=" + getCategory().toString();
	ret += "\nfirstTelecommand=" + getFirstTelecommand().toString();
	ret += "\nsecondTelecommand=" + getSecondTelecommand().toString();
	ret += "\nfrequencyRx=" + getFrequencyRx().toString();
	ret += "\nfrequencyTx=" + getFrequencyTx().toString();
	ret += "\neos=" + getEos().toString();
	ret += "\n}";

	return ret;
}