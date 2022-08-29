#include <iostream>
#include <fstream>

#include "distress/Distress.h"
#include "decoder/DscDecoder.h"

char bits2byte(char *bits)
{
	char byte = 0;

	byte |= bits[0] << 0;
	byte |= bits[1] << 1;
	byte |= bits[2] << 2;
	byte |= bits[3] << 3;
	byte |= bits[4] << 4;
	byte |= bits[5] << 5;
	byte |= bits[6] << 6;
	byte |= bits[7] << 7;

	return byte;
}

class MyListener : public DecoderListener
{
public:

	virtual void onIncomeDsc(DigitalSelectiveCall *call)
	{
		std::cout << "onIncomeDsc: " << call->toString() << "\n";
	}

	virtual void onDotPatternFound()
	{
		std::cout << "onDotPatternFound\n";
	}
};

int main()
{
	// Длина массива битовых символов
	int dscSize = 0;

	// Составление сообщения типа Distress в программном виде
	Distress *distress = new Distress(
		Mmsi(123456789),
		DistressNature(DistressNature::Symbol_COLLISION),
		Coordinates("12345", "4321", Quadrant(Quadrant::Symbol_SW)),
		TimeUTC(),
		FirstTelecommand(FirstTelecommand::Symbol_F1B_J2B_TTY_FEC)
	);

	std::cout << distress->toString() << "\n";

	// Кодирование составленного сообщения в форму DSC.
	// В полученном массиве каждый байт имеет значение 0 или 1 и соответствует биту в сообщении DSC
	// Для конвертации полученного массива в массив "настоящих" байт сообщения используется функция bits2byte()
	char *dsc = distress->encode(&dscSize);

	// Вывод в файлы: dsc_bits.bin - исходный массив, см. комментарий выше
	//                dsc.bin - массив "настоящих" байт сообщения
	std::ofstream ofile;
	ofile.open("dsc.bin");

	for (int i = 0; i < dscSize / 8; i++) {
		ofile << bits2byte(&dsc[i * 8]);
	}

	ofile.close();

	std::ofstream ofile2;
	ofile2.open("dsc_bits.bin");

	for (int i = 0; i < dscSize; i++) {
		ofile2 << dsc[i];
	}

	ofile2.close();

	//dscSize = sizeof(dsc);

	// Для уменьшения ложных срабатываний декодирование начинается только при приеме части сообщения (phasing sequence)
	// DSC 2 или более раза. Для имитации этого создаем массив в котором наше сообщение Distress
	// повторяется 4 раза
	char *myDsc = new char[dscSize * 4];
	for (int i = 0; i < 4; i++) {
		memcpy(myDsc + i * dscSize, dsc, dscSize);
	}
	dsc = myDsc;
	dscSize *= 4;

	// Универсальный декодер
	DscDecoder *dscDecoder = new DscDecoder();

	// "Слушатель" декодера - не обязателен
	MyListener *listener = new MyListener();

	dscDecoder->addListener(listener);

	// В реальной обстановке полученные биты сообщени я могут поступать в декодер фрагментированно.
	// Декодер имеет внутренний буфер размером 2000 байт и автоматечески сообщает слушателю если в нем
	// обнаруживается сообщение
	for (int i = 0; i < dscSize; i += 1) {
		dscDecoder->onBit(dsc[i]);
	}
}
