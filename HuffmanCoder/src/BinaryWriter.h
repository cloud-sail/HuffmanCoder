
#ifndef BINARY_WRITER_H
#define BINARY_WRITER_H
#include <fstream>

class BinaryWriter
{
private:
	std::ofstream file_;
	uint8_t buffer;
	uint8_t N;

	void clear_buffer();
	


public:
	BinaryWriter(const std::string& filename);
	~BinaryWriter();

	void write_bit(bool bit);
	void write_byte(uint8_t byte);
	void write_int(uint32_t i);
	
};


#endif
