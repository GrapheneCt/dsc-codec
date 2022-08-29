#pragma once

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "entities/DscNumber.h"
#include "DigitalSelectiveCall.h"
#include "SemiAutoCall.h"
#include "DscMarkers.h"

/** @author AlexeyVorobyev */
class SemiAutoVhfAck : public SemiAutoCall
{
public:

	SemiAutoVhfAck(Mmsi selfId, Mmsi address,
		FirstTelecommand ft, SecondTelecommand st,
		PstnNumber number, DscNumber channelNumber);

	std::string toString();

	std::vector<Code> getAdditionalCodes();

private:

	DscNumber channelNumber;
};