#pragma once

#include "entities/Address.h"
#include "entities/Coordinates.h"

/**
 * Geographical area.
 *
 * Coding in accordance with Rec. ITU-R M.493-13 p.5.3.
 *
 * Note: coding of coordinate in transsmition of "Geographical area" DSCs
 * is different. We take only degrees.
 *
 * @author AlexeyVorobyev
 */
class Area : public Address
{
public:

	Area();
	Area(Coordinates coordinates, int dy, int dx);

	Coordinates getCoordinates();

	int getDy();
	int getDx();

	std::vector<Code> toCodes();

	std::string toString();

	/**
	 * Decodes geographical area.
	 *
	 * We take only degrees.
	 */
	static Area fromCodes(std::vector<Code> codes);

private:

	Coordinates coordinates;
	int dy;
	int dx;
};
