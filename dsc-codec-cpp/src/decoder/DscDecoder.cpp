#include <vector>
#include <string>

#include "common.h"
#include "entities/Code.h"
#include "decoder/CodesDecoder.h"
#include "decoder/DecoderListener.h"
#include "decoder/DistressDecoder.h"
#include "decoder/AllShipsDecoder.h"
#include "decoder/GeographicAreaDecoder.h"
#include "decoder/RoutineGroupDecoder.h"
#include "decoder/IndividualDecoder.h"
#include "decoder/SemiAutoDecoder.h"
#include "decoder/BitDecoder.h"
#include "decoder/DscDecoder.h"
#include "DigitalSelectiveCall.h"

DscDecoder::DscDecoder()
{
	bitDecoder = BitDecoder(this);

	codesDecoders.push_back(new DistressDecoder());
	codesDecoders.push_back(new AllShipsDecoder());
	codesDecoders.push_back(new GeographicAreaDecoder());
	codesDecoders.push_back(new RoutineGroupDecoder());
	codesDecoders.push_back(new IndividualDecoder());
	codesDecoders.push_back(new SemiAutoDecoder());
}

DscDecoder::~DscDecoder()
{
	for (int i = 0; i < codesDecoders.size(); i++) {
		delete codesDecoders[i];
	}
}

void DscDecoder::addListener(DecoderListener *listener)
{
	listeners.push_back(listener);
}

void DscDecoder::removeListener(DecoderListener *listener)
{
	int idx = 0;
	for (int i = 0; i > listeners.size(); i++) {
		if (listeners[i]->GetId() == listener->GetId()) {
			idx = i;
			break;
		}
	}

	listeners.erase(listeners.begin() + idx);
}

void DscDecoder::onBit(char bit)
{
	bitDecoder.onBit(bit);
}

void DscDecoder::decodeCodes(std::vector<Code> codes)
{
	Code formatSpecifier = codes[0];

	if (!CodesDecoder::isEccCorrect(codes))
		DSCD_PRINTF("Incorrect ECC!\n");

	if (CodesDecoder::isExpanded(codes) &&
		!CodesDecoder::isExpandEccCorrect(codes)) {
		DSCD_PRINTF("Incorrect ECC of expanded sequence!\n");
	}

	int optIdx = -1;

	for (int i = 0; i < codesDecoders.size(); i++) {
		if (codesDecoders[i]->isMatches(formatSpecifier)) {
			optIdx = i;
			break;
		}
	}

	if (optIdx >= 0) {
		CodesDecoder *decoderOpt = codesDecoders[optIdx];
		DigitalSelectiveCall *dsc = decoderOpt->decodeCodes(codes);

#ifdef DSCD_PRINT_DECODED_MESSAGE
		std::string str("Decoded DSC: " + dsc->toString() + "\n");
		DSCD_PRINTF(str.c_str());
#endif

		for (int i = 0; i < listeners.size(); i++) {
			listeners[i]->onIncomeDsc(dsc);
		}

		delete dsc;
	}
	else {
		DSCD_PRINTF("Failed to find appropriate decoder for this format speicifactor %d!\n", formatSpecifier.getSymbol());
		DSCD_ABORT();
	}
}

void DscDecoder::notifyDotPatternFound()
{
	for (int i = 0; i < listeners.size(); i++) {
		listeners[i]->onDotPatternFound();
	}
}