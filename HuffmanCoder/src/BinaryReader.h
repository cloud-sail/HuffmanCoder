#ifndef BINARY_READER_H
#define BINARY_READER_H
#include <fstream>

class BinaryReader
{
private:
	std::ifstream file_;
	uint8_t buffer;
	uint8_t N;

public:
	BinaryReader(const std::string& filename);
	~BinaryReader();

	bool read_bit();
	uint8_t read_byte();
	uint32_t read_int();
};
#endif
