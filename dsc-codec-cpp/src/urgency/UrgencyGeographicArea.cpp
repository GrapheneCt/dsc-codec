#include <string>
#include <vector>

#include "entities/Mmsi.h"
#include "entities/Frequency.h"
#include "DigitalSelectiveCall.h"
#include "GeographicArea.h"
#include "urgency/UrgencyGeographicArea.h"

UrgencyGeographicArea::UrgencyGeographicArea(Mmsi selfId, Area area,
	FirstTelecommand ft,
	SecondTelecommand st,
	Frequency freqRx,
	Frequency freqTx) :
	GeographicArea(selfId, area, Category(Code(Category::Symbol_URGENCY)), ft, st, freqRx, freqTx)
{

}

UrgencyGeographicArea::UrgencyGeographicArea(Mmsi selfId, Area area,
	FirstTelecommand ft,
	SecondTelecommand st,
	Frequency freqRx) :
	GeographicArea(selfId, area, Category(Code(Category::Symbol_URGENCY)), ft, st, freqRx)
{

}

std::string UrgencyGeographicArea::toString()
{
	std::string ret("UrgencyGeographicArea{");
	ret += "\nformatSpecifier = " + getFormatSpecifier().toString();
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