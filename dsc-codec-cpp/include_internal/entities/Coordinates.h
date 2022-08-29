#pragma once

#include "entities/Transmittable.h"

class Quadrant
{
public:

	enum Symbol
	{
		Symbol_NE,
		Symbol_NW,
		Symbol_SE,
		Symbol_SW,
	};

	static Quadrant fromString(std::string s);

	static Quadrant fromCode(int code);

	Quadrant();
	Quadrant(int code);
	~Quadrant();

	int getCode();

	std::string toString();

private:

	int code;
};

/**
 * Представляет собой обычные координаты, без расширенной последовательности.
 *
 * @author AlexeyVorobyev
 */
class Coordinates : public Transmittable
{
public:

	/**
	 * Создаёт класс координат
	 *
	 * @param longitude долгота (5 цифр)
	 * @param latitude  широта (4 цифры)
	 * @param quadrant  квадрант
	 */
	Coordinates();
	Coordinates(std::string longitude, std::string latitude, Quadrant quadrant);
	Coordinates(std::string longitude, std::string latitude);
	~Coordinates();

	std::string getLongitude();

	std::string getLatitude();

	Quadrant getQuadrant();

	std::vector<Code> toCodes();

	/**
	 * Возвращает декодированные координаты из символов.
	 *
	 * При получении координат по умолчанию выводит их как получил.
	 *
	 * @param codes коды
	 * @return координаты
	 */
	static Coordinates fromCodes(std::vector<Code> codes);

	std::string toString();

private:
		
	/**
	 * Возвращает декодированные координаты из 5 символов.
	 *
	 * Исключения из-за того, что непонятно что может пойти не так.
	 *
	 * @param codes коды
	 * @return координаты
	 */
	static Coordinates fromCodes5(std::vector<Code> codes);

	/**
	 * Возвращает декодированные координаты из 3 символов.
	 *
	 * Исключения из-за того, что непонятно что может пойти не так.
	 *
	 * @param codes коды
	 * @return координаты
	 */
	static Coordinates fromCodes3(std::vector<Code> codes);

	/** Долгота. Состоит из 5 цифр: градусов(3) и минут(2) */
	std::string longitude;

	/** Широта. Состоит из 4 цифр: градусов(2) и минут(2) */
	std::string latitude;

	Quadrant quadrant;
};
