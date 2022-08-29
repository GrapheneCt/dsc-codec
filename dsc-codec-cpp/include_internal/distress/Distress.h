#pragma once

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "entities/Mmsi.h"
#include "entities/TimeUTC.h"
#include "structure/Category.h"
#include "structure/DistressNature.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "DigitalSelectiveCall.h"

/** @author AlexeyVorobyev */
class Distress : public DigitalSelectiveCall
{
public:

	Distress(Mmsi selfId, DistressNature nature,
		Coordinates coordinates, TimeUTC distressTime,
		FirstTelecommand subsequentCommunication);

	Distress(Mmsi selfId, DistressNature nature,
		Coordinates coordinates, TimeUTC distressTime,
		FirstTelecommand subsequentCommunication,
		ExpansionPosition expansionPosition);

	/** @see DigitalSelectiveCall#toCodes() */
	std::vector<Code> toCodes();

	std::string toString();

	ExpansionPosition getExpansion();
	DistressNature getNature();
	Coordinates getCoordinates();
	TimeUTC getDistressTime();
	FirstTelecommand getSubsequentCommunication();

private:

	/** Характер бедствия. 112 */
	 DistressNature nature;
	/** Координаты судна, терпящего бедствие */
	Coordinates coordinates;
	/** Время бедствия */
	TimeUTC distressTime;
	/** Последующий тип связи */
	FirstTelecommand subsequentCommunication;
	ExpansionPosition expansionPosition;
	bool hasExpansionPosition;
};