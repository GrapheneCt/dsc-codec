#include <string>
#include <vector>

#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "entities/PstnNumber.h"
#include "entities/Frequency.h"
#include "entities/Area.h"
#include "entities/TimeUTC.h"
#include "DscMarkers.h"
#include "DigitalSelectiveCall.h"
#include "IndividualCall.h"

IndividualCall::IndividualCall(Phasing eos, Mmsi selfId, Mmsi address,
	Category category,
	FirstTelecommand firstTelecommand,
	SecondTelecommand secondTelecommand,
	Frequency frequencyRx,
	Frequency frequencyTx,
	Coordinates coordinates,
	TimeUTC time) :
	DigitalSelectiveCall(FormatSpecifier(Code(FormatSpecifier::Symbol_INDIVIDUAL)), eos, selfId)
{
	this->address = address;
	this->category = category;
	this->firstTelecommand = firstTelecommand;
	this->secondTelecommand = secondTelecommand;
	this->frequencyRx = frequencyRx;
	this->coordinates = coordinates;
	this->time = time;
	this->frequencyTx = frequencyTx;
	this->hasFrequencyRx = false;
	this->hasCoordinates = false;
	this->hasTime = false;
	this->hasFrequencyTx = false;

	if (this->frequencyTx.getValue() != 0) {
		this->hasFrequencyTx = true;
	}

	if (this->frequencyRx.getValue() != 0) {
		this->hasFrequencyRx = true;
	}

	if (this->coordinates.getLatitude() != "9999" &&
		this->coordinates.getLongitude() != "99999") {
		this->hasCoordinates = true;
	}

	if (this->time.getUtcTime() != 0) {
		this->hasTime = true;
	}
}

Frequency IndividualCall::getFrequencyTx()
{
	return frequencyTx;
}

Mmsi IndividualCall::getAddress()
{
	return address;
}

Category IndividualCall::getCategory()
{
	return category;
}

FirstTelecommand IndividualCall::getFirstTelecommand()
{
	return firstTelecommand;
}

SecondTelecommand IndividualCall::getSecondTelecommand()
{
	return secondTelecommand;
}

Frequency IndividualCall::getFrequencyRx()
{
	return frequencyRx;
}

Coordinates IndividualCall::getCoordinates()
{
	return coordinates;
}

TimeUTC IndividualCall::getTime()
{
	return time;
}

std::vector<Code> IndividualCall::toCodes()
{
	std::vector<Code> codes;

	codes.push_back(getFormatSpecifier().getCode());
	std::vector<Code> addrCodes = address.toCodes();
	codes.insert(codes.end(), addrCodes.begin(), addrCodes.end());
	codes.push_back(category.getCode());
	std::vector<Code> selfIdCodes = getSelfId().toCodes();
	codes.insert(codes.end(), selfIdCodes.begin(), selfIdCodes.end());
	codes.push_back(firstTelecommand.getCode());
	codes.push_back(secondTelecommand.getCode());

	if (hasFrequencyRx) {
		std::vector<Code> frxCodes = frequencyRx.toCodes();
		codes.insert(codes.end(), frxCodes.begin(), frxCodes.end());
	}
	else if (hasCoordinates) {
		codes.push_back(Code(DscMarkers::posMarker));
		std::vector<Code> coordCodes = coordinates.toCodes();
		codes.insert(codes.end(), coordCodes.begin(), coordCodes.end());
	}

	std::vector<Code> ftxCodes;
	if (hasFrequencyTx)
		ftxCodes = frequencyTx.toCodes();
	else
		ftxCodes = Frequency::getNoInfoCodes();
	codes.insert(codes.end(), ftxCodes.begin(), ftxCodes.end());

	if (hasTime) {
		std::vector<Code> timeCodes = time.toCodes();
		codes.insert(codes.end(), timeCodes.begin(), timeCodes.end());
	}

	codes.push_back(getEos().getCode());

	codes.push_back(calculateEccFromInfoCodes(codes));

	codes.insert(codes.begin(), getFormatSpecifier().getCode());

	return codes;
}

bool IndividualCall::getHasFrequencyTx()
{
	return hasFrequencyTx;
}

bool IndividualCall::getHasFrequencyRx()
{
	return hasFrequencyRx;
}

bool IndividualCall::getHasCoordinates()
{
	return hasCoordinates;
}

bool IndividualCall::getHasTime()
{
	return hasTime;
}