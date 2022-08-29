#pragma once

#include "entities/Code.h"
#include "entities/Coordinates.h"
#include "entities/TimeUTC.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/DistressNature.h"
#include "structure/Phasing.h"
#include "distress/DistressAck.h"
#include "distress/DistressRelay.h"
#include "distress/DistressRelayAck.h"
#include "distress/DistressRelayRq.h"
#include "structure/Phasing.h"
#include "safety/SafetyAllShips.h"
#include "urgency/UrgencyAllShips.h"
#include "decoder/CodesDecoder.h"
#include "DigitalSelectiveCall.h"

/**
 * Decodes DSC with category of "All Ships".
 *
 * Calls: "Acknowledge of distress, retranslation of distress,
 * acknowledge of distress retranslation, safety and urgency.
 *
 * @author AlexeyVorobyev
 */
class AllShipsDecoder : public CodesDecoder
{
public:

	DigitalSelectiveCall *decodeCodes(std::vector<Code> codes);

	bool isMatches(Code code);

private:

	DigitalSelectiveCall *decodeDistress(std::vector<Code> codes);

	/** Decodes retranslation of distress (with acknowledge) */
	DigitalSelectiveCall *decodeDistressRelay(std::vector<Code> codes);

	/** Decodes distress acknowledge */
	DigitalSelectiveCall *decodeDistressAck(std::vector<Code> codes);

	/** Decodes "Safety" and "Urgency" calls */
	DigitalSelectiveCall *decodeSafetyOrUrgency(std::vector<Code> codes, Category category);
};