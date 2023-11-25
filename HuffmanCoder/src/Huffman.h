#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <string>
#include <unordered_map>

#include "BinaryReader.h"
#include "BinaryWriter.h"


struct HNode
{
	char data;
	long long freq;
	HNode* left;
	HNode* right;
	HNode(char d, long long f, HNode* l = nullptr, HNode* r = nullptr)
		:data(d), freq(f), left(l), right(r) {}
};


class CompareFrequency
{
public:
	bool operator()(const HNode* x, const HNode* y)
	{
		return x->freq > y->freq;
	}
};



class Huffman
{
private:
	HNode* root_;
	std::unordered_map<char, std::vector<bool>> codes_;

public:
	Huffman();
	~Huffman();
	void encode(const std::string& input_file, const std::string& output_file);
	void decode(const std::string& input_file, const std::string& output_file);

private:
	void build_tree(const std::string& filename);
	void build_codes(const HNode* node, std::vector<bool> &code);
	void print_codes();
	void handle_one_node_case();
	void write_tree(const HNode* node, BinaryWriter &writer);

	HNode * read_tree(BinaryReader &reader);

	void delete_tree(HNode* node);

};

#endif

