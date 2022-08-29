# Codec (coder/decoder) for Digitical Selective Call, C++ version
COder/DECoder of Digital Selective Call (DSC), C++ version
## Description
This codec implements R-REC-M.493-14-201509
## Quick start
### Transmission
- Transmit Distress message to file
```
Distress *distress = new Distress(
	Mmsi(123456789),
	DistressNature(DistressNature::Symbol_COLLISION),
	Coordinates("12345", "4321"),
	TimeUTC(),
	FirstTelecommand(FirstTelecommand::Symbol_F1B_J2B_TTY_FEC)
);

std::cout << distress->toString();

char *dsc = distress->encode(&dscSize);

std::ofstream ofile;
ofile.open("dsc_bits.bin");

for (int i = 0; i < dscSize; i++) {
	ofile << dsc[i];
}

ofile.close();
```
### Receive
- Receive Distress message from array
```
DscDecoder *dscDecoder = new DscDecoder();
MyListener *listener = new MyListener();

dscDecoder->addListener(listener);

for (int i = 0; i < dscSize; i += 1) {
	dscDecoder->onBit(dsc[i]);
}
```

## Credits
[Original project](https://github.com/vorobuev/dsc-codec)
