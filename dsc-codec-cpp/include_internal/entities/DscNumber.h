#pragma once

#include <vector>
#include <sstream>

#include "entities/Coordinates.h"

/**
 * Целое число.
 *
 * @author AlexeyVorobyev
 */
class DscNumber : public Transmittable
{
public:

	DscNumber();
	DscNumber(long long number);

	long long getNumber();
	std::vector<Code> toCodes();
	std::string toString();

	static DscNumber fromCodes(std::vector<Code> codes);

private:

	long long number;
};
