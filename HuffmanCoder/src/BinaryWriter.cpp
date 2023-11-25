#include "BinaryWriter.h"

static constexpr uint8_t BYTE_LEN = 8;

BinaryWriter::BinaryWriter(const std::string& filename)
	: file_(filename, std::ios::binary), buffer(0), N(0)
{
	if (!file_.is_open())
	{
		throw std::runtime_error("Error opening file" + filename);
	}
}

BinaryWriter::~BinaryWriter()
{
	if (file_.is_open())
	{
		clear_buffer();
		file_.close();
	}
}

void BinaryWriter::clear_buffer()
{
	if (N == 0) return;
	buffer <<= (8 - N);
	file_ << buffer;
	buffer = 0;
	N = 0;
}

void BinaryWriter::write_bit(bool bit)
{
	buffer <<= 1;
	if (bit) buffer |= 1;
	N++;
	if (N == BYTE_LEN) clear_buffer();
}

void BinaryWriter::write_byte(uint8_t byte)
{
	if (N == 0)
	{
		file_ << byte;
		return;
	}

	for (uint8_t i = 0; i < BYTE_LEN; i++)
	{
		bool bit = ((byte >> (8 - i - 1)) & 1) == 1;
		write_bit(bit);
	}
}


void BinaryWriter::write_int(uint32_t i)
{
	write_byte((i >> 24) & 0xff);
	write_byte((i >> 16) & 0xff);
	write_byte((i >> 8) & 0xff);
	write_byte((i >> 0) & 0xff);
}
