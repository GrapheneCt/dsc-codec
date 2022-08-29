#include <string>
#include <vector>

#include "common.h"
#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "entities/Mmsi.h"
#include "entities/TimeUTC.h"
#include "structure/Category.h"
#include "structure/DistressNature.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "DigitalSelectiveCall.h"
#include "distress/Distress.h"

Distress::Distress(Mmsi selfId, DistressNature nature,
	Coordinates coordinates, TimeUTC distressTime,
	FirstTelecommand subsequentCommunication) :
	DigitalSelectiveCall(FormatSpecifier(Code(FormatSpecifier::Symbol_DISTRESS)), Phasing(Code(Phasing::Symbol_EOS)), selfId)
{
	int subsequentCommunicationSymbol = subsequentCommunication.getCode().getSymbol();

	if (subsequentCommunicationSymbol == FirstTelecommand::Symbol_F3E_G3E_ALL_MODES_TP ||
		subsequentCommunicationSymbol == FirstTelecommand::Symbol_J3E_TP ||
		subsequentCommunicationSymbol == FirstTelecommand::Symbol_F1B_J2B_TTY_FEC ||
		subsequentCommunicationSymbol == FirstTelecommand::Symbol_NO_INFO) {
		this->nature = nature;
		this->coordinates = coordinates;
		this->distressTime = distressTime;
		this->subsequentCommunication = subsequentCommunication;
		this->hasExpansionPosition = false;
	}
	else {
		DSCD_PRINTF("Unknown subsequent communication type: %d\n", subsequentCommunicationSymbol);
		DSCD_ABORT();
	}
}

Distress::Distress(Mmsi selfId, DistressNature nature,
	Coordinates coordinates, TimeUTC distressTime,
	FirstTelecommand subsequentCommunication,
	ExpansionPosition expansionPosition) :
	DigitalSelectiveCall(FormatSpecifier(Code(FormatSpecifier::Symbol_DISTRESS)), Phasing(Code(Phasing::Symbol_EOS)), selfId)
{

	int subsequentCommunicationSymbol = subsequentCommunication.getCode().getSymbol();

	if (subsequentCommunicationSymbol == FirstTelecommand::Symbol_F3E_G3E_ALL_MODES_TP ||
		subsequentCommunicationSymbol == FirstTelecommand::Symbol_J3E_TP ||
		subsequentCommunicationSymbol == FirstTelecommand::Symbol_F1B_J2B_TTY_FEC ||
		subsequentCommunicationSymbol == FirstTelecommand::Symbol_NO_INFO) {
		this->nature = nature;
		this->coordinates = coordinates;
		this->distressTime = distressTime;
		this->subsequentCommunication = subsequentCommunication;
		this->expansionPosition = expansionPosition;
		this->hasExpansionPosition = true;
	}
	else {
		DSCD_PRINTF("Unknown subsequent communication type: %d\n", subsequentCommunicationSymbol);
		DSCD_ABORT();
	}
}

/** @see DigitalSelectiveCall#toCodes() */
std::vector<Code> Distress::toCodes()
{
	std::vector<Code> codes;

	codes.push_back(getFormatSpecifier().getCode());
	std::vector<Code> selfIdCodes = getSelfId().toCodes();
	codes.insert(codes.end(), selfIdCodes.begin(), selfIdCodes.end());
	codes.push_back(nature.getCode());
	std::vector<Code> dsCoordCodes = coordinates.toCodes();
	codes.insert(codes.end(), dsCoordCodes.begin(), dsCoordCodes.end());
	std::vector<Code> dsTimeCodes = distressTime.toCodes();
	codes.insert(codes.end(), dsTimeCodes.begin(), dsTimeCodes.end());
	codes.push_back(subsequentCommunication.getCode());
	codes.push_back(Code(Phasing::Symbol_EOS));

	codes.push_back(calculateEccFromInfoCodes(codes));
	codes.insert(codes.begin(), getFormatSpecifier().getCode());

	return codes;
}

std::string Distress::toString()
{
	std::string ret("Distress{");
	ret += "\nformatSpecifier=" + getFormatSpecifier().toString();
	ret += "\nselfId=" + getSelfId().toString();
	ret += "\nnature=" + nature.toString();
	ret += "\ncoordinates=" + coordinates.toString();
	ret += "\ndistressTime=" + distressTime.toString();
	ret += "\nsubsequentCommunication=" + subsequentCommunication.toString();
	ret += "\nexpansion=" + expansionPosition.toString();
	ret += "\neos=" + getEos().toString();
	ret += "\n}";

	return ret;
}

ExpansionPosition Distress::getExpansion() {
	return expansionPosition;
}

DistressNature Distress::getNature() {
	return nature;
}

Coordinates Distress::getCoordinates() {
	return coordinates;
}

TimeUTC Distress::getDistressTime() {
	return distressTime;
}

FirstTelecommand Distress::getSubsequentCommunication() {
	return subsequentCommunication;
}