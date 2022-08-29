#pragma once

#include <vector>

/**
 * Represents code of symbol.
 *
 * On creation calculates 10-bits ECC code.
 *
 * @author AlexeyVorobyev
 */
class Code
{
public:

	enum Symbol
	{
		Symbol_ERROR = -1,
		Symbol_SKIP = 0
	};

	static std::vector<Code> createCodes(char *bytes, int bytesLen);

	Code();
	Code(int symbol);
	~Code();

	int getSymbol();
	bool isErrorCode();
	char *getTenDigitCode();

	std::string toString();

private:

	static int bytesToInt(char *bytes, int bytesLen, bool order);
	static bool isEOS(Code code);

	/** Code in decimal nubmer system */
	int symbol;

	/** Rec. ITU-R M.493-13, pg. 4 */
	char tenDigitCode[10];
	bool hasTenDigitCode;
};