#pragma once

#include <vector>

#include "entities/Code.h"

/**
 * Интерфейс для сущностей, которые могут быть переданы через передатчик в
 * составе ЦИВа.
 *
 * @author AlexeyVorobyev
 */
class Transmittable
{
public:

	/**
	 * Конвертирует сущность в символы для передачи
	 *
	 * @return символы для передачи
	 */
	virtual std::vector<Code> toCodes()
	{
		return std::vector<Code>();
	}
};