#pragma once

#include "DigitalSelectiveCall.h"

/**
 * Listener of decoded DSC.
 *
 * @author AlexeyVorobyev
 */
class DecoderListener
{
public:

	DecoderListener();
	~DecoderListener();

	virtual void onIncomeDsc(DigitalSelectiveCall *call) =0;
	virtual void onDotPatternFound() =0;

	unsigned int GetId();

	unsigned int id;
};