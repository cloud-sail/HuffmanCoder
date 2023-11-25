#ifndef FILE_READER_H
#define FILE_READER_H
#include <fstream>


class FileReader
{
private:
	std::ifstream file_;

public:
	FileReader(const std::string& filename);
	~FileReader();

	bool read_byte(char & byte);
	std::streampos size();
};

#endif
