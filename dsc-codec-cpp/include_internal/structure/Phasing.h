#pragma once

#include "entities/Code.h"

/** @author AlexeyVorobyev */
class Phasing
{
public:

	enum Symbol
	{
		Symbol_RX0 = 104,
		Symbol_RX1 = 105,
		Symbol_RX2 = 106,
		Symbol_RX3 = 107,
		Symbol_RX4 = 108,
		Symbol_RX5 = 109,
		Symbol_RX6 = 110,
		Symbol_RX7 = 111,
		Symbol_EOS_ACK_RQ = 117,
		Symbol_EOS_ACK_BQ = 122,
		Symbol_DX = 125,
		Symbol_EOS = 127
	};

	static bool isEOS(Phasing p);

	static bool isEOS(Code code);

	static Phasing *getRxes();

	static bool isRx(Code p);

	static bool isDx(Code p);

	static Phasing fromSymbol(int symbol);

	Phasing();
	Phasing(Code code);

	Code getCode();

	std::string toString();

private:

	Code code;
};
