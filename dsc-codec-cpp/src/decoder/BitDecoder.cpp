#include <string>
#include <vector>

#include "common.h"
#include "entities/Code.h"
#include "structure/Phasing.h"
#include "DigitalSelectiveCall.h"
#include "decoder/BitDecoder.h"
#include "decoder/DscDecoder.h"

FakeByteBuffer::FakeByteBuffer()
{
	memset(this->storage, 0, kbufferCapacity);
	this->pos = 0;
};

FakeByteBuffer::~FakeByteBuffer()
{

};

void FakeByteBuffer::put(char val)
{
	storage[pos] = val;
	pos++;
}

void FakeByteBuffer::put(char *vals, int len)
{
	memcpy(&storage[pos], vals, len);
	pos += len;
}

void FakeByteBuffer::get(char *dst, int len)
{
	memcpy(dst, &storage[pos], len);
}

char *FakeByteBuffer::array()
{
	return storage;
}

int FakeByteBuffer::position()
{
	return pos;
}

void FakeByteBuffer::position(int val)
{
	pos = val;
}

int FakeByteBuffer::capacity()
{
	return kbufferCapacity;
}

void FakeByteBuffer::clear()
{
	memset(storage, 0, kbufferCapacity);
	pos = 0;
}

BitDecoder::BitDecoder()
{

}

BitDecoder::BitDecoder(void *codeDecoder)
{
	this->codeDecoder = codeDecoder;

	this->beginningPattern = createBeginningPattern();
	this->endingPattern = createEndingPattern();
}

BitDecoder::~BitDecoder()
{

}

void BitDecoder::onBit(char bit)
{
	buffer.put(bit);
	int tempLen = 0;

	tempLen = buffer.position();
	char *bytes = new char[tempLen];

	memcpy(bytes, buffer.array(), tempLen);

	int toDelete = decodeBytes(bytes, tempLen);
	delete bytes;
	if (toDelete == 0)
		return;

	int newPosition = buffer.position() - toDelete;
	tempLen = buffer.capacity() - toDelete;
	char *tempBytes = new char[tempLen];
	buffer.position(toDelete);
	buffer.get(tempBytes, tempLen);
	buffer.clear();

	buffer.put(tempBytes, tempLen);
	buffer.position(newPosition);

	delete tempBytes;
}

int BitDecoder::decodeBytes(char *bytes, int length)
{
	// Not enough bytes for decoding?
	if (length < 200)
		return 0;

	std::vector<Code> createdCodes;
	// Size of symbol is 10 bytes, so we need to shift
	for (int i = 0; i < 10; i++) {

		char *tempBytes = (char *)calloc(length - i, 1);

		//char *tempBytes = new char[length - i];
		memcpy(tempBytes, &bytes[i], length - i);
		createdCodes = Code::createCodes(tempBytes, length - i);

		// Counter for incorrect symbols
		int bad = 0;

		// Check on errors
		for (Code sign : createdCodes)
			if (sign.getSymbol() == Code::Symbol_ERROR)
				bad++;

		if (!((length - i) / 10 - bad < 10)) {
			delete tempBytes;
			break;
		}

		delete tempBytes;
	}

	// Message ready for further decoding?
	int headPosition = findHeadPosition(createdCodes);
	// if we've found beginning then continue decoding
	// else remove 21 bytes
	if (headPosition < 0)
		return 21;

	// Do we need to put back into buffer and save?
	int endPosition = findEndingPosition(createdCodes);
	// if we've found end of sequence then continue decoding
	// else remove bytes
	if (endPosition < 0) {
		if (length > 2000)
			return 50;

		return 0;
	}

	// Is DSC with expanded sequence?
	int expandPosition = findExpandPosition(
		createdCodes, endPosition + endingPattern.size()
	);
	if (expandPosition < 0 && length < 2000) {
		return 0;
	}

	// To the end position adds two for decoding ECC symbol
	std::vector<Code> message = processMessage(
		createdCodes, headPosition,
		expandPosition < 0 ? endPosition + 3 : expandPosition + 3,
		expandPosition > 0
	);

	std::string decodedSymbols;
	char str[33];
	for (int i = 0; i < message.size(); i++) {
		snprintf(str, sizeof(str), "%d ", message[i].getSymbol());
		decodedSymbols += str;
	}

#ifdef DSCD_PRINT_DECODED_SYMBOLS
	DSCD_PRINTF("Decoded symbols: %s\n", decodedSymbols.c_str());
#endif

	DscDecoder *dscDec = (DscDecoder *)codeDecoder;
	dscDec->decodeCodes(message);

	return (endPosition * 10 + endingPattern.size() * 10);
}

int BitDecoder::findHeadPosition(std::vector<Code> codes)
{
	std::vector<Code> tempCodes;

	for (int i = 0; i < codes.size(); i++) {
		tempCodes.push_back(codes[i]);

		if (i > 3 && isMatchesBeginning(tempCodes))
			return i + 1;
	}

	return -1;
}

int BitDecoder::findEndingPosition(std::vector<Code> codes)
{
	std::vector<Code> tempCodes;

	for (int i = 0; i < codes.size(); i++) {
		tempCodes.push_back(codes[i]);

		if (i > 3 && isMatchesEnding(tempCodes))
			return (i - endingPattern.size());
	}

	return -1;
}

int BitDecoder::findExpandPosition(std::vector<Code> codes, int endPos)
{
	std::vector<Code> tempCodes;

	for (int i = endPos; i < codes.size(); ++i) {
		tempCodes.push_back(codes[i]);

		if (i > 3 && isMatchesEnding(tempCodes)) {
			return (i - endingPattern.size());
		}
	}

	return -1;
}

static int codeCount = 0;

/** Codes are beginning of the message if phasing was achieved. */
bool BitDecoder::isMatchesBeginning(std::vector<Code> codes)
{
	int dxCounter = 0;
	int rxCounter = 0;

	for (int i = 0; i < codes.size(); i++) {
		if ((int)(beginningPattern.size() - codes.size() + i) < 0)
			continue;

		if (codes[i].getSymbol() == beginningPattern[beginningPattern.size() + i - codes.size()].getSymbol()) {
			if (Phasing::isDx(codes[i]))
				dxCounter += 1;
			else if (Phasing::isRx(codes[i]))
				rxCounter += 1;
		}

		bool phasingAchieved = (rxCounter >= 3)
			|| ((rxCounter >= 2) && (dxCounter >= 1))
			|| ((rxCounter >= 1) && (dxCounter >= 2));

		if (phasingAchieved)
			return true;
	}

	return false;
}

bool BitDecoder::isMatchesEnding(std::vector<Code> codes)
{
	int eosCounter = 0;

	for (int i = 0; i < codes.size(); i++) {
		if (codes.size() > endingPattern.size() + i)
			continue;

		bool flag = (codes[i].getSymbol() == endingPattern[endingPattern.size() + i - codes.size()].getSymbol());
		bool isEos = Phasing::isEOS(codes[i]);

		if (flag && isEos) {
			eosCounter++;

			if (eosCounter >= 4)
				return true;
		}
	}

	return false;
}

/** Converts double DSC into single */
std::vector<Code> BitDecoder::processMessage(std::vector<Code> createdCodes,
	int startPosition,
	int endPosition,
	bool expand)
{
	std::vector<Code> message;
	message.resize(endPosition - startPosition + 4);
	for (int i = 0; i <= (endPosition - startPosition) / 2 + 2; i++)
		message.push_back(Code(Code::Symbol_ERROR));

	for (int i = 0; i <= ((endPosition - startPosition) / 2) + 2; i++) {
		bool flag1 = (createdCodes[startPosition - 4 + i * 2].getSymbol() == createdCodes[startPosition + i * 2 + 1].getSymbol());

		if (flag1) {
			message[i] = createdCodes[startPosition + i * 2 + 1];
		}
		else if (createdCodes[startPosition - 4 + i * 2].isErrorCode()) {
			if (createdCodes[startPosition + i * 2 + 1].isErrorCode()) {
				message[i] = createdCodes[startPosition + i * 2 + 1];
			}
		}
		else
			message[i] = createdCodes[startPosition - 4 + i * 2];
	}

	// Removing of superfluos EOS symbols
	if (expand) {
		int eosPos = 0;
		for (int i = 0; i < 2; ++i) {
			for (int i = message.size() - 1; i > 0; i--) {
				if (message[i].getSymbol() == Phasing::Symbol_EOS) {
					eosPos = i;
					break;
				}
			}

			message.erase(message.begin() + eosPos);
		}

		eosPos = 0;
		for (int i = message.size() - 1; i > 0; i--) {
			if (message[i].getSymbol() == Phasing::Symbol_EOS) {
				eosPos = i;
				break;
			}
		}

		Code expandEos = message[eosPos];
		message.erase(message.begin() + eosPos);
		message.insert(message.end() - 1, expandEos);
	}

	return message;
}

std::vector<Code> BitDecoder::createBeginningPattern() {
	std::vector<Code> pattern;
	pattern.resize(16);

	for (int i = 0; i < 6; i++) {
		// Dx
		pattern[i * 2] = Code(125);
		// Rx
		pattern[i * 2 + 1] = Code(111 - i);
	}

	pattern[12] = Code(Code::Symbol_SKIP);
	pattern[13] = Code(105);
	pattern[14] = Code(Code::Symbol_SKIP);
	pattern[15] = Code(104);

	return pattern;
}

std::vector<Code> BitDecoder::createEndingPattern()
{
	std::vector<Code> pattern;

	pattern.push_back(Code(Phasing::Symbol_EOS));
	for (int i = 1; i < 4; i++)
		pattern.push_back(Code(Code::Symbol_SKIP));

	for (int i = 4; i < 7; i++)
		pattern.push_back(Code(Phasing::Symbol_EOS));

	pattern.push_back(Code(Code::Symbol_SKIP));

	return pattern;
}