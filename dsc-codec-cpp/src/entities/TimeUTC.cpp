#pragma warning(disable : 4996)

#include <vector>
#include <sstream>
#include <time.h>

#include "entities/Transmittable.h"
#include "entities/TimeUTC.h"

TimeUTC::TimeUTC(time_t utcTime)
{
	this->utcTime = utcTime;
	this->valid = true;
}

TimeUTC::TimeUTC()
{
	this->utcTime = 0;
	this->valid = false;
}

time_t TimeUTC::getUtcTime()
{
	return utcTime;
}

std::vector<Code> TimeUTC::toCodes()
{
	std::vector<Code> signs;
	struct tm * utime;
	int hour = 88;
	int min = 88;

	if (valid) {
		utime = gmtime(&utcTime);

		int hour = utime->tm_hour;
		int min = utime->tm_min;
	}

	signs.push_back(Code(hour));
	signs.push_back(Code(min));

	return signs;
}

TimeUTC TimeUTC::fromCodes(std::vector<Code> codes)
{
	if (codes.size() < 2) {
		printf("Для декодирования времени необходимо 2 символа. Получено: %d\n" + codes.size());
		abort();
	}

	int hour = codes[0].getSymbol();
	int min = codes[1].getSymbol();

	// Если часы и минуты равны 88 - это означает, что время неизвестно
	if (hour == 88 || min == 88)
		return TimeUTC();
	else {
		struct tm utime;
		memset(&utime, 0, sizeof(tm));
		utime.tm_hour = hour;
		utime.tm_min = min;

		return TimeUTC(mktime(&utime));
	}
}

TimeUTC TimeUTC::now()
{
	time_t ltime;
	struct tm * utime;

	time(&ltime);

	utime = gmtime(&ltime);

	time_t utctime = mktime(utime);

	return TimeUTC(utctime);
}

std::string TimeUTC::toString()
{
	if (!valid) {
		return ("TimeUTC{EMPTY}");
	}

	struct tm * utime;
	utime = gmtime(&utcTime);
	std::ostringstream s;

	s << utime->tm_hour;
	std::string hour = s.str();
	s.str("");
	s.clear();
	s << utime->tm_min;
	std::string minute = s.str();

	return ("TimeUTC{utcTime=" + hour + " h " + minute + " m" + "}");
}