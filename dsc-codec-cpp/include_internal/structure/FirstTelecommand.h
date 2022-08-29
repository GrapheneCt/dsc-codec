#pragma once

#include <string>

#include "entities/Code.h"

/** @author AlexeyVorobyev */
class FirstTelecommand
{
public:

	enum Symbol
	{
		Symbol_F3E_G3E_ALL_MODES_TP = 100,
		Symbol_F3E_G3E_DUPLEX_TP = 101,
		Symbol_POLLING = 103,
		Symbol_UNABLE_TO_COMPLY = 104,
		Symbol_END_OF_CALL = 105,
		Symbol_DATA = 106,
		Symbol_J3E_TP = 109,
		Symbol_DISTRESS_ACK = 110,
		Symbol_DISTRESS_RELAY = 112,
		Symbol_F1B_J2B_TTY_FEC = 113,
		Symbol_F1B_J2B_TTY_ARQ = 115,
		Symbol_TEST = 118,
		Symbol_SHIP_POSITION = 121,
		Symbol_NO_INFO = 126
	};

	FirstTelecommand();
	FirstTelecommand(Code code);
	~FirstTelecommand();

	Code getCode();

	static FirstTelecommand fromSymbol(int symbol);

	std::string toString();

private:

	Code code;
};