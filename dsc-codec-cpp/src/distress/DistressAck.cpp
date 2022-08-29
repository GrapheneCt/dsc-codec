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
#include "distress/DistressAck.h"

DistressAck::DistressAck(Mmsi selfId, Mmsi distressMmsi,
	DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications) :
	DigitalSelectiveCall(FormatSpecifier(Code(FormatSpecifier::Symbol_ALL_SHIPS)), Phasing(Code(Phasing::Symbol_EOS)), selfId)
{
	this->category = Category(Code(Category::Symbol_DISTRESS));
	this->telecommand = FirstTelecommand(Code(FirstTelecommand::Symbol_DISTRESS_ACK));
	this->distressMmsi = distressMmsi;
	this->nature = nature;
	this->distressCoordinates = distressCoordinates;
	this->time = time;
	this->subsequentCommunications = subsequentCommunications;
	this->hasExpansionPosition = false;
}

DistressAck::DistressAck(Mmsi selfId, Mmsi distressMmsi,
	DistressNature nature,
	Coordinates distressCoordinates, TimeUTC time,
	FirstTelecommand subsequentCommunications,
	ExpansionPosition expansionPosition) :
	DigitalSelectiveCall(FormatSpecifier(Code(FormatSpecifier::Symbol_ALL_SHIPS)), Phasing(Code(Phasing::Symbol_EOS)), selfId)
{
	this->category = Category(Code(Category::Symbol_DISTRESS));
	this->telecommand = FirstTelecommand(Code(FirstTelecommand::Symbol_DISTRESS_ACK));
	this->distressMmsi = distressMmsi;
	this->nature = nature;
	this->distressCoordinates = distressCoordinates;
	this->time = time;
	this->subsequentCommunications = subsequentCommunications;
	this->expansionPosition = expansionPosition;
	this->hasExpansionPosition = true;
}

Category DistressAck::getCategory() {
	return category;
}

FirstTelecommand DistressAck::getTelecommand() {
	return telecommand;
}

Mmsi DistressAck::getDistressMmsi() {
	return distressMmsi;
}

DistressNature DistressAck::getNature() {
	return nature;
}

Coordinates DistressAck::getDistressCoordinates() {
	return distressCoordinates;
}

TimeUTC DistressAck::getTime() {
	return time;
}

FirstTelecommand DistressAck::getSubsequentCommunications() {
	return subsequentCommunications;
}

ExpansionPosition DistressAck::getExpansionPosition() {
	return expansionPosition;
}

/** @see DigitalSelectiveCall#toCodes() */
std::vector<Code> DistressAck::toCodes()
{
	std::vector<Code> codes;

	codes.push_back(getFormatSpecifier().getCode());
	codes.push_back(category.getCode());
	std::vector<Code> selfIdCodes = getSelfId().toCodes();
	codes.insert(codes.end(), selfIdCodes.begin(), selfIdCodes.end());
	codes.push_back(telecommand.getCode());
	std::vector<Code> dsMmsiCodes = distressMmsi.toCodes();
	codes.insert(codes.end(), dsMmsiCodes.begin(), dsMmsiCodes.end());
	codes.push_back(nature.getCode());
	std::vector<Code> dsCoordCodes = distressCoordinates.toCodes();
	codes.insert(codes.end(), dsCoordCodes.begin(), dsCoordCodes.end());
	std::vector<Code> dsTimeCodes = time.toCodes();
	codes.insert(codes.end(), dsTimeCodes.begin(), dsTimeCodes.end());
	codes.push_back(subsequentCommunications.getCode());
	codes.push_back(Code(Phasing::Symbol_EOS));

	codes.push_back(calculateEccFromInfoCodes(codes));
	codes.insert(codes.begin(), getFormatSpecifier().getCode());

	return codes;
}

ExpansionPosition DistressAck::getExpansion() {
	return expansionPosition;
}

std::string DistressAck::toString()
{
	std::string ret("DistressAck{");
	ret += "\nformatSpecifier=" + getFormatSpecifier().toString();
	ret += "\nselfId=" + getSelfId().toString();
	ret += "\ncategory=" + category.toString();
	ret += "\ntelecommand=" + telecommand.toString();
	ret += "\ndistressMmsi=" + distressMmsi.toString();
	ret += "\nnature=" + nature.toString();
	ret += "\ndistressCoordinates=" + distressCoordinates.toString();
	ret += "\ntime=" + time.toString();
	ret += "\nsubsequentCommunications=" + subsequentCommunications.toString();
	ret += "\nexpansion=" + expansionPosition.toString();
	ret += "\neos=" + getEos().toString();
	ret += "\n}";

	return ret;
}