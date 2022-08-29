#pragma once

#include "entities/Code.h"

/** @author AlexeyVorobyev */
class Category
{
public:

	enum Symbol
	{
		Symbol_ROUTINE = 100,
		Symbol_SAFETY = 108,
		Symbol_URGENCY = 110,
		Symbol_DISTRESS = 112
	};

	Category();
	Category(Code code);

	Code getCode();
	std::string toString();

	static Category fromSymbol(int symbol);

private:

	Code code;

};