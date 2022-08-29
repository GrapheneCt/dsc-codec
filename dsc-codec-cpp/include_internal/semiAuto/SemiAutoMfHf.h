#pragma once

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "DigitalSelectiveCall.h"
#include "SemiAutoCall.h"

/** @author AlexeyVorobyev */
class SemiAutoMfHf : public SemiAutoCall
{
public:

	SemiAutoMfHf(Mmsi selfId, Mmsi address,
		FirstTelecommand ft, SecondTelecommand st,
		PstnNumber number, Frequency rxFrequency = Frequency(0),
		Frequency txFrequency = Frequency(0),
		Coordinates pos = Coordinates());

	std::vector<Code> getAdditionalCodes();

	std::string toString();

private:

	Frequency rxFrequency;
	Frequency txFrequency;
	Coordinates pos;

	bool hasFrequencyRx;
	bool hasFrequencyTx;
	bool hasCoordinates;
};