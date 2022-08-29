#pragma once

#include <vector>
#include <sstream>
#include <time.h>

#include "entities/Transmittable.h"

/**
 * Класс-хелпер для представления времени в UTC и конвертаций.
 *
 * @author AlexeyVorobyev
 */
class TimeUTC : public Transmittable
{
public:

	/**
	 * Создаёт контейнер для указанного времени по UTC
	 *
	 * @param utcTime время по UTC
	 */
	TimeUTC(time_t utcTime);

	/** Создаёт заглушку для времени (часы и минуты равны 88) */
	TimeUTC();

	time_t getUtcTime();
	std::vector<Code> toCodes();
	std::string toString();

	/**
	 * Декодирует время по UTC.
	 *
	 * Для декодирования необходимо 2 символа (часы и минуты).
	 *
	 * @param codes коды для декодирования
	 * @return время по UTC
	 */
	static TimeUTC fromCodes(std::vector<Code> codes);

	/**
	 * Возвращает текущее время по UTC
	 *
	 * @return текущее время по UTC
	 */
	static TimeUTC now();

private:

	time_t utcTime;
	bool valid;
};
