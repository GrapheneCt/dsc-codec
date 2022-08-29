#pragma once

#include "entities/Frequency.h"
#include "entities/Mmsi.h"
#include "GeographicArea.h"

/** @author AlexeyVorobyev */
class SafetyGeographicArea : public GeographicArea
{
public:

	SafetyGeographicArea(Mmsi selfId, Area area,
		FirstTelecommand ft,
		SecondTelecommand st,
		Frequency freqRx,
		Frequency freqTx);

	SafetyGeographicArea(Mmsi selfId, Area area,
		FirstTelecommand ft,
		SecondTelecommand st,
		Frequency freqRx);

	std::string toString();
};
