#include "DigitalSelectiveCall.h"
#include "decoder/DecoderListener.h"

static unsigned int s_idgen = 0;

DecoderListener::DecoderListener()
{
	this->id = s_idgen;
	s_idgen++;
}

DecoderListener::~DecoderListener()
{

}

unsigned int DecoderListener::GetId()
{
	return id;
}