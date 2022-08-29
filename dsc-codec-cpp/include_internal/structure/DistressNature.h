#pragma once

#include "entities/Code.h"

/** @author AlexeyVorobyev */
class DistressNature
{
public:

	enum Symbol
	{
		Symbol_FIRE_EXPLOSION = 100,
		Symbol_FLOODING = 101,
		Symbol_COLLISION = 102,
		Symbol_GROUNDING = 103,
		Symbol_LISTING = 104,
		Symbol_SINKING = 105,
		Symbol_DISABLED_AND_ADRIFT = 106,
		Symbol_UNDESIGNATED = 107,
		Symbol_ABANDONING_SHIP = 108,
		Symbol_PIRACY = 109,
		Symbol_MAN_OVERBOARD = 110,
		Symbol_EPIRB_EMISSION = 112
	};

	static DistressNature fromSymbol(int symbol);

	DistressNature();
	DistressNature(Code code);
	~DistressNature();

	Code getCode();

	std::string toString();

private:

	Code code;
};