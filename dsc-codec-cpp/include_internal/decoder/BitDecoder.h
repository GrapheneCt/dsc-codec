#pragma once

#include "entities/Code.h"
#include "structure/Phasing.h"
#include "DigitalSelectiveCall.h"

class FakeByteBuffer
{
public:

	FakeByteBuffer();

	~FakeByteBuffer();

	void put(char val);
	void put(char *vals, int len);
	void get(char *dst, int len);
	char *array();
	int position();
	void position(int val);
	int capacity();
	void clear();

private:

	static const int kbufferCapacity = 10 * 400;

	char storage[kbufferCapacity];
	int pos;
};

/**
 * Decoder for bits (0 and 1)
 *
 * @author AlexeyVorobyev
 */
class BitDecoder
{
public:

	BitDecoder();
	BitDecoder(void *codeDecoder); // class DscDecoder -- to avoid circular dependency
	~BitDecoder();

	void onBit(char bit);
	int decodeBytes(char *bytes, int length);
	int findHeadPosition(std::vector<Code> codes);
	int findEndingPosition(std::vector<Code> codes);
	int findExpandPosition(std::vector<Code> codes, int endPos);
	/** Codes are beginning of the message if phasing was achieved. */
	bool isMatchesBeginning(std::vector<Code> codes);
	bool isMatchesEnding(std::vector<Code> codes);

private:

	/** Converts double DSC into single */
	std::vector<Code> processMessage(std::vector<Code> createdCodes,
		int startPosition,
		int endPosition,
		bool expand);

	std::vector<Code> createBeginningPattern();
	std::vector<Code> createEndingPattern();

	void *codeDecoder; // class DscDecoder -- to avoid circular dependency

	std::vector<Code> beginningPattern;
	std::vector<Code> endingPattern;
	FakeByteBuffer buffer;
};