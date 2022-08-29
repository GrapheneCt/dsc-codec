#include <string>
#include <vector>

#include "entities/Frequency.h"
#include "entities/Coordinates.h"
#include "entities/DscNumber.h"
#include "DigitalSelectiveCall.h"
#include "SemiAutoCall.h"
#include "DscMarkers.h"
#include "semiAuto/SemiAutoVhf.h"

SemiAutoVhf::SemiAutoVhf(Mmsi selfId, Mmsi address,
	FirstTelecommand ft, SecondTelecommand st,
	PstnNumber number, DscNumber channelNumber) :
	SemiAutoCall(Phasing(Code(Phasing::Symbol_EOS_ACK_RQ)), selfId, address, ft, st, number)
{
	this->channelNumber = channelNumber;
}

std::string SemiAutoVhf::toString()
{
	std::string ret("SemiAutoVhf{");
	ret += "\naddress=" + getAddress().toString();
	ret += "\ncategory=" + getCategory().toString();
	ret += "\nfirstTelecommand=" + getFirstTelecommand().toString();
	ret += "\nsecondTelecommand=" + getSecondTelecommand().toString();
	ret += "\nchannelNumber=" + channelNumber.toString();
	ret += "\nnumber=" + getPstnNumber().toString();
	ret += "\n}";

	return ret;
}

std::vector<Code> SemiAutoVhf::getAdditionalCodes()
{
	std::vector<Code> codes;

	// Marker of VHF channel
	codes.push_back(Code(DscMarkers::vhfChannelMarker));

	std::vector<Code> channelNumCodes = channelNumber.toCodes();
	if (channelNumCodes.size() < 2) {
		codes.push_back(Code(0));
		codes.push_back(channelNumCodes[0]);
	}
	else if (channelNumCodes.size() == 2) {
		codes.insert(codes.end(), channelNumCodes.begin(), channelNumCodes.end());
	}
	else {
		codes.insert(codes.end(), channelNumCodes.begin(), channelNumCodes.begin() + 2);
	}

	return codes;
}