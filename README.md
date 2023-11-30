# Huffman Coder

This Huffman coder is a program designed to compress and decompress files, developed using Visual Studio 2022 on Windows.

Name: Yunfan He
Date: 2023/11/21-2023/11/25

## Directory structure
In src folder, there are 5 class:
* BinaryReader
* BinaryWriter
* FileReader
* FileWriter
* Huffman

## Code explanation
The biggest challenge in this project was implementing the reading of binary files, where reading and writing files require bit-level operations, while the minimum unit of file reading is a byte. This needs to maintain a buffer to handle binary file operations. Additionally, serializing and deserializing Huffman trees was another significant aspect.

In this project, I used RAII (Resource Acquisition Is Initialization) to write all my classes. I believe RAII offers the following two advantages:

Resource Management: RAII ensures effective resource management by guaranteeing resource availability within an object's lifetime and proper release when the object goes out of scope. This includes various resources such as memory, file handles, locks, network connections, etc.

Exception Safety: RAII ensures exception safety by invoking an object's destructor in case of exceptions, ensuring proper resource cleanup and preventing resource leaks. This maintains program consistency, avoiding half-initialized or unhandled resources.

## Simple performance analysis
In testcase folder, I compress and depress diffrent types of files and compare the size.
* long text: 1448049 -> 1106153
* picture: 2023902 -> 2023167
* single char text: 19 -> 8
* video 138439KB -> 138096KB
* pdf 3415KB -> 3367KB

## Installation and Running

### Requirements

- Windows operating system
- Visual Studio 2022 or a compatible version

### Download and Build

1. Clone this repository or download the source code as a ZIP file.
2. Open the project file using Visual Studio 2022.
3. Build the project in Visual Studio to generate HuffmanCoder.exe.

### Usage

The program offers two primary functionalities: compressing and decompressing files.

#### Compressing Files

To compress a file, run the program using the following format:

```shell
HuffmanCoder.exe -c inputFileName compressedFileName
```

- `-c`: Represents the compression operation.
- `inputFileName`: Path to the input file you want to compress.
- `compressedFileName`: Path and name for the compressed output file.

#### Decompressing Files

To decompress a file, use the program with the following format:

```shell
HuffmanCoder.exe -x compressedFileName outputFileName
```

- `-x`: Indicates the decompression operation.
- `compressedFileName`: Path to the compressed file you want to decompress.
- `outputFileName`: Path and name for the decompressed output file.

## Examples

### Compressing File Example

Please change directory to `testcase` and run command below.
```shell
.\HuffmanCoder.exe -c .\picture.png .\compressed\picture
.\HuffmanCoder.exe -c .\empty.txt .\compressed\empty
.\HuffmanCoder.exe -c .\long_text.txt .\compressed\long
.\HuffmanCoder.exe -c .\single_char.txt .\compressed\single
```

### Decompressing File Example

```shell
.\HuffmanCoder.exe -x .\compressed\picture .\extracted\picture.png
.\HuffmanCoder.exe -x .\compressed\single .\extracted\single.txt
.\HuffmanCoder.exe -x .\compressed\long .\extracted\long.txt
.\HuffmanCoder.exe -x .\compressed\single .\extracted\single.txt
```

## Notes

- Ensure that the input file exists and the paths are correct.
- Make sure the file to compress is less than 4GB.