#include "entities/Transmittable.h"
#include "entities/Coordinates.h"

Quadrant Quadrant::fromString(std::string s)
{
	if (s == "NE")
		return Quadrant(Quadrant::Symbol_NE);
	else if (s == "NW")
		return Quadrant(Quadrant::Symbol_NW);
	else if (s == "SE")
		return Quadrant(Quadrant::Symbol_SE);
	else if (s == "SW")
		return Quadrant(Quadrant::Symbol_SW);
	else
	{
		printf("Квадранта %s не существует!\n", s.c_str());
		abort();
	}

	return Quadrant(Quadrant::Symbol_NW);
}

Quadrant Quadrant::fromCode(int code)
{
	if (code > 3 || code < 0) {
		return Quadrant(Quadrant::Symbol_NE);
	}

	return Quadrant(code);
}

Quadrant::Quadrant()
{
	this->code = 0;
}

Quadrant::Quadrant(int code)
{
	this->code = code;
}

Quadrant::~Quadrant()
{

}

int Quadrant::getCode()
{
	return code;
}

std::string Quadrant::toString()
{
	switch (code) {
	case 0: return "NE";
	case 1: return "NW";
	case 2: return "SE";
	case 3: return "SW";
	default:
		printf("Квадранта с кодом %d не существует!\n", code);
		abort();
		break;
	}

	return "NE";
}

Coordinates::Coordinates()
{
	this->longitude = "99999";
	this->latitude = "9999";
	this->quadrant = Quadrant(Quadrant::Symbol_NE);
}

/**
* Создаёт класс координат
*
* @param longitude долгота (5 цифр)
* @param latitude  широта (4 цифры)
* @param quadrant  квадрант
*/
Coordinates::Coordinates(std::string ilongitude, std::string ilatitude, Quadrant quadrant)
{
	if (ilongitude.length() == 5 && ilatitude.length() == 4) {
		this->longitude = ilongitude;
		this->latitude = ilatitude;
		this->quadrant = quadrant;
	}
	else
	{
		printf("Долгота(longitude) должна состоять из 5 цифр, а широта(latitude) из 4!\n");
		abort();
	}
}

Coordinates::Coordinates(std::string ilongitude, std::string ilatitude)
{
	if (ilongitude.length() == 5 && ilatitude.length() == 4) {
		this->longitude = ilongitude;
		this->latitude = ilatitude;
		this->quadrant = Quadrant(Quadrant::Symbol_NE);
	}
	else
	{
		printf("Долгота(longitude) должна состоять из 5 цифр, а широта(latitude) из 4!\n");
		abort();
	}
}

Coordinates::~Coordinates()
{

}

std::string Coordinates::getLongitude()
{
	return longitude;
}

std::string Coordinates::getLatitude()
{
	return latitude;
}

Quadrant Coordinates::getQuadrant()
{
	return quadrant;
}

std::vector<Code> Coordinates::toCodes()
{
	std::vector<Code> signs;
	const char *clatitude = latitude.c_str();
	const char *clongitude = longitude.c_str();
	char tmp1[2];
	char tmp2[2];
	tmp1[1] = 0;
	tmp2[1] = 0;

	tmp1[0] = clatitude[0];
	signs.push_back(Code(quadrant.getCode() * 10 + atoi(tmp1)));

	tmp1[0] = clatitude[1];
	tmp2[0] = clatitude[2];
	signs.push_back(Code(atoi(tmp1) * 10 + atoi(tmp2)));

	tmp1[0] = clatitude[3];
	tmp2[0] = clongitude[0];
	signs.push_back(Code(atoi(tmp1) * 10 + atoi(tmp2)));

	tmp1[0] = clongitude[1];
	tmp2[0] = clongitude[2];
	signs.push_back(Code(atoi(tmp1) * 10 + atoi(tmp2)));

	tmp1[0] = clongitude[3];
	tmp2[0] = clongitude[4];
	signs.push_back(Code(atoi(tmp1) * 10 + atoi(tmp2)));

	return signs;
}

/**
	* Возвращает декодированные координаты из символов.
	*
	* При получении координат по умолчанию выводит их как получил.
	*
	* @param codes коды
	* @return координаты
	*/
Coordinates Coordinates::fromCodes(std::vector<Code> codes)
{
	int quadrantCode = codes[0].getSymbol() / 10;
	bool quadrantExists = (quadrantCode >= 0 && quadrantCode <= 3);

	// Координаты по умолчанию (не определены)
	if (!quadrantExists)
		return Coordinates("99999", "9999", Quadrant(Quadrant::Symbol_NE));

	if (codes.size() == 5) return fromCodes5(codes);
	else if (codes.size() == 3) return fromCodes3(codes);
	else {
		printf("Количество символов для декодирования должно быть 3 или 5. Получено: %d\n", codes.size());
		abort();
	}

	return Coordinates("99999", "9999", Quadrant(Quadrant::Symbol_NE));
}

std::string Coordinates::toString()
{
	std::string q = getQuadrant().toString();

	if (longitude == "99999" && latitude == "9999") {
		return "EMPTY";
	}

	std::string lon = longitude.substr(0, 3) + "'"
		+ longitude.substr(3, 5) + q.at(0);

	std::string lat = latitude.substr(0, 2) + "'" +
		latitude.substr(2, 4) + q.at(1);

	return lon + " " + lat;
}

/**
	* Возвращает декодированные координаты из 5 символов.
	*
	* Исключения из-за того, что непонятно что может пойти не так.
	*
	* @param codes коды
	* @return координаты
	*/
Coordinates Coordinates::fromCodes5(std::vector<Code> codes)
{
	Quadrant quadrant = Quadrant::fromCode(
		codes[0].getSymbol() / 10
	);

	char str[33];

	int lval = (codes[0].getSymbol() - ((codes[0].getSymbol()
		/ 10) * 10)) * 1000 + codes[1].getSymbol() * 10 +
		codes[2].getSymbol() / 10;

	std::string ilat = "";
	if ((lval / 100) < 10) ilat += "0";
	snprintf(str, sizeof(str), "%d", (int)((double)lval / 100));
	ilat += str;
	if ((lval - (lval / 100) * 100) < 10) ilat += "0";
	ilat += "00";

	lval = (codes[2].getSymbol() - ((codes[2].getSymbol() / 10)
		* 10)) * 10000 + codes[3].getSymbol() * 100 + codes[4].getSymbol();
	std::string ilong = "";
	if (lval / 100 < 100) ilong += "0";
	if (lval / 100 < 10) ilong += "0";

	snprintf(str, sizeof(str), "%d", (int)((double)lval / 100));
	ilong += str;

	if (lval - (lval / 100) * 100 < 10) ilong += "0";
	ilong += "00";

	return Coordinates(ilong, ilat, quadrant);
}

/**
	* Возвращает декодированные координаты из 3 символов.
	*
	* Исключения из-за того, что непонятно что может пойти не так.
	*
	* @param codes коды
	* @return координаты
	*/
Coordinates Coordinates::fromCodes3(std::vector<Code> codes)
{
	Quadrant quadrant = Quadrant::fromCode(
		codes[0].getSymbol() / 10
	);

	char str[33];

	int lval = (codes[0].getSymbol() -
		((codes[0].getSymbol() / 10) * 10)) * 10 +
		codes[1].getSymbol() / 10;

	std::string ilat = "";
	snprintf(str, sizeof(str), "%d", lval);
	ilat += str;

	lval = (codes[1].getSymbol() - ((codes[1].getSymbol() /
		10) * 10)) * 100 + codes[2].getSymbol();

	std::string ilong = "";
	snprintf(str, sizeof(str), "%d", lval);
	ilong += str;

	return Coordinates(ilong, ilat, quadrant);
}