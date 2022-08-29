#include <string>
#include <vector>

#include "entities/Code.h"
#include "structure/Phasing.h"
#include "DigitalSelectiveCall.h"
#include "DscMarkers.h"
#include "decoder/CodesDecoder.h"

Phasing CodesDecoder::getEos(std::vector<Code> codes)
{
	int eosIndex = -1;
	int eosBq = -1;

	for (int i = 0; i < codes.size(); i++) {
		if (codes[i].getSymbol() == Phasing::Symbol_EOS)
			eosIndex = i;
		else if (codes[i].getSymbol() == Phasing::Symbol_EOS_ACK_BQ)
			eosBq = i;
	}

	if (eosIndex > 0) return Phasing(Code(Phasing::Symbol_EOS));
	else if (eosBq > 0) return Phasing(Code(Phasing::Symbol_EOS_ACK_BQ));

	return Phasing(Code(Phasing::Symbol_EOS_ACK_RQ));
}

bool CodesDecoder::isPosMarker(Code c)
{
	return (c.getSymbol() == DscMarkers::posMarker);
}

bool CodesDecoder::isVhfChannelMarker(Code c)
{
	return (c.getSymbol() == DscMarkers::vhfChannelMarker);
}

bool CodesDecoder::isExpanded(std::vector<Code> codes)
{
	int eosIndex = -1000;
	int eosSymbol = getEos(codes).getCode().getSymbol();

	for (int i = 0; i < codes.size(); i++) {
		if (codes[i].getSymbol() == eosSymbol)
			eosIndex = i;
	}

	return (codes.size() > eosIndex + 2);
}

bool CodesDecoder::isNumberMarker(Code c)
{
	return (c.getSymbol() == DscMarkers::pstnMarker);
}

bool CodesDecoder::isMfHfChannelMarker(Code c)
{
	return ((c.getSymbol() / 10) == 3);
}

Code CodesDecoder::parseSecondSymbolOfCode(Code c)
{
	char str[33];

	snprintf(str, sizeof(str), "%d", c.getSymbol());
	str[1] = 0;

	return Code(atoi(str));
}

bool CodesDecoder::hasFrequency(std::vector<Code> codes)
{
	// 126 is marker meaning "No information"
	// 106 is marker meaning that is is followed by number

	int count126 = 0;

	for (int i = 0; i < codes.size(); i++) {
		if (codes[i].getSymbol() == 126)
			count126++;
	}

	return ((count126 != 3) && (codes[0].getSymbol() != 106));
}

bool CodesDecoder::isEccCorrect(std::vector<Code> codes)
{
	int eosIndex = -1;
	int eosSymbol = getEos(codes).getCode().getSymbol();

	for (int i = 0; i < codes.size(); i++) {
		if (codes[i].getSymbol() == eosSymbol) {
			eosIndex = i;
			break;
		}
	}

	int receivedEcc = codes[eosIndex + 1].getSymbol();
	Code calculatedEcc = DigitalSelectiveCall::calculateEccFromInfoCodes(std::vector<Code>(codes.begin() + 1, codes.begin() + eosIndex + 1));

	return (calculatedEcc.getSymbol() == receivedEcc);
}

bool CodesDecoder::isExpandEccCorrect(std::vector<Code> codes)
{
	int eosIndex = -1;
	int eosSymbol = getEos(codes).getCode().getSymbol();

	for (int i = 0; i < codes.size(); i++) {
		if (codes[i].getSymbol() == eosSymbol) {
			eosIndex = i;
			break;
		}
	}

	if (isExpanded(codes)) {
		int receivedExpanEcc = codes[codes.size() - 1].getSymbol();
		Code calculatedEcc = DigitalSelectiveCall::calculateEccFromInfoCodes(std::vector<Code>(codes.begin() + eosIndex + 2, codes.end()));

		return (calculatedEcc.getSymbol() == receivedExpanEcc);
	}

	return false;
}