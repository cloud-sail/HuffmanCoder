# Huffman Coder README

This Huffman coder is a program designed to compress and decompress files, developed using Visual Studio 2022 on Windows.

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

Please change directory to testcase and run command below.
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