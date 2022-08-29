#include <string>
#include <vector>

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "DigitalSelectiveCall.h"
#include "SemiAutoCall.h"
#include "DscMarkers.h"
#include "semiAuto/SemiAutoMfHf.h"

SemiAutoMfHf::SemiAutoMfHf(Mmsi selfId, Mmsi address,
	FirstTelecommand ft, SecondTelecommand st,
	PstnNumber number, Frequency rxFrequency,
	Frequency txFrequency,
	Coordinates pos) :
	SemiAutoCall(Phasing(Code(Phasing::Symbol_EOS_ACK_RQ)), selfId, address, ft, st, number)
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

std::vector<Code> SemiAutoMfHf::getAdditionalCodes()
{
	std::vector<Code> codes;

	std::vector<Code> frxCodes;
	if (hasFrequencyRx) {
		frxCodes = rxFrequency.toCodes();
		codes.insert(codes.end(), frxCodes.begin(), frxCodes.end());
	}
	else if (hasCoordinates) {
		// Маркер координат
		codes.push_back(Code(DscMarkers::posMarker));
		std::vector<Code> posCodes = pos.toCodes();
		codes.insert(codes.end(), posCodes.begin(), posCodes.end());
	}
	else {
		frxCodes = Frequency::getNoInfoCodes();
		codes.insert(codes.end(), frxCodes.begin(), frxCodes.end());
	}

	std::vector<Code> ftxCodes;
	if (hasFrequencyTx)
		ftxCodes = txFrequency.toCodes();
	else
		ftxCodes = Frequency::getNoInfoCodes();
	codes.insert(codes.end(), ftxCodes.begin(), ftxCodes.end());

	return codes;
}

std::string SemiAutoMfHf::toString()
{
	std::string ret("SemiAutoMfHf{");
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