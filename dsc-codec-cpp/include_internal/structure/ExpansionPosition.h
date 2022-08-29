#pragma once

#include <string>

#include "entities/Transmittable.h"
#include "entities/Code.h"

/** @author AlexeyVorobyev */
class ExpansionPosition : public Transmittable
{
public:

	ExpansionPosition();
	ExpansionPosition(std::string enhancedLatitude,
		std::string enhancedLongitude);
	~ExpansionPosition();

	int getExpansionSpecifier();

	std::string getEnhancedLatitude();
	std::string getEnhancedLongitude();

	static ExpansionPosition fromCodes(std::vector<Code> codes);

	std::string toString();
	std::vector<Code> toCodes();

private:

	int expansionSpecifier;
	std::string enhancedLatitude;
	std::string enhancedLongitude;
};
