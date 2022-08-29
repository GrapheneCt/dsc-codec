#pragma once

#include "entities/Address.h"

/**
 * Maritime Mobile Service Identity (MMSI).
 *
 * Состоит строго из 10 цифр.
 *
 * @author AlexeyVorobyev
 */
class Mmsi : public Address
{
public:

	/**
	 * Возвращает MMSI из символов.
	 *
	 * Как правило, MMSI кодируется 5 символами.
	 *
	 * @param codes символы
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

	/** Номер MMSI */
	long long value;
};