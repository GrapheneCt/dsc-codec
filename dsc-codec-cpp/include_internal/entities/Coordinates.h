#pragma once

#include "entities/Transmittable.h"

class Quadrant
{
public:

	enum Symbol
	{
		Symbol_NE,
		Symbol_NW,
		Symbol_SE,
		Symbol_SW,
	};

	static Quadrant fromString(std::string s);

	static Quadrant fromCode(int code);

	Quadrant();
	Quadrant(int code);
	~Quadrant();

	int getCode();

	std::string toString();

private:

	int code;
};

/**
 * ������������ ����� ������� ����������, ��� ����������� ������������������.
 *
 * @author AlexeyVorobyev
 */
class Coordinates : public Transmittable
{
public:

	/**
	 * ������ ����� ���������
	 *
	 * @param longitude ������� (5 ����)
	 * @param latitude  ������ (4 �����)
	 * @param quadrant  ��������
	 */
	Coordinates();
	Coordinates(std::string longitude, std::string latitude, Quadrant quadrant);
	Coordinates(std::string longitude, std::string latitude);
	~Coordinates();

	std::string getLongitude();

	std::string getLatitude();

	Quadrant getQuadrant();

	std::vector<Code> toCodes();

	/**
	 * ���������� �������������� ���������� �� ��������.
	 *
	 * ��� ��������� ��������� �� ��������� ������� �� ��� �������.
	 *
	 * @param codes ����
	 * @return ����������
	 */
	static Coordinates fromCodes(std::vector<Code> codes);

	std::string toString();

private:
		
	/**
	 * ���������� �������������� ���������� �� 5 ��������.
	 *
	 * ���������� ��-�� ����, ��� ��������� ��� ����� ����� �� ���.
	 *
	 * @param codes ����
	 * @return ����������
	 */
	static Coordinates fromCodes5(std::vector<Code> codes);

	/**
	 * ���������� �������������� ���������� �� 3 ��������.
	 *
	 * ���������� ��-�� ����, ��� ��������� ��� ����� ����� �� ���.
	 *
	 * @param codes ����
	 * @return ����������
	 */
	static Coordinates fromCodes3(std::vector<Code> codes);

	/** �������. ������� �� 5 ����: ��������(3) � �����(2) */
	std::string longitude;

	/** ������. ������� �� 4 ����: ��������(2) � �����(2) */
	std::string latitude;

	Quadrant quadrant;
};
