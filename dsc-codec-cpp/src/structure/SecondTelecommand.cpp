#include <string>

#include "entities/Code.h"
#include "structure/SecondTelecommand.h"

SecondTelecommand::SecondTelecommand()
{

}

SecondTelecommand::SecondTelecommand(Code code)
{
	this->code = code;
}

SecondTelecommand::~SecondTelecommand()
{

}

Code SecondTelecommand::getCode()
{
	return code;
}

SecondTelecommand SecondTelecommand::fromSymbol(int symbol)
{
	int validSyms[] = { SecondTelecommand::Symbol_NO_REASON_GIVEN, SecondTelecommand::Symbol_CONGESTION_AT_MARITIME_SWITCHIN_CENTER,
	SecondTelecommand::Symbol_BUSY, SecondTelecommand::Symbol_QUEUE_INDICATOR, SecondTelecommand::Symbol_STATION_BARRED,
	SecondTelecommand::Symbol_NO_OPERATOR_AVAILABLE, SecondTelecommand::Symbol_OPERATOR_TEMPORARILY_UNAVAILABLE,
	SecondTelecommand::Symbol_EQUIPMENT_DISABLED, SecondTelecommand::Symbol_UNABLE_TO_USE_PROPOSED_CHANNEL,
	SecondTelecommand::Symbol_UNABLE_TO_USE_PROPOSED_MODE, SecondTelecommand::Symbol_NOT_PARTIES_OF_ARMED_CONFLICT,
	SecondTelecommand::Symbol_MEDICAL_TRANSPORTS, SecondTelecommand::Symbol_PAY_PHONE_PUBLIC_CALL_OFFICE,
	SecondTelecommand::Symbol_FACSIMILE, SecondTelecommand::Symbol_NO_INFO };

	for (int i = 0; i < sizeof(validSyms) / sizeof(int); i++) {
		if (symbol == validSyms[i]) {
			return SecondTelecommand(Code(symbol));
		}
	}

	printf("Failed to find second telecommand for specified symbol: %d\n", symbol);
	abort();

	return SecondTelecommand(Code(SecondTelecommand::Symbol_NO_INFO));
}

std::string SecondTelecommand::toString()
{
	switch (code.getSymbol()) {
	case SecondTelecommand::Symbol_NO_REASON_GIVEN:
		return "No reason given";
	case SecondTelecommand::Symbol_CONGESTION_AT_MARITIME_SWITCHIN_CENTER:
		return "Congestion at maritime switching centre";
	case SecondTelecommand::Symbol_BUSY:
		return "Busy";
	case SecondTelecommand::Symbol_QUEUE_INDICATOR:
		return "Queue indication";
	case SecondTelecommand::Symbol_STATION_BARRED:
		return "Station barred";
	case SecondTelecommand::Symbol_NO_OPERATOR_AVAILABLE:
		return "No operator available";
	case SecondTelecommand::Symbol_OPERATOR_TEMPORARILY_UNAVAILABLE:
		return "Operator temporarily unavailable";
	case SecondTelecommand::Symbol_EQUIPMENT_DISABLED:
		return "Equipmet disabled";
	case SecondTelecommand::Symbol_UNABLE_TO_USE_PROPOSED_CHANNEL:
		return "Unable to use proposed channel";
	case SecondTelecommand::Symbol_UNABLE_TO_USE_PROPOSED_MODE:
		return "Unable to use proposed mode";
	case SecondTelecommand::Symbol_NOT_PARTIES_OF_ARMED_CONFLICT:
		return "Ships and aircraft of States not parties to an armed conflict";
	case SecondTelecommand::Symbol_MEDICAL_TRANSPORTS:
		return "Medical transports";
	case SecondTelecommand::Symbol_PAY_PHONE_PUBLIC_CALL_OFFICE:
		return "Pay-phone/public call office";
	case SecondTelecommand::Symbol_FACSIMILE:
		return "Facsimile/data according to Recommendation ITU-R M.1081";
	case SecondTelecommand::Symbol_NO_INFO:
		return "No information";
	default:
		printf("SecondTelecommand %d is invalid\n", code.getSymbol());
		abort();
		break;
	}

	return "";
}