#include "entities/Mmsi.h"
#include "entities/Address.h"

Mmsi Mmsi::fromCodes(std::vector<Code> codes)
{
	long long temp;

	temp = codes[0].getSymbol() * 100000000ll;
	temp += codes[1].getSymbol() * 1000000ll;
	temp += codes[2].getSymbol() * 10000ll;
	temp += codes[3].getSymbol() * 100ll;
	temp += codes[4].getSymbol();
	temp /= 10;

	return Mmsi(temp);
}

Mmsi::Mmsi()
{
	this->value = 0;
}

Mmsi::Mmsi(long long value)
{
	this->value = value;
}

Mmsi::~Mmsi()
{

}

long long Mmsi::getValue()
{
	return value;
}

std::vector<Code> Mmsi::toCodes()
{
	std::vector<Code> codes;

	long long tempMid = value;
	int divider = 10000000;
	for (int i = 0; i < 4; i++) {
		long long temp = tempMid / divider;
		tempMid -= temp * divider;
		codes.push_back(Code((int)temp));
		divider /= 100;
	}
	tempMid *= 10;

	codes.push_back(Code((int)tempMid));

	return codes;
}

std::string Mmsi::toString()
{
	if (value == 0) {
		return "Mmsi{EMPTY}";
	}

	char llbuffer[256];
	snprintf(llbuffer, sizeof(llbuffer), "%lld", value);

	std::string ret("Mmsi{");
	ret += llbuffer;
	ret += "}";

	return ret;
}