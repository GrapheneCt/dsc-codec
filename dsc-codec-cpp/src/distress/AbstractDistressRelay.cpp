#include <string>
#include <vector>

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "entities/Mmsi.h"
#include "entities/TimeUTC.h"
#include "structure/Category.h"
#include "structure/DistressNature.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "DigitalSelectiveCall.h"
#include "distress/AbstractDistressRelay.h"

AbstractDistressRelay::AbstractDistressRelay(FormatSpecifier formatSpecifier, Phasing eos,
	Mmsi selfId, Mmsi distressMmsi,
	DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications,
	Address address,
	ExpansionPosition expansionPosition) :
	DigitalSelectiveCall(formatSpecifier, eos, selfId)
{
	this->category = Category(Code(Category::Symbol_DISTRESS));
	this->telecommand = FirstTelecommand(Code(FirstTelecommand::Symbol_DISTRESS_RELAY));
	this->address = address;
	this->distressMmsi = distressMmsi;
	this->nature = nature;
	this->distressCoordinates = distressCoordinates;
	this->time = time;
	this->subsequentCommunications = subsequentCommunications;
	this->expansionPosition = expansionPosition;
	this->hasExpansionPosition = true;
	this->hasAddress = true;
}

AbstractDistressRelay::AbstractDistressRelay(FormatSpecifier formatSpecifier, Phasing eos,
	Mmsi selfId, Mmsi distressMmsi,
	DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications,
	Address address) :
	DigitalSelectiveCall(formatSpecifier, eos, selfId)
{
	this->category = Category(Code(Category::Symbol_DISTRESS));
	this->telecommand = FirstTelecommand(Code(FirstTelecommand::Symbol_DISTRESS_RELAY));
	this->address = address;
	this->distressMmsi = distressMmsi;
	this->nature = nature;
	this->distressCoordinates = distressCoordinates;
	this->time = time;
	this->subsequentCommunications = subsequentCommunications;
	this->hasExpansionPosition = false;
	this->hasAddress = true;
}

AbstractDistressRelay::AbstractDistressRelay(FormatSpecifier formatSpecifier, Phasing eos,
	Mmsi selfId, Mmsi distressMmsi,
	DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications,
	ExpansionPosition expansionPosition) :
	DigitalSelectiveCall(formatSpecifier, eos, selfId)
{
	this->category = Category(Code(Category::Symbol_DISTRESS));
	this->telecommand = FirstTelecommand(Code(FirstTelecommand::Symbol_DISTRESS_RELAY));
	this->distressMmsi = distressMmsi;
	this->nature = nature;
	this->distressCoordinates = distressCoordinates;
	this->time = time;
	this->subsequentCommunications = subsequentCommunications;
	this->expansionPosition = expansionPosition;
	this->hasExpansionPosition = true;
	this->hasAddress = false;
}

AbstractDistressRelay::AbstractDistressRelay(FormatSpecifier formatSpecifier, Phasing eos,
	Mmsi selfId, Mmsi distressMmsi,
	DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications) :
	DigitalSelectiveCall(formatSpecifier, eos, selfId)
{
	this->category = Category(Code(Category::Symbol_DISTRESS));
	this->telecommand = FirstTelecommand(Code(FirstTelecommand::Symbol_DISTRESS_RELAY));
	this->distressMmsi = distressMmsi;
	this->nature = nature;
	this->distressCoordinates = distressCoordinates;
	this->time = time;
	this->subsequentCommunications = subsequentCommunications;
	this->hasExpansionPosition = false;
	this->hasAddress = false;
}

Address AbstractDistressRelay::getAddress() {
	return address;
}

Category AbstractDistressRelay::getCategory() {
	return category;
}

FirstTelecommand AbstractDistressRelay::getTelecommand() {
	return telecommand;
}

Mmsi AbstractDistressRelay::getDistressMmsi() {
	return distressMmsi;
}

DistressNature AbstractDistressRelay::getNature() {
	return nature;
}

Coordinates AbstractDistressRelay::getDistressCoordinates() {
	return distressCoordinates;
}

TimeUTC AbstractDistressRelay::getTime() {
	return time;
}

FirstTelecommand AbstractDistressRelay::getSubsequentCommunications() {
	return subsequentCommunications;
}

ExpansionPosition AbstractDistressRelay::getExpansion() {
	return expansionPosition;
}

/** @see DigitalSelectiveCall#toCodes() */
std::vector<Code> AbstractDistressRelay::toCodes()
{
	std::vector<Code> codes;

	codes.push_back(getFormatSpecifier().getCode());

	if (hasAddress) {
		std::vector<Code> addrCodes = address.toCodes();
		codes.insert(codes.end(), addrCodes.begin(), addrCodes.end());
	}

	codes.push_back(category.getCode());
	std::vector<Code> selfIdCodes = getSelfId().toCodes();
	codes.insert(codes.end(), selfIdCodes.begin(), selfIdCodes.end());
	codes.push_back(telecommand.getCode());
	std::vector<Code> dsMmsiCodes = distressMmsi.toCodes();
	codes.insert(codes.end(), dsMmsiCodes.begin(), dsMmsiCodes.end());
	codes.push_back(nature.getCode());
	std::vector<Code> dsCoordCodes = distressCoordinates.toCodes();
	codes.insert(codes.end(), dsCoordCodes.begin(), dsCoordCodes.end());
	std::vector<Code> timeCodes = time.toCodes();
	codes.insert(codes.end(), timeCodes.begin(), timeCodes.end());
	codes.push_back(subsequentCommunications.getCode());
	codes.push_back(getEos().getCode());

	codes.push_back(calculateEccFromInfoCodes(codes));
	codes.insert(codes.begin(), getFormatSpecifier().getCode());

	return codes;
}