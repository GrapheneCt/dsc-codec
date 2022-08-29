#include <cstddef>
#include <vector>

#include "structure/Phasing.h"

bool Phasing::isEOS(Phasing p)
{
	int symbol = p.getCode().getSymbol();
	return (symbol == Phasing::Symbol_EOS ||
		symbol == Phasing::Symbol_EOS_ACK_BQ ||
		symbol == Phasing::Symbol_EOS_ACK_RQ);
}

bool Phasing::isEOS(Code code)
{
	int symbol = code.getSymbol();
	return (symbol == Phasing::Symbol_EOS ||
		symbol == Phasing::Symbol_EOS_ACK_BQ ||
		symbol == Phasing::Symbol_EOS_ACK_RQ);
}

bool Phasing::isRx(Code p)
{
	int s = p.getSymbol();
	return (s == Phasing::Symbol_RX0 || s == Phasing::Symbol_RX1 || s == Phasing::Symbol_RX2 || s == Phasing::Symbol_RX3 ||
		s == Phasing::Symbol_RX4 || s == Phasing::Symbol_RX5 ||s == Phasing::Symbol_RX6 || s == Phasing::Symbol_RX7);
}

bool Phasing::isDx(Code p)
{
	return (p.getSymbol() == Phasing::Symbol_DX);
}

Phasing Phasing::fromSymbol(int symbol)
{
	int validSyms[] = { Phasing::Symbol_RX0, Phasing::Symbol_RX1, Phasing::Symbol_RX2, Phasing::Symbol_RX3, Phasing::Symbol_RX4,
	Phasing::Symbol_RX5, Phasing::Symbol_RX6, Phasing::Symbol_RX7, Phasing::Symbol_EOS_ACK_RQ, Phasing::Symbol_EOS_ACK_BQ,
	Phasing::Symbol_DX, Phasing::Symbol_EOS };

	for (int i = 0; i < sizeof(validSyms) / sizeof(int); i++) {
		if (symbol == validSyms[i]) {
			return Phasing(Code(symbol));
		}
	}

	printf("Failed to find phasing for specified symbol: %d\n", symbol);
	abort();

	return Phasing(Code(Phasing::Symbol_EOS));
}

Phasing::Phasing()
{

}

Phasing::Phasing(Code code)
{
	this->code = code;
}

Code Phasing::getCode()
{
	return code;
}

std::string Phasing::toString()
{
	switch (code.getSymbol()) {
	case Phasing::Symbol_RX0:
		return "RX0";
	case Phasing::Symbol_RX1:
		return "RX1";
	case Phasing::Symbol_RX2:
		return "RX2";
	case Phasing::Symbol_RX3:
		return "RX3";
	case Phasing::Symbol_RX4:
		return "RX4";
	case Phasing::Symbol_RX5:
		return "RX5";
	case Phasing::Symbol_RX6:
		return "RX6";
	case Phasing::Symbol_RX7:
		return "RX7";
	case Phasing::Symbol_EOS_ACK_RQ:
		return "EOS_ACK_RQ";
	case Phasing::Symbol_EOS_ACK_BQ:
		return "EOS_ACK_BQ";
	case Phasing::Symbol_DX:
		return "DX";
	case Phasing::Symbol_EOS:
		return "EOS";
	default:
		printf("Phasing %d is invalid\n", code.getSymbol());
		abort();
		break;
	}

	return "";
}