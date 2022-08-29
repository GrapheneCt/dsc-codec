#pragma once

#include "entities/Mmsi.h"
#include "entities/Frequency.h"
#include "DigitalSelectiveCall.h"
#include "AllShipsCall.h"

/** @author AlexeyVorobyev */
class UrgencyAllShips : public AllShipsCall
{
public:

	UrgencyAllShips(Mmsi selfId, FirstTelecommand ft,
		SecondTelecommand st, Frequency freqRx,
		Frequency freqTx);

	UrgencyAllShips(Mmsi selfId, FirstTelecommand ft,
		SecondTelecommand st, Frequency freqRx);

	std::string toString();
};