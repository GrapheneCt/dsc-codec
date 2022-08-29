#pragma once

#include "entities/Transmittable.h"

/**
 * PSTN �����.
 *
 * � ������ ��� �������������� �������, �� ���� ����������� �� 16 ����.
 *
 * @author AlexeyVorobyev
 */
class PstnNumber : public Transmittable
{
public:

	PstnNumber();

	/**
	 * ������ PSTN �����
	 *
	 * @param number ��������� ������������� ������, ��������� �� 16 ����
	 */
	PstnNumber(std::string number);

	/**
	 * ���������� � ���������� PSTN ����� �� ���������� �����
	 *
	 * @param codes 8 ����� ��� �������������
	 * @return �������������� PSTN
	 */
	static PstnNumber fromCodes(std::vector<Code> codes);

	/**
	 * ��� �������� PSTN ������ ���������� ���������� 8 ��������.
	 *
	 * � ������, ���� ����� �����������, ���������� �������� 1 ������� ������.
	 *
	 * @see Transmittable#toCodes()
	 */
	std::vector<Code> toCodes();

	std::string toString();

private:

	bool checkFormat(std::string num);

	std::string number;
};