#pragma once

#include "entities/Transmittable.h"

/**
 * Представляет частоту.
 *
 * Частота состоит из 3 символов.
 *
 * Пример: 0234,56 kHz будет представлена как 02 34 56.
 *
 * TODO: Выяснить, в каком типе данных удобнее хранить и как представлять.
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
