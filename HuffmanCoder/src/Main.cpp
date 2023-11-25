#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "FileReader.h"
#include "Huffman.h"


int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " -c input compressedFile | -x compressedFile output.txt" << std::endl;
        return 1;
    }
    std::vector<std::string> args(argv, argv + argc);
    const std::string compress_mode(args[1]), input_file(args[2]), output_file(args[3]);

    std::cout << "compress_mode: " << compress_mode << std::endl;
    std::cout << "input_file: " << input_file << std::endl;
    std::cout << "output_file: " << output_file << std::endl;

    // check empty file and large file
    FileReader in_file(input_file);
    auto input_file_size= in_file.size();
    std::cout << input_file_size << std::endl;
    if (input_file_size == 0)
    {
        std::ofstream out_file(output_file);
        out_file.close(); 
        std::cout << "Empty file created." << std::endl;
        return 0;
    } else if(input_file_size > UINT32_MAX)
    {
        std::cerr<< "Input file is too large!" << std::endl;
        return 1;
    }

    Huffman huffman;
    if (compress_mode == "-c")
    {
        huffman.encode(input_file, output_file);
    }
    else if (compress_mode == "-x")
    {
        huffman.decode(input_file, output_file);
    } else
    {
        std::cerr << "Wrong mode!" << std::endl;
        return 1;
    }

    return 0;
}
