#include <string>
#include <vector>

#include "structure/FormatSpecifier.h"
#include "structure/Phasing.h"
#include "entities/Mmsi.h"
#include "structure/PossibleExpansion.h"
#include "DigitalSelectiveCall.h"

DigitalSelectiveCall::DigitalSelectiveCall(FormatSpecifier formatSpecifier,
	Phasing eos, Mmsi selfId)
{
	if (!Phasing::isEOS(eos)) {
		printf("Expected symbol of the end of the sequence. Received: %s\n", eos.toString().c_str());
		abort();
	}

	this->formatSpecifier = formatSpecifier;
	this->eos = eos;
	this->selfId = selfId;
	this->hasPossibleExpansion = false;
}

DigitalSelectiveCall::~DigitalSelectiveCall()
{

}

FormatSpecifier DigitalSelectiveCall::getFormatSpecifier()
{
	return formatSpecifier;
}

Phasing DigitalSelectiveCall::getEos()
{
	return eos;
}

Mmsi DigitalSelectiveCall::getSelfId()
{
	return selfId;
}

Code DigitalSelectiveCall::calculateEccFromInfoCodes(std::vector<Code> infoCodes)
{
	int result = 0;

	for (int i = 0; i < infoCodes.size(); i++) {
		result ^= infoCodes[i].getSymbol();
	}

	return Code(result);
}

char *DigitalSelectiveCall::encode(int *size)
{
	std::vector<Code> dxSeq;
	std::vector<Code> rxSeq;

	// Construction of phasing sequence
	for (int i = 0; i < 6; i++) dxSeq.push_back(Phasing::Symbol_DX);

	Phasing rxes[] = { Phasing(Phasing::Symbol_RX7), Phasing(Phasing::Symbol_RX6),
		Phasing(Phasing::Symbol_RX5), Phasing(Phasing::Symbol_RX4), Phasing(Phasing::Symbol_RX3),
		Phasing(Phasing::Symbol_RX2), Phasing(Phasing::Symbol_RX1), Phasing(Phasing::Symbol_RX0) };

	for (Phasing rx : rxes) rxSeq.push_back(rx.getCode());

	std::vector<Code> codes = toCodes();

	for (Code cd : codes) printf("%d ", cd.getSymbol());

	for (Code s : codes) {
		dxSeq.push_back(s);
		rxSeq.push_back(s);
	}

	dxSeq.push_back(getEos().getCode());
	dxSeq.push_back(getEos().getCode());

	if (hasPossibleExpansion) {
		ExpansionPosition ep = getExpansion();
		std::vector<Code> epCodes;
		epCodes.push_back(getEos().getCode());
		epCodes.push_back(calculateEccFromInfoCodes(epCodes));

		rxSeq.push_back(Code(126));
		rxSeq.push_back(Code(126));

		for (Code s : epCodes) {
			dxSeq.push_back(s);
			rxSeq.push_back(s);
		}

		dxSeq.push_back(getEos().getCode());
		dxSeq.push_back(getEos().getCode());
	}

	int bytesLen = 200 + (dxSeq.size() + rxSeq.size()) * 10;
	int bytesIdx = 0;
	char *bytes = new char[bytesLen];
	if (size)
		*size = bytesLen;

	// Adding dot pattern
	for (int i = 0; i < 200; i++) {
		if (i % 2 == 0)
			bytes[i] = 0;
		else
			bytes[i] = 1;
		bytesIdx++;
	}

	// Connection of DX and RX sequences
	for (int i = 0; i < (bytesLen - 200) / 20; i++) {
		memcpy(&bytes[bytesIdx], dxSeq[i].getTenDigitCode(), 10);
		bytesIdx += 10;
		memcpy(&bytes[bytesIdx], rxSeq[i].getTenDigitCode(), 10);
		bytesIdx += 10;
	}

	return bytes;
}