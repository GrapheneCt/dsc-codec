#include "entities/Transmittable.h"
#include "entities/PstnNumber.h"

PstnNumber::PstnNumber()
{

}

PstnNumber::PstnNumber(std::string number)
{
	if (!checkFormat(number)) {
		printf("PSTN ����� ������ �������� �� ����! ��������: %s � �������� %d\n", number.c_str(), number.length());
		abort();
	}

	this->number = number;
}

PstnNumber PstnNumber::fromCodes(std::vector<Code> codes)
{
	//std::string number = codes.stream().reduce("", (c1, c2)->c1 + c2.getSymbol(), (c1, c2)->c1 + c2);
	printf("������� PstnNumber::fromCodes() �� �����������. ����� ��������� ������� PSTN\n");

	return PstnNumber("0000000000000000");
}

std::vector<Code> PstnNumber::toCodes()
{
	std::vector<Code> codes;

	/*
	StringBuilder builder = new StringBuilder(number);
	// ���� ������ ������ 16, �� ���������� ��������� ��� ������ �������
	int numLength = number.length();
	if (numLength < 16) {
		while (builder.length() != 16) {
			builder.insert(0, "0");
		}
	}

	String[] numArray = builder.toString().split("(?<=\\G..)");

	for (String s : numArray) {
		codes.add(new Code(Integer.parseInt(s)));
	}
	*/

	printf("������� PstnNumber::toCodes() �� �����������. ����� ��������� ������� PSTN\n");

	for (int i = 0; i < 8; i++)
	{
		codes.push_back(Code(0));
	}

	return codes;
}

std::string PstnNumber::toString()
{
	if (number == "0000000000000000") {
		return "PstnNumber{EMPTY}";
	}

	return "PstnNumber{" + number + "}";
}


bool PstnNumber::checkFormat(std::string num)
{
	return (num.find_first_not_of("0123456789") == std::string::npos);
}