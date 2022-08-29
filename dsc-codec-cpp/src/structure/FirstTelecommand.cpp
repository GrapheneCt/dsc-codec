#include <string>

#include "common.h"
#include "entities/Code.h"
#include "structure/FirstTelecommand.h"

FirstTelecommand::FirstTelecommand()
{

}

FirstTelecommand::FirstTelecommand(Code code)
{
	this->code = code;
}

FirstTelecommand::~FirstTelecommand()
{

}

Code FirstTelecommand::getCode()
{
	return code;
}

FirstTelecommand FirstTelecommand::fromSymbol(int symbol)
{
	int validSyms[] = { FirstTelecommand::Symbol_F3E_G3E_ALL_MODES_TP, FirstTelecommand::Symbol_F3E_G3E_DUPLEX_TP,
	FirstTelecommand::Symbol_POLLING, FirstTelecommand::Symbol_UNABLE_TO_COMPLY, FirstTelecommand::Symbol_END_OF_CALL,
	FirstTelecommand::Symbol_DATA, FirstTelecommand::Symbol_J3E_TP, FirstTelecommand::Symbol_DISTRESS_ACK,
	FirstTelecommand::Symbol_DISTRESS_RELAY, FirstTelecommand::Symbol_F1B_J2B_TTY_FEC, FirstTelecommand::Symbol_F1B_J2B_TTY_ARQ,
	FirstTelecommand::Symbol_TEST,  FirstTelecommand::Symbol_SHIP_POSITION, FirstTelecommand::Symbol_NO_INFO };

	for (int i = 0; i < sizeof(validSyms) / sizeof(int); i++) {
		if (symbol == validSyms[i]) {
			return FirstTelecommand(Code(symbol));
		}
	}

	DSCD_PRINTF("Failed to find first telecommand for specified symbol: %d\n", symbol);
	DSCD_ABORT();

	return FirstTelecommand(Code(FirstTelecommand::Symbol_NO_INFO));
}

std::string FirstTelecommand::toString()
{
	switch (code.getSymbol()) {
	case FirstTelecommand::Symbol_F3E_G3E_ALL_MODES_TP:
		return "F3E/G3E All modes TP";
	case FirstTelecommand::Symbol_F3E_G3E_DUPLEX_TP:
		return "F3E/G3E duplex TP";
	case FirstTelecommand::Symbol_POLLING:
		return "Polling";
	case FirstTelecommand::Symbol_UNABLE_TO_COMPLY:
		return "Unable to comply";
	case FirstTelecommand::Symbol_END_OF_CALL:
		return "End of call";
	case FirstTelecommand::Symbol_DATA:
		return "Data";
	case FirstTelecommand::Symbol_J3E_TP:
		return "J3E TP";
	case FirstTelecommand::Symbol_DISTRESS_ACK:
		return "Distress acknowledgement";
	case FirstTelecommand::Symbol_DISTRESS_RELAY:
		return "Distress relay";
	case FirstTelecommand::Symbol_F1B_J2B_TTY_FEC:
		return "F1B/J2B TTY-FEC";
	case FirstTelecommand::Symbol_F1B_J2B_TTY_ARQ:
		return "F1B/J2B TTY-ARQ";
	case FirstTelecommand::Symbol_TEST:
		return "Test";
	case FirstTelecommand::Symbol_SHIP_POSITION:
		return "Ship position or location registration updating";
	case FirstTelecommand::Symbol_NO_INFO:
		return "No information";
	default:
		DSCD_PRINTF("FirstTelecommand %d is invalid\n", code.getSymbol());
		DSCD_ABORT();
		break;
	}

	return "";
}