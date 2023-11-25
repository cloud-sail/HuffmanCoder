#include "BinaryReader.h"

static constexpr uint8_t BYTE_LEN = 8;

BinaryReader::BinaryReader(const std::string& filename)
	: file_(filename, std::ios::binary), buffer(0), N(BYTE_LEN)
{
	if (!file_.is_open())
	{
		throw std::runtime_error("Error opening file" + filename);
	}
	file_ >> std::noskipws;
	file_ >> buffer;
}

BinaryReader::~BinaryReader()
{
	if (file_.is_open())
	{
		file_.close();
	}
}

bool BinaryReader::read_bit()
{
	N--;
	bool bit = ((buffer >> N) & 1) == 1;
	if (N == 0)
	{
		file_ >> buffer;
		N = BYTE_LEN;
	}
	return bit;
}

uint8_t BinaryReader::read_byte()
{
	uint8_t result = buffer;
	if (N == BYTE_LEN)
	{
		file_ >> buffer;
		return result;
	}  
	result <<= (8 - N);
	file_ >> buffer;
	result |= (buffer >> N);
	return result;
}

uint32_t BinaryReader::read_int()
{
	uint32_t result = 0;
	for (int i = 0; i < 4; i++)
	{
		uint8_t byte = read_byte();
		result <<= 8;
		result |= byte;
	}
	return result;
}

