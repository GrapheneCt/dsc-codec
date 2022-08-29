#include <string>
#include <vector>

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "DigitalSelectiveCall.h"
#include "SemiAutoCall.h"
#include "semiAuto/SemiAutoMfHfAck.h"

SemiAutoMfHfAck::SemiAutoMfHfAck(Mmsi selfId, Mmsi address,
	FirstTelecommand ft, SecondTelecommand st,
	PstnNumber number, Frequency rxFrequency,
	Frequency txFrequency,
	Coordinates pos) :
	SemiAutoCall(Phasing(Code(Phasing::Symbol_EOS_ACK_BQ)), selfId, address, ft, st, number)
{
	this->rxFrequency = rxFrequency;
	this->txFrequency = txFrequency;
	this->pos = pos;
	this->hasFrequencyRx = false;
	this->hasFrequencyTx = false;
	this->hasCoordinates = false;

	if (this->txFrequency.getValue() != 0) {
		this->hasFrequencyTx = true;
	}

	if (this->rxFrequency.getValue() != 0) {
		this->hasFrequencyRx = true;
	}

	if (this->pos.getLatitude() != "9999" &&
		this->pos.getLongitude() != "99999") {
		this->hasCoordinates = true;
	}
}

std::vector<Code> SemiAutoMfHfAck::getAdditionalCodes()
{
	std::vector<Code> codes;

	std::vector<Code> tmpCodes;
	if (hasFrequencyRx) {
		tmpCodes = rxFrequency.toCodes();
	}
	else if (hasCoordinates) {
		tmpCodes = pos.toCodes();
	}
	else {
		tmpCodes = Frequency::getNoInfoCodes();
	}

	codes.insert(codes.end(), tmpCodes.begin(), tmpCodes.end());

	if (hasFrequencyTx) {
		tmpCodes = txFrequency.toCodes();
		codes.insert(codes.end(), tmpCodes.begin(), tmpCodes.end());
	}
	else if (!hasCoordinates) {
		tmpCodes = Frequency::getNoInfoCodes();
		codes.insert(codes.end(), tmpCodes.begin(), tmpCodes.end());
	}

	return codes;
}

std::string SemiAutoMfHfAck::toString()
{
	std::string ret("SemiAutoMfHfAck{");
	ret += "\naddress=" + getAddress().toString();
	ret += "\ncategory=" + getCategory().toString();
	ret += "\nfirstTelecommand=" + getFirstTelecommand().toString();
	ret += "\nsecondTelecommand=" + getSecondTelecommand().toString();
	ret += "\nrxFrequency=" + rxFrequency.toString();
	ret += "\ntxFrequency=" + txFrequency.toString();
	ret += "\npos=" + pos.toString();
	ret += "\nnumber=" + getPstnNumber().toString();
	ret += "\n}";

	return ret;
}