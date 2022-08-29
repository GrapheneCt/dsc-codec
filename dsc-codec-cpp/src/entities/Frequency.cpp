#include <vector>

#include "entities/Transmittable.h"
#include "entities/Frequency.h"

Frequency::Frequency()
{
	this->value = 0;
}

Frequency::Frequency(int value)
{
	this->value = value;
}

int Frequency::getValue()
{
	return value;
}

std::vector<Code> Frequency::toCodes()
{
	std::vector<Code> signs;

	long f = value;

	int divider = 10000;
	for (int i = 0; i < 3; i++) {
		int temp = (int)(f / divider);
		f -= temp * divider;
		signs.push_back(Code(temp));
		divider /= 100;
	}

	return signs;
}

Frequency Frequency::fromCodes(std::vector<Code> codes)
{
	int frequency = codes[0].getSymbol() * 10000 +
		codes[1].getSymbol() * 100 + codes[2].getSymbol();

	frequency *= 100;

	return Frequency(frequency);
}

std::vector<Code> Frequency::getNoInfoCodes()
{
	std::vector<Code> codes;

	codes.push_back(Code(126));
	codes.push_back(Code(126));
	codes.push_back(Code(126));

	return codes;
}

std::string Frequency::toString()
{
	if (value == 0) {
		return "EMPTY";
	}

	char str[256];
	snprintf(str, sizeof(str), "%d Hz", value);

	return str;
}
