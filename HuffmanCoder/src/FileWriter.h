#ifndef FILE_WRITER_H
#define FILE_WRITER_H
#include <fstream>


class FileWriter
{
private:
	std::ofstream file_;

public:
	FileWriter(const std::string& filename);
	~FileWriter();

	void write_byte(char& byte);
};

#endif
