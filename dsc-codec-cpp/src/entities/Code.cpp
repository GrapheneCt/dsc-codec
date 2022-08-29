#include <cstddef>
#include <vector>

#include "entities/Code.h"
#include "structure/Phasing.h"

using namespace std;

vector<Code> Code::createCodes(char *bytes, int bytesLen)
{
	vector<Code> codes;

	char bValue[7];
	char errbar[3];

	for (int i = 0; i < bytesLen / 10; i++) {
		int counter = 0;

		char b;
		for (int j = 0; j < 10; j++) {
			// Cчитываем 10 байт
			b = bytes[j + i * 10];
			// Подсчитываем количество нулей
			if (j < 7) {
				bValue[j] = b;
				if (b == 0x00)
					counter++;
			}
			else {
				errbar[j - 7] = b;
			}
		}

		if (counter == bytesToInt(errbar, sizeof(errbar), false))
			codes.push_back(Code(bytesToInt(bValue, sizeof(bValue), true)));
		else
			codes.push_back(Code(Code::Symbol_ERROR));

	}

	return codes;
}

Code::Code()
{
	this->symbol = Symbol_SKIP;
	this->hasTenDigitCode = false;
}

Code::Code(int symbol)
{
	this->symbol = symbol;
	this->hasTenDigitCode = false;
}

Code::~Code()
{

}

int Code::getSymbol()
{
	return symbol;
}

std::string Code::toString()
{
	char str[32];
	snprintf(str, sizeof(str), "Code{%d}", symbol);

	return str;
}

bool Code::isErrorCode()
{
	return (symbol == Code::Symbol_ERROR);
}

char *Code::getTenDigitCode()
{
	if (!hasTenDigitCode) {
		int tempValue = symbol;

		int divisor = 64;

		int zeroCount = 0;
		for (int i = 6; i >= 0; i--) {
			if (tempValue / divisor == 0) {
				tenDigitCode[i] = 0;
				zeroCount++;
			}
			else {
				tenDigitCode[i] = 1;
				tempValue -= divisor;
			}
			divisor /= 2;
		}

		divisor = 4;
		for (int i = 7; i < 10; i++) {
			if (zeroCount / divisor == 0)
				tenDigitCode[i] = 0;
			else {
				tenDigitCode[i] = 1;
				zeroCount -= divisor;
			}
			divisor /= 2;
		}

		hasTenDigitCode = true;
	}

	return tenDigitCode;
}

int Code::bytesToInt(char *bytes, int bytesLen, bool order)
{
	int result = 0;
	int power = 1;

	if (order) {
		for (int i = 0; i < bytesLen; i++) {
			if (bytes[i] == 0x01)
				result += power;

			power *= 2;
		}
	}
	else {
		for (int i = bytesLen - 1; i >= 0; i--) {
			if (bytes[i] == 0x01)
				result += power;

			power *= 2;
		}
	}

	return result;
}

bool Code::isEOS(Code code)
{
	int symbol = code.getSymbol();

	return (symbol == Phasing::Symbol_EOS ||
		symbol == Phasing::Symbol_EOS_ACK_RQ ||
		symbol == Phasing::Symbol_EOS_ACK_BQ);
}