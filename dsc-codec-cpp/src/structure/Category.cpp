#include "entities/Code.h"
#include "structure/Category.h"

Category::Category()
{

}

Category::Category(Code code)
{
	this->code = code;
}

Code Category::getCode()
{
	return code;
}

Category Category::fromSymbol(int symbol)
{
	int validSyms[] = { Category::Symbol_ROUTINE, Category::Symbol_SAFETY, Category::Symbol_URGENCY, Category::Symbol_DISTRESS };

	for (int i = 0; i < sizeof(validSyms) / sizeof(int); i++) {
		if (symbol == validSyms[i]) {
			return Category(Code(symbol));
		}
	}

	printf("Failed to find phasing for specified symbol: %d\n", symbol);
	abort();

	return Category(Code(Category::Symbol_ROUTINE));
}

std::string Category::toString()
{
	switch (code.getSymbol()) {
	case Category::Symbol_ROUTINE: return "Routine";
	case Category::Symbol_SAFETY: return "Safety";
	case Category::Symbol_URGENCY: return "Urgency";
	case Category::Symbol_DISTRESS: return "Distress";
	default:
		printf("��������� %d �� ����������\n", code.getSymbol());
		abort();
		break;
	}

	return "Routine";
}