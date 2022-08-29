#include "entities/Code.h"
#include "structure/DistressNature.h"

DistressNature::DistressNature()
{

}

DistressNature::DistressNature(Code code)
{
	this->code = code;
}

DistressNature::~DistressNature()
{

}

Code DistressNature::getCode()
{
	return code;
}

DistressNature DistressNature::fromSymbol(int symbol)
{
	int validSyms[] = { DistressNature::Symbol_FIRE_EXPLOSION, DistressNature::Symbol_FLOODING,
	DistressNature::Symbol_COLLISION, DistressNature::Symbol_GROUNDING, 
	DistressNature::Symbol_LISTING, DistressNature::Symbol_SINKING,
	DistressNature::Symbol_DISABLED_AND_ADRIFT, DistressNature::Symbol_UNDESIGNATED,
	DistressNature::Symbol_ABANDONING_SHIP, DistressNature::Symbol_PIRACY,
	DistressNature::Symbol_MAN_OVERBOARD, DistressNature::Symbol_EPIRB_EMISSION };

	for (int i = 0; i < sizeof(validSyms) / sizeof(int); i++) {
		if (symbol == validSyms[i]) {
			return DistressNature(Code(symbol));
		}
	}

	printf("Failed to find distress nature for specified symbol: %d\n", symbol);
	abort();

	return DistressNature(Code(DistressNature::Symbol_UNDESIGNATED));
}

std::string DistressNature::toString()
{
	switch (code.getSymbol()) {
	case DistressNature::Symbol_FIRE_EXPLOSION: return "Fire, explosion";
	case DistressNature::Symbol_FLOODING: return "Flooding";
	case DistressNature::Symbol_COLLISION: return "Collision";
	case DistressNature::Symbol_GROUNDING: return "Grounding";
	case DistressNature::Symbol_LISTING: return "Listing, in danger of capsizing";
	case DistressNature::Symbol_SINKING: return "Sinking";
	case DistressNature::Symbol_DISABLED_AND_ADRIFT: return "Disabled and adrift";
	case DistressNature::Symbol_UNDESIGNATED: return "Undesignated distress";
	case DistressNature::Symbol_ABANDONING_SHIP: return "Abandoning ship";
	case DistressNature::Symbol_PIRACY: return "Piracy/armed robbery attack";
	case DistressNature::Symbol_MAN_OVERBOARD: return "Man overboard";
	case DistressNature::Symbol_EPIRB_EMISSION: return "EPIRB emission";
	default:
		printf("Distress %d is invalid\n", code.getSymbol());
		abort();
		break;
	}

	return "";
}