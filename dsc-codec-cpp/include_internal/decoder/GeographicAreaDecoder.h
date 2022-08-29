#pragma once

#include "entities/Code.h"
#include "entities/Coordinates.h"
#include "entities/TimeUTC.h"
#include "entities/Area.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/DistressNature.h"
#include "structure/Phasing.h"
#include "safety/SafetyGeographicArea.h"
#include "urgency/UrgencyGeographicArea.h"
#include "structure/Phasing.h"
#include "safety/SafetyAllShips.h"
#include "urgency/UrgencyAllShips.h"
#include "decoder/CodesDecoder.h"
#include "DigitalSelectiveCall.h"

/**
 * Decoder of "Geographical Area" DSCs.
 *
 * Decodes: retranslation of distress (with ack), safety and urgency.
 *
 * @author AlexeyVorobyev
 */
class GeographicAreaDecoder : public CodesDecoder
{
	DigitalSelectiveCall *decodeCodes(std::vector<Code> codes);

	DigitalSelectiveCall *decodeSafetyOrUrgency(
		Mmsi selfId,
		Area area,
		Category category,
		std::vector<Code> codes);

	DigitalSelectiveCall *decodeDistressRelay(Mmsi selfId, Area area, std::vector<Code> codes);

	bool isMatches(Code code);
};