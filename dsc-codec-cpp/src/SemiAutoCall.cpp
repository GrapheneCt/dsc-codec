#include <string>
#include <vector>

#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "entities/PstnNumber.h"
#include "DigitalSelectiveCall.h"
#include "DscMarkers.h"
#include "SemiAutoCall.h"

SemiAutoCall::SemiAutoCall(Phasing eos, Mmsi selfId, Mmsi address,
	FirstTelecommand firstTelecommand,
	SecondTelecommand secondTelecommand,
	PstnNumber pstnNumber) :
	DigitalSelectiveCall(FormatSpecifier(Code(FormatSpecifier::Symbol_IDIVIDUAL_SEMI_AUTOMATIC)), eos, selfId)
{
	this->address = address;
	this->firstTelecommand = firstTelecommand;
	this->secondTelecommand = secondTelecommand;
	this->pstnNumber = pstnNumber;
	this->category = Category(Category::Symbol_ROUTINE);
}

std::vector<Code> SemiAutoCall::toCodes()
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

	std::vector<Code> addCodes = getAdditionalCodes();
	codes.insert(codes.end(), addCodes.begin(), addCodes.end());

	// Addinf of PSTN number
	codes.push_back(Code(DscMarkers::pstnMarker));

	std::vector<Code> pstnCodes = pstnNumber.toCodes();
	codes.insert(codes.end(), pstnCodes.begin(), pstnCodes.end());

	codes.push_back(getEos().getCode());

	codes.push_back(calculateEccFromInfoCodes(codes));

	codes.insert(codes.begin(), getFormatSpecifier().getCode());

	return codes;
}

Mmsi SemiAutoCall::getAddress()
{
	return address;
}

Category SemiAutoCall::getCategory()
{
	return category;
}

FirstTelecommand SemiAutoCall::getFirstTelecommand()
{
	return firstTelecommand;
}

SecondTelecommand SemiAutoCall::getSecondTelecommand()
{
	return secondTelecommand;
}

PstnNumber SemiAutoCall::getPstnNumber()
{
	return pstnNumber;
}