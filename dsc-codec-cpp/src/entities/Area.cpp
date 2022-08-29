#include "entities/Area.h"
#include "entities/Address.h"
#include "entities/Coordinates.h"

Area::Area()
{
	this->dy = 0;
	this->dx = 0;
}

Area::Area(Coordinates coordinates, int dy, int dx)
{
	this->coordinates = coordinates;
	this->dy = dy;
	this->dx = dx;
}

Coordinates Area::getCoordinates()
{
	return coordinates;
}

int Area::getDy()
{
	return dy;
}

int Area::getDx()
{
	return dx;
}

std::vector<Code> Area::toCodes()
{
	std::vector<Code> codes;
	const char *latitude = coordinates.getLatitude().c_str();
	const char *longitude = coordinates.getLongitude().c_str();
	char tmp1[2];
	char tmp2[2];
	tmp1[1] = 0;
	tmp2[1] = 0;

	Quadrant quadrant = coordinates.getQuadrant();

	tmp1[0] = latitude[0];
	codes.push_back(Code(quadrant.getCode() * 10 + atoi(tmp1)));

	tmp1[0] = latitude[1];
	tmp2[0] = longitude[0];
	codes.push_back(Code(atoi(tmp1) * 10 + atoi(tmp2)));

	tmp1[0] = longitude[1];
	tmp2[0] = longitude[2];
	codes.push_back(Code(atoi(tmp1) * 10 + atoi(tmp2)));

	codes.push_back(Code(dy));
	codes.push_back(Code(dx));

	return codes;
}

std::string Area::toString()
{
	char pos[256];
	snprintf(pos, sizeof(pos), ", dy=%d, dx=%d", dy, dx);

	std::string ret("Area{coordinates=" + coordinates.toString() + pos + "}");

	return ret;
}

Area Area::fromCodes(std::vector<Code> codes)
{
	std::vector<Code> sliceOfCodes(codes.cbegin(), codes.cbegin() + codes.size() - 1);
	Coordinates coordinates = Coordinates::fromCodes(sliceOfCodes);

	int dy = codes[3].getSymbol();
	int dx = codes[4].getSymbol();

	return Area(coordinates, dy, dx);
}