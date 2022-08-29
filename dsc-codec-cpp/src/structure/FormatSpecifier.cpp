#include <string>

#include "entities/Code.h"
#include "structure/FormatSpecifier.h"

FormatSpecifier::FormatSpecifier()
{

}

FormatSpecifier::FormatSpecifier(Code code)
{
	this->code = code;
}

FormatSpecifier::~FormatSpecifier()
{

}

Code FormatSpecifier::getCode()
{
	return code;
}

FormatSpecifier FormatSpecifier::fromSymbol(int symbol)
{
	int validSyms[] = { FormatSpecifier::Symbol_GEOGRAPHICAL_AREA, FormatSpecifier::Symbol_DISTRESS,
	FormatSpecifier::Symbol_COMMON_INTEREST, FormatSpecifier::Symbol_ALL_SHIPS, FormatSpecifier::Symbol_INDIVIDUAL,
	FormatSpecifier::Symbol_RESERVED, FormatSpecifier::Symbol_IDIVIDUAL_SEMI_AUTOMATIC };

	for (int i = 0; i < sizeof(validSyms) / sizeof(int); i++) {
		if (symbol == validSyms[i]) {
			return FormatSpecifier(Code(symbol));
		}
	}

	printf("Failed to find format specified for specified symbol: %d\n", symbol);
	abort();

	return FormatSpecifier(Code(FormatSpecifier::Symbol_INDIVIDUAL));
}

std::string FormatSpecifier::toString()
{
	switch (code.getSymbol()) {
	case FormatSpecifier::Symbol_GEOGRAPHICAL_AREA:
		return "Geographical area";
	case FormatSpecifier::Symbol_DISTRESS:
		return "Distress";
	case FormatSpecifier::Symbol_COMMON_INTEREST:
		return "Ships having common interest";
	case FormatSpecifier::Symbol_ALL_SHIPS:
		return "All ships";
	case FormatSpecifier::Symbol_INDIVIDUAL:
		return "Individual stations";
	case FormatSpecifier::Symbol_RESERVED:
		return "Reserved for national non-calling purposes e.g. Report ITU-R M.1159";
	case FormatSpecifier::Symbol_IDIVIDUAL_SEMI_AUTOMATIC:
		return "Individual station semi-automatic/automatic service";
	default:
		printf("FormatSpecifier %d is invalid\n", code.getSymbol());
		abort();
		break;
	}

	return "";
}