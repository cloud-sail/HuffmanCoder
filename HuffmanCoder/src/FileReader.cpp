#include "FileReader.h"


FileReader::FileReader(const std::string& filename) : file_(filename, std::ios::binary)
{
	if (!file_.is_open())
	{
		throw std::runtime_error("Error opening file" + filename);
	}

}

FileReader::~FileReader()
{
	if (file_.is_open())
	{
		file_.close();
	}
}


bool FileReader::read_byte(char& byte)
{
	return static_cast<bool>(file_.get(byte));
}

std::streampos FileReader::size()
{
	file_.seekg(0, std::ios::end);
	const std::streampos length = file_.tellg();
    file_.seekg(0, std::ios::beg);
    return length;
}
