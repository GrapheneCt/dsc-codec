#include <string>
#include <vector>

#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "entities/PstnNumber.h"
#include "entities/Frequency.h"
#include "DigitalSelectiveCall.h"
#include "AllShipsCall.h"

AllShipsCall::AllShipsCall(Mmsi selfId, Category category,
	FirstTelecommand firstTelecommand,
	SecondTelecommand secondTelecommand,
	Frequency frequencyRx,
	Frequency frequencyTx) :
	DigitalSelectiveCall(FormatSpecifier(Code(FormatSpecifier::Symbol_ALL_SHIPS)), Phasing(Code(Phasing::Symbol_EOS)), selfId)
{
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

std::vector<Code> AllShipsCall::toCodes()
{
	std::vector<Code> codes;

	codes.push_back(getFormatSpecifier().getCode());
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

Category AllShipsCall::getCategory()
{
	return category;
}

FirstTelecommand AllShipsCall::getFirstTelecommand()
{
	return firstTelecommand;
}

SecondTelecommand AllShipsCall::getSecondTelecommand()
{
	return secondTelecommand;
}

Frequency AllShipsCall::getFrequencyRx()
{
	return frequencyRx;
}

Frequency AllShipsCall::getFrequencyTx()
{
	return frequencyTx;
}

bool AllShipsCall::getHasFrequencyTx()
{
	return hasFrequencyTx;
}