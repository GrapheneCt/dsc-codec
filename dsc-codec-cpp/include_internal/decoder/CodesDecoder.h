#pragma once

#include "entities/Code.h"
#include "structure/Phasing.h"
#include "DigitalSelectiveCall.h"
#include "DscMarkers.h"

/**
 * Abstract decoder for symbols of DSC.
 *
 * @author AlexeyVorobyev
 */
class CodesDecoder
{
public:

	/**
	 * Returns EOS symbol from specified codes.
	 *
	 * Method expects full sequence of codes of single DSC.
	 *
	 * @param codes codes of full DSC
	 * @return EOS symbol
	 */
	static Phasing getEos(std::vector<Code> codes);

	/**
	 * Checks whether specified code is position marker.
	 *
	 * If specified code is position marker then it is followed by coordinates.
	 */
	static bool isPosMarker(Code c);

	/**
	 * Checks whether specified code is VHF channel marker.
	 *
	 * If specified code is VHF channel marker then it is folled by number of
	 * VHF channel (two-digit).
	 */
	static bool isVhfChannelMarker(Code c);

	/** Checks wether DSC is expanded */
	static bool isExpanded(std::vector<Code> codes);

	/** Checks wether specified code is marker of "Number" type. */
	static bool isNumberMarker(Code c);

	/** Checks whether specified code is MF/HF channel marker. */
	static bool isMfHfChannelMarker(Code c);

	static Code parseSecondSymbolOfCode(Code c);

	/** Checks whether DSC has frequency. */
	static bool hasFrequency(std::vector<Code> codes);

	static bool isEccCorrect(std::vector<Code> codes);

	static bool isExpandEccCorrect(std::vector<Code> codes);

	virtual DigitalSelectiveCall *decodeCodes(std::vector<Code> codes) =0;

	/**
	 * Checks wether this decoder appropriate for specified format specificator.
	 */
	virtual bool isMatches(Code code) =0;
};
