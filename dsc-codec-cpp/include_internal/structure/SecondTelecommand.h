#pragma once

#include "entities/Code.h"

/** @author AlexeyVorobyev */
class SecondTelecommand
{
public:

	enum Symbol
	{
		Symbol_NO_REASON_GIVEN = 100,
		Symbol_CONGESTION_AT_MARITIME_SWITCHIN_CENTER = 101,
		Symbol_BUSY = 102,
		Symbol_QUEUE_INDICATOR = 103,
		Symbol_STATION_BARRED = 104,
		Symbol_NO_OPERATOR_AVAILABLE = 105,
		Symbol_OPERATOR_TEMPORARILY_UNAVAILABLE = 106,
		Symbol_EQUIPMENT_DISABLED = 107,
		Symbol_UNABLE_TO_USE_PROPOSED_CHANNEL = 108,
		Symbol_UNABLE_TO_USE_PROPOSED_MODE = 109,
		Symbol_NOT_PARTIES_OF_ARMED_CONFLICT = 110,
		Symbol_MEDICAL_TRANSPORTS = 111,
		Symbol_PAY_PHONE_PUBLIC_CALL_OFFICE = 112,
		Symbol_FACSIMILE = 113,
		Symbol_NO_INFO = 126
	};

	SecondTelecommand();
	SecondTelecommand(Code code);
	~SecondTelecommand();

	Code getCode();

	static SecondTelecommand fromSymbol(int symbol);

	std::string toString();

private:

	Code code;
};