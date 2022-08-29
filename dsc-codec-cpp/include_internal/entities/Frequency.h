#pragma once

#include "entities/Transmittable.h"

/**
 * ������������ �������.
 *
 * ������� ������� �� 3 ��������.
 *
 * ������: 0234,56 kHz ����� ������������ ��� 02 34 56.
 *
 * TODO: ��������, � ����� ���� ������ ������� ������� � ��� ������������.
 *
 * @author AlexeyVorobyev
 */
class Frequency : public Transmittable
{
public:

	Frequency();
	Frequency(int value);

	int getValue();
	std::vector<Code> toCodes();
	std::string toString();

	static Frequency fromCodes(std::vector<Code> codes);
	static std::vector<Code> getNoInfoCodes();

private:

	int value;
};
