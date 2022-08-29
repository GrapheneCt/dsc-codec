#include "common.h"
#include "entities/Transmittable.h"
#include "entities/PstnNumber.h"

PstnNumber::PstnNumber()
{

}

PstnNumber::PstnNumber(std::string number)
{
	if (!checkFormat(number)) {
		DSCD_PRINTF("PSTN must contain numbers. TX: %s with size of %d\n", number.c_str(), number.length());
		DSCD_ABORT();
	}

	this->number = number;
}

PstnNumber PstnNumber::fromCodes(std::vector<Code> codes)
{
	//std::string number = codes.stream().reduce("", (c1, c2)->c1 + c2.getSymbol(), (c1, c2)->c1 + c2);
	DSCD_PRINTF("PstnNumber::fromCodes() is not implemented. PSTN will be set to 0\n");

	return PstnNumber("0000000000000000");
}

std::vector<Code> PstnNumber::toCodes()
{
	std::vector<Code> codes;

	/*
	StringBuilder builder = new StringBuilder(number);
	// Если размер меньше 16, то необходимо дополнить его нулями спереди
	int numLength = number.length();
	if (numLength < 16) {
		while (builder.length() != 16) {
			builder.insert(0, "0");
		}
	}

	String[] numArray = builder.toString().split("(?<=\\G..)");

	for (String s : numArray) {
		codes.add(new Code(Integer.parseInt(s)));
	}
	*/

	DSCD_PRINTF("PstnNumber::toCodes() is not implemented. PSTN will be set to 0\n");

	for (int i = 0; i < 8; i++)
	{
		codes.push_back(Code(0));
	}

	return codes;
}

std::string PstnNumber::toString()
{
	if (number == "0000000000000000") {
		return "PstnNumber{EMPTY}";
	}

	return "PstnNumber{" + number + "}";
}


bool PstnNumber::checkFormat(std::string num)
{
	return (num.find_first_not_of("0123456789") == std::string::npos);
}