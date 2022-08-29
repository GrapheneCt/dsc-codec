#include <string>
#include <vector>

#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "entities/PstnNumber.h"
#include "entities/Frequency.h"
#include "entities/Area.h"
#include "DigitalSelectiveCall.h"
#include "GeographicArea.h"

GeographicArea::GeographicArea(Mmsi selfId, Area area, Category category,
	FirstTelecommand firstTelecommand,
	SecondTelecommand secondTelecommand,
	Frequency frequencyRx,
	Frequency frequencyTx) :
	DigitalSelectiveCall(FormatSpecifier(Code(FormatSpecifier::Symbol_GEOGRAPHICAL_AREA)), Phasing(Code(Phasing::Symbol_EOS)), selfId)
{
	this->area = area;
	this->category = category;
	this->firstTelecommand = firstTelecommand;
	this->secondTelecommand = secondTelecommand;
	this->frequencyRx = frequencyRx;
	this->frequencyTx = frequencyTx;
	this->hasFrequencyTx = false;

	if (this->frequencyTx.getValue() != 0) {
		this->hasFrequencyTx = true;
	}
}

Area GeographicArea::getArea()
{
	return area;
}

Category GeographicArea::getCategory()
{
	return category;
}

FirstTelecommand GeographicArea::getFirstTelecommand()
{
	return firstTelecommand;
}

SecondTelecommand GeographicArea::getSecondTelecommand()
{
	return secondTelecommand;
}

Frequency GeographicArea::getFrequencyRx()
{
	return frequencyRx;
}

Frequency GeographicArea::getFrequencyTx()
{
	return frequencyTx;
}

bool GeographicArea::getHasFrequencyTx()
{
	return hasFrequencyTx;
}

std::vector<Code> GeographicArea::toCodes()
{
	std::vector<Code> codes;

	codes.push_back(getFormatSpecifier().getCode());
	std::vector<Code> areaCodes = area.toCodes();
	codes.insert(codes.end(), areaCodes.begin(), areaCodes.end());
	codes.push_back(category.getCode());
	std::vector<Code> selfIdCodes = getSelfId().toCodes();
	codes.insert(codes.end(), selfIdCodes.begin(), selfIdCodes.end());
	codes.push_back(firstTelecommand.getCode());
	codes.push_back(secondTelecommand.getCode());
	std::vector<Code> frxCodes = frequencyRx.toCodes();
	codes.insert(codes.end(), frxCodes.begin(), frxCodes.end());

	std::vector<Code> ftxCodes;
	if (hasFrequencyTx)
		ftxCodes = frequencyTx.toCodes();
	else
		ftxCodes = Frequency::getNoInfoCodes();
	codes.insert(codes.end(), ftxCodes.begin(), ftxCodes.end());

	codes.push_back(getEos().getCode());

	codes.push_back(calculateEccFromInfoCodes(codes));

	codes.insert(codes.begin(), getFormatSpecifier().getCode());

	return codes;
}