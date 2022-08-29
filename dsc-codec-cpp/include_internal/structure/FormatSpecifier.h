#pragma once

#include <string>

#include "entities/Code.h"

/** @author AlexeyVorobyev */
class FormatSpecifier
{
public:

	enum Symbol
	{
		Symbol_GEOGRAPHICAL_AREA = 102,
		Symbol_DISTRESS = 112,
		Symbol_COMMON_INTEREST = 114,
		Symbol_ALL_SHIPS = 116,
		Symbol_INDIVIDUAL = 120,
		Symbol_RESERVED = 121,
		Symbol_IDIVIDUAL_SEMI_AUTOMATIC = 123
	};

	FormatSpecifier();
	FormatSpecifier(Code code);
	~FormatSpecifier();

	Code getCode();

	static FormatSpecifier fromSymbol(int symbol);

	std::string toString();

private:

	Code code;
};
