#include <vector>

#include "entities/Code.h"
#include "entities/Coordinates.h"
#include "entities/TimeUTC.h"
#include "entities/DscNumber.h"
#include "structure/Category.h"
#include "structure/FirstTelecommand.h"
#include "structure/DistressNature.h"
#include "structure/Phasing.h"
#include "routine/RoutineGroup.h"
#include "semiAuto/SemiAutoVhf.h"
#include "semiAuto/SemiAutoVhfAck.h"
#include "semiAuto/SemiAutoMfHf.h"
#include "semiAuto/SemiAutoMfHfAck.h"
#include "structure/Phasing.h"
#include "safety/SafetyAllShips.h"
#include "urgency/UrgencyAllShips.h"
#include "decoder/CodesDecoder.h"
#include "DigitalSelectiveCall.h"
#include "decoder/SemiAutoDecoder.h"

DigitalSelectiveCall *SemiAutoDecoder::decodeCodes(std::vector<Code> codes)
{
	Mmsi address = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 2, codes.begin() + 7));
	Mmsi selfId = Mmsi::fromCodes(std::vector<Code>(codes.begin() + 8, codes.begin() + 13));
	FirstTelecommand ft = FirstTelecommand::fromSymbol(codes[13].getSymbol());
	SecondTelecommand st = SecondTelecommand::fromSymbol(codes[14].getSymbol());

	Coordinates pos;
	Frequency freqRx;
	Frequency freqTx;
	DscNumber vhfChannelNumber;
	Phasing eos = getEos(codes);
	int eosSym = eos.getCode().getSymbol();

	bool withMfHfChannel = isMfHfChannelMarker(codes[15]);
	bool withVhfChannel = isVhfChannelMarker(codes[15]);
	bool withPos = isPosMarker(codes[15]);

	// Отслеживание позиции, с которой необходимо начать считывать номер
	int lastPos;

	if (withPos) {
		// Координаты
		pos = Coordinates::fromCodes(std::vector<Code>(codes.begin() + 16, codes.begin() + 21));
		lastPos = 21;
	}
	else if (withVhfChannel) {
		// VHF канал
		vhfChannelNumber = DscNumber::fromCodes(std::vector<Code>(codes.begin() + 16, codes.begin() + 18));
		lastPos = 18;
	}
	else if (withMfHfChannel) {
		// ПВ/КВ канал. Должен представлять частоту
		std::vector<Code> channelCodes = std::vector<Code>(codes.begin() + 16, codes.begin() + 18);
		channelCodes.insert(channelCodes.begin(), parseSecondSymbolOfCode(codes[15]));
		freqRx = Frequency::fromCodes(channelCodes);
		lastPos = 20;
	}
	else {
		// Частота
		freqRx = Frequency::fromCodes(std::vector<Code>(codes.begin() + 15, codes.begin() + 18));
		lastPos = 18;
	}

	// Проверка на присутствие tx частоты
	if (!withPos && hasFrequency(std::vector<Code>(codes.begin() + lastPos, codes.begin() + lastPos + 3))) {
		if (withMfHfChannel) {
			std::vector<Code> txCodes = std::vector<Code>(codes.begin() + lastPos, codes.begin() + lastPos + 2);
			txCodes.insert(txCodes.begin(), parseSecondSymbolOfCode(codes[lastPos - 1]));
			freqTx = Frequency::fromCodes(txCodes);
		}
		else {
			freqTx = Frequency::fromCodes(std::vector<Code>(codes.begin() + lastPos, codes.begin() + lastPos + 3));
		}

		lastPos += 3;
	}

	PstnNumber number = PstnNumber::fromCodes(std::vector<Code>(codes.begin() + lastPos + 1, codes.begin() + codes.size() - 2));

	// Если был передан номер УКВ канала, то это УКВ вызов
	if (withVhfChannel) {
		if (eosSym == Phasing::Symbol_EOS_ACK_RQ) {
			return new SemiAutoVhf(selfId, address, ft, st, number, vhfChannelNumber);
		}
		else {
			return new SemiAutoVhfAck(selfId, address, ft, st, number, vhfChannelNumber);
		}
	}
	else {

		if (eosSym == Phasing::Symbol_EOS_ACK_RQ) {
			return new SemiAutoMfHf(selfId, address, ft, st, number, freqRx, freqTx, pos);
		}
		else {
			return new SemiAutoMfHfAck(selfId, address, ft, st, number, freqRx, freqTx, pos);
		}
	}
}

bool SemiAutoDecoder::isMatches(Code code)
{
	return (code.getSymbol() == FormatSpecifier::Symbol_IDIVIDUAL_SEMI_AUTOMATIC);
}