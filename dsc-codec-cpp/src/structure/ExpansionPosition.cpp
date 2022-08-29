#include <string>

#include "entities/Transmittable.h"
#include "entities/Code.h"
#include "structure/ExpansionPosition.h"

ExpansionPosition::ExpansionPosition()
{
	this->expansionSpecifier = 999;
}

ExpansionPosition::ExpansionPosition(std::string enhancedLatitude,
	std::string enhancedLongitude)
{
	this->expansionSpecifier = 100;
	this->enhancedLatitude = enhancedLatitude;
	this->enhancedLongitude = enhancedLongitude;
}

ExpansionPosition::~ExpansionPosition()
{

}

int ExpansionPosition::getExpansionSpecifier()
{
	return expansionSpecifier;
}

std::string ExpansionPosition::getEnhancedLatitude()
{
	return enhancedLatitude;
}

std::string ExpansionPosition::getEnhancedLongitude()
{
	return enhancedLongitude;
}

ExpansionPosition ExpansionPosition::fromCodes(std::vector<Code> codes)
{
	std::string latitude = "";
	std::string longitude = "";
	char str[33];

	int latTmp = codes[0].getSymbol() + codes[1].getSymbol();
	int longTmp = codes[2].getSymbol() + codes[3].getSymbol();

	snprintf(str, sizeof(str), "%d", latTmp);
	latitude += str;
	snprintf(str, sizeof(str), "%d", longTmp);
	longitude += str;

	return ExpansionPosition(latitude, longitude);
}

std::string ExpansionPosition::toString()
{
	if (expansionSpecifier == 999) {
		return "ExpansionPosition{EMPTY}";
	}

	char str[33];

	std::string ret("ExpansionPosition{");
	snprintf(str, sizeof(str), "%d", expansionSpecifier);
	ret += str;
	ret += ", enhancedLatitude='" + enhancedLatitude + "\', enhancedLongitude='" + enhancedLongitude + "\'}";

	return ret;
}

std::vector<Code> ExpansionPosition::toCodes()
{
	std::vector<Code> codes;
	const char *celat = enhancedLatitude.c_str();
	const char *celong = enhancedLongitude.c_str();
	char tmp1[3];
	char tmp2[3];
	tmp1[2] = 0;
	tmp2[2] = 0;

	// Спецификатор расширенной последовательности
	codes.push_back(Code(100));

	tmp1[0] = celat[0];
	tmp1[1] = celat[1];
	tmp2[0] = celat[2];
	tmp2[1] = celat[3];
	codes.push_back(Code(atoi(tmp1)));
	codes.push_back(Code(atoi(tmp2)));

	tmp1[0] = celong[0];
	tmp1[1] = celong[1];
	tmp2[0] = celong[2];
	tmp2[1] = celong[3];
	codes.push_back(Code(atoi(tmp1)));
	codes.push_back(Code(atoi(tmp2)));

	return codes;
}