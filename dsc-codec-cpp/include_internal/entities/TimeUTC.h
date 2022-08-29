#pragma once

#include <vector>
#include <sstream>
#include <time.h>

#include "entities/Transmittable.h"

/**
 * �����-������ ��� ������������� ������� � UTC � �����������.
 *
 * @author AlexeyVorobyev
 */
class TimeUTC : public Transmittable
{
public:

	/**
	 * ������ ��������� ��� ���������� ������� �� UTC
	 *
	 * @param utcTime ����� �� UTC
	 */
	TimeUTC(time_t utcTime);

	/** ������ �������� ��� ������� (���� � ������ ����� 88) */
	TimeUTC();

	time_t getUtcTime();
	std::vector<Code> toCodes();
	std::string toString();

	/**
	 * ���������� ����� �� UTC.
	 *
	 * ��� ������������� ���������� 2 ������� (���� � ������).
	 *
	 * @param codes ���� ��� �������������
	 * @return ����� �� UTC
	 */
	static TimeUTC fromCodes(std::vector<Code> codes);

	/**
	 * ���������� ������� ����� �� UTC
	 *
	 * @return ������� ����� �� UTC
	 */
	static TimeUTC now();

private:

	time_t utcTime;
	bool valid;
};
