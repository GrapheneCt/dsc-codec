#pragma once

#include "entities/Mmsi.h"
#include "entities/Frequency.h"
#include "DigitalSelectiveCall.h"
#include "GeographicArea.h"

/** @author AlexeyVorobyev */
class UrgencyGeographicArea : public GeographicArea
{
public:

	UrgencyGeographicArea(Mmsi selfId, Area area,
		FirstTelecommand ft,
		SecondTelecommand st,
		Frequency freqRx,
		Frequency freqTx);

	UrgencyGeographicArea(Mmsi selfId, Area area,
		FirstTelecommand ft,
		SecondTelecommand st,
		Frequency freqRx);

	std::string toString();
};