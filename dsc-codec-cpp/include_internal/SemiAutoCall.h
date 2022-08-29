#pragma once

#include "entities/Mmsi.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/SecondTelecommand.h"
#include "entities/PstnNumber.h"
#include "DigitalSelectiveCall.h"

/**
 * "Semi-auto" call.
 *
 * @author AlexeyVorobyev
 */
class SemiAutoCall : public DigitalSelectiveCall
{
public:

	SemiAutoCall(Phasing eos, Mmsi selfId, Mmsi address,
		FirstTelecommand firstTelecommand,
		SecondTelecommand secondTelecommand,
		PstnNumber pstnNumber);

	std::vector<Code> toCodes();

	virtual std::vector<Code> getAdditionalCodes() =0;

	Mmsi getAddress();
	Category getCategory();
	FirstTelecommand getFirstTelecommand();
	SecondTelecommand getSecondTelecommand();
	PstnNumber getPstnNumber();

private:

	Mmsi address;
	Category category;
	FirstTelecommand firstTelecommand;
	SecondTelecommand secondTelecommand;
	PstnNumber pstnNumber;
};