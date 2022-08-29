#pragma once

#include "entities/Frequency.h"
#include "entities/Mmsi.h"
#include "AllShipsCall.h"

/** @author AlexeyVorobyev */
class SafetyAllShips : public AllShipsCall
{
public:

	SafetyAllShips(Mmsi selfId, FirstTelecommand ft,
		SecondTelecommand st, Frequency freqRx,
		Frequency freqTx);

	SafetyAllShips(Mmsi selfId, FirstTelecommand ft,
		SecondTelecommand st, Frequency freqRx);

	std::string toString();
};