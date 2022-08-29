#pragma once

#include <vector>

#include "entities/Code.h"

/**
 * ��������� ��� ���������, ������� ����� ���� �������� ����� ���������� �
 * ������� ����.
 *
 * @author AlexeyVorobyev
 */
class Transmittable
{
public:

	/**
	 * ������������ �������� � ������� ��� ��������
	 *
	 * @return ������� ��� ��������
	 */
	virtual std::vector<Code> toCodes()
	{
		return std::vector<Code>();
	}
};