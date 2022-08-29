#pragma once

#include "entities/Address.h"

/**
 * Maritime Mobile Service Identity (MMSI).
 *
 * ������� ������ �� 10 ����.
 *
 * @author AlexeyVorobyev
 */
class Mmsi : public Address
{
public:

	/**
	 * ���������� MMSI �� ��������.
	 *
	 * ��� �������, MMSI ���������� 5 ���������.
	 *
	 * @param codes �������
	 * @return MMSI
	 */
	static Mmsi fromCodes(std::vector<Code> codes);

	Mmsi();
	Mmsi(long long value);
	~Mmsi();

	long long getValue();
	std::vector<Code> toCodes();

	std::string  toString();

private:

	/** ����� MMSI */
	long long value;
};