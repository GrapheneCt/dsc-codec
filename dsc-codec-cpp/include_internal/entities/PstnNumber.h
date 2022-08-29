#pragma once

#include "entities/Transmittable.h"

/**
 * PSTN номер.
 *
 * У номера нет фиксированного размера, но есть ограничение до 16 цифр.
 *
 * @author AlexeyVorobyev
 */
class PstnNumber : public Transmittable
{
public:

	PstnNumber();

	/**
	 * Создаёт PSTN номер
	 *
	 * @param number строковое представление номера, состоящее из 16 цифр
	 */
	PstnNumber(std::string number);

	/**
	 * Декодирует и возвращает PSTN номер из переданных кодов
	 *
	 * @param codes 8 кодов для декодирования
	 * @return декодированный PSTN
	 */
	static PstnNumber fromCodes(std::vector<Code> codes);

	/**
	 * При передаче PSTN номера необходимо передавать 8 символов.
	 *
	 * В случае, если номер отсутствует, достаточно передать 1 нулевой символ.
	 *
	 * @see Transmittable#toCodes()
	 */
	std::vector<Code> toCodes();

	std::string toString();

private:

	bool checkFormat(std::string num);

	std::string number;
};