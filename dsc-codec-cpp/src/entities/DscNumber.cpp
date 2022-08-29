#include <vector>
#include <stdlib.h>

#include "entities/Coordinates.h"
#include "entities/DscNumber.h"

DscNumber::DscNumber(long long number)
{
	this->number = number;
}

DscNumber::DscNumber()
{
	this->number = 0;
}

long long DscNumber::getNumber()
{
	return number;
}

std::vector<Code> DscNumber::toCodes()
{
	std::vector<Code> codes;

	char ibuffer[33];
	char tmp[3];
	tmp[2] = 0;

	snprintf(ibuffer, sizeof(ibuffer), "%lld", number);
	std::string n = ibuffer;

	const char *cstr = n.c_str();
	for (int i = 0; i < n.length(); i += 2) {
		tmp[0] = cstr[i];
		tmp[1] = cstr[i + 1];
		codes.push_back(Code(atoi(tmp)));
	}

	return codes;
}

DscNumber DscNumber::fromCodes(std::vector<Code> codes)
{
	std::string buffer;
	char str[33];

	for (Code c : codes) {
		snprintf(str, sizeof(str), "%d", c.getSymbol());
		buffer.append(str);
	}

	return DscNumber(atoll(buffer.c_str()));
}

std::string DscNumber::toString()
{
	if (number == 0) {
		return "DscNumber{ EMPTY }";
	}

	char llbuffer[256];
	snprintf(llbuffer, sizeof(llbuffer), "%lld", number);

	std::string ret("DscNumber{ number=");
	ret += llbuffer;
	ret += "}";

	return ret;
}