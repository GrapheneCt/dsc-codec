#include <string>
#include <vector>

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "DigitalSelectiveCall.h"
#include "routine/RoutineGroup.h"

RoutineGroup::RoutineGroup(Mmsi selfId, Mmsi address,
	FirstTelecommand firstTelecommand,
	Frequency frequencyRx,
	Frequency frequencyTx) :
	DigitalSelectiveCall(FormatSpecifier(Code(FormatSpecifier::Symbol_COMMON_INTEREST)), Phasing(Code(Phasing::Symbol_EOS)), selfId)
{
	this->address = address;
	this->firstTelecommand = firstTelecommand;
	this->frequencyRx = frequencyRx;
	this->frequencyTx = frequencyTx;
	this->hasFrequencyTx = false;

	this->category = Category(Code(Category::Symbol_ROUTINE));
	this->secondTelecommand = SecondTelecommand(Code(SecondTelecommand::Symbol_NO_INFO));

	if (this->frequencyTx.getValue() == 0) {
		this->hasFrequencyTx = true;
	}
}

std::vector<Code> RoutineGroup::toCodes()
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
	std::vector<Code> frxCodes = frequencyRx.toCodes();
	codes.insert(codes.end(), frxCodes.begin(), frxCodes.end());

	std::vector<Code> ftxCodes;
	if (hasFrequencyTx)
		ftxCodes = frequencyTx.toCodes();
	else
		ftxCodes = Frequency::getNoInfoCodes();

	codes.push_back(getEos().getCode());
	codes.push_back(calculateEccFromInfoCodes(codes));
	codes.insert(codes.begin(), getFormatSpecifier().getCode());

	return codes;
}

Mmsi RoutineGroup::getAddress() {
	return address;
}

Category RoutineGroup::getCategory() {
	return category;
}

FirstTelecommand RoutineGroup::getFirstTelecommand() {
	return firstTelecommand;
}

SecondTelecommand RoutineGroup::getSecondTelecommand() {
	return secondTelecommand;
}

Frequency RoutineGroup::getFrequencyRx() {
	return frequencyRx;
}

Frequency RoutineGroup::getFrequencyTx() {
	return frequencyTx;
}

std::string RoutineGroup::toString()
{
	std::string ret("RoutineGroup{");
	ret += "\nformatSpecifier=" + getFormatSpecifier().toString();
	ret += "\nselfId=" + getSelfId().toString();
	ret += "\naddress=" + address.toString();
	ret += "\ncategory=" + getCategory().toString();
	ret += "\nfirstTelecommand=" + getFirstTelecommand().toString();
	ret += "\nsecondTelecommand=" + getSecondTelecommand().toString();
	ret += "\nfrequencyRx=" + getFrequencyRx().toString();
	ret += "\nfrequencyTx=" + getFrequencyTx().toString();
	ret += "\neos=" + getEos().toString();
	ret += "\n}";

	return ret;
}