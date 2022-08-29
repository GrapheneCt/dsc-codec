#pragma once

#include "entities/Code.h"
#include "decoder/BitDecoder.h"
#include "decoder/CodesDecoder.h"
#include "decoder/DecoderListener.h"
#include "decoder/DistressDecoder.h"
#include "decoder/AllShipsDecoder.h"
#include "decoder/GeographicAreaDecoder.h"
#include "decoder/RoutineGroupDecoder.h"
#include "decoder/IndividualDecoder.h"
#include "decoder/SemiAutoDecoder.h"
#include "DigitalSelectiveCall.h"

/**
 * Main decoder of DSC.
 *
 * Converts list of symbols into DSC.
 *
 * @author AlexeyVorobyev
 */
class DscDecoder
{
public:

	DscDecoder();

	~DscDecoder();

	void addListener(DecoderListener *listener);

	void removeListener(DecoderListener *listener);

	void onBit(char bit);

	void decodeCodes(std::vector<Code> codes);

	void notifyDotPatternFound();

private:

	BitDecoder bitDecoder;

	std::vector<DecoderListener *> listeners;

	std::vector<CodesDecoder *> codesDecoders;
};