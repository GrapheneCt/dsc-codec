#pragma once

#include "structure/FormatSpecifier.h"
#include "structure/Phasing.h"
#include "entities/Mmsi.h"
#include "structure/PossibleExpansion.h"

/**
 * Abstract Digital Selective Call.
 *
 * Contains format specifier and symbol of the end of the sequence called "EOS".
 *
 * @author AlexeyVorobyev
 */
class DigitalSelectiveCall : public PossibleExpansion
{
public:

	/**
	 * Calculates symbol of error detection "ECC" from information codes.
	 *
	 * @param infoCodes information codes
	 * @return ECC symbol
	 */
	static Code calculateEccFromInfoCodes(std::vector<Code> infoCodes);

	DigitalSelectiveCall(FormatSpecifier formatSpecifier,
		Phasing eos, Mmsi selfId);
	~DigitalSelectiveCall();

	/**
	 * Converts DSC into symbol representation for transmission.
	 *
	 * Contains two specifications of format, information codes, ECC and EOS.
	 *
	 * @return list of symbol for transmission
	 */
	virtual std::vector<Code> toCodes() =0;

	virtual std::string toString() =0;

	/**
	* Converts DSC into bytes representation
	*
	* @return sequence of bytes
	*/
	char *encode(int *size);

	FormatSpecifier getFormatSpecifier();
	Phasing getEos();
	Mmsi getSelfId();

private:

	FormatSpecifier formatSpecifier;
	Phasing eos;
	Mmsi selfId;
	bool hasPossibleExpansion;
};