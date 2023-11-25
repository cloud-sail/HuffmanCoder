#include "FileWriter.h"

FileWriter::FileWriter(const std::string& filename) : file_(filename, std::ios::binary)
{
	if (!file_.is_open())
	{
		throw std::runtime_error("Error opening file" + filename);
	}

}

FileWriter::~FileWriter()
{
	if (file_.is_open())
	{
		file_.close();
	}
}

void FileWriter::write_byte(char& byte)
{
	file_.put(byte);
}
