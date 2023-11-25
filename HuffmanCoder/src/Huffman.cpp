#include <algorithm>
#include <map>
#include <iostream>
#include <queue>
#include "Huffman.h"

#include <csignal>

#include "BinaryReader.h"
#include "BinaryWriter.h"
#include "FileReader.h"
#include "FileWriter.h"


Huffman::Huffman() : root_(nullptr)
{
}

Huffman::~Huffman()
{
	if (root_ != nullptr) delete_tree(root_);
}


void Huffman::build_tree(const std::string& filename)
{
	FileReader file(filename);
	std::map<char, long long> freq_table;
	char data;
	while(file.read_byte(data))
	{
		freq_table[data]++;
	}
	// print frequency table
	std::for_each(freq_table.begin(), freq_table.end(), [](const std::pair<char, long long>& element)
	{
		std::cout << "Key: " << element.first << ", Value: " << element.second << std::endl;
	});
	
	std::priority_queue < HNode*, std::vector<HNode*>, CompareFrequency> pq;
	std::for_each(freq_table.begin(), freq_table.end(), [&pq](const std::pair<char, long long>& element)
	{
		HNode* node = new HNode(element.first, element.second, nullptr, nullptr);
		pq.push(node);
	});
	while (pq.size()>1)
	{
		HNode* left = pq.top();
		pq.pop();
		HNode* right = pq.top();
		pq.pop();
		HNode* new_node = new HNode('\0', left->freq + right->freq, right, left);
		pq.push(new_node);
	}

	if (pq.empty()) throw std::runtime_error("file is empty " + filename);
	root_ = pq.top();
}

void Huffman::build_codes(const HNode* node, std::vector<bool>& code)
{
	if (node == nullptr)
	{
		std::cout << "Warning: node is null" << std::endl;
		return;
	}
	if (node->left == nullptr && node->right == nullptr)
	{
		codes_[node->data] = code;
		return;
	}
	code.push_back(false);
	build_codes(node->left, code);
	code.pop_back();
	code.push_back(true);
	build_codes(node->right, code);
	code.pop_back();
}

void Huffman::print_codes()
{
	for (const auto& pair : codes_) {
		std::cout << pair.first << ": ";
		for (bool bit : pair.second) {
			std::cout << bit;
		}
		std::cout << std::endl;
	}
}

void Huffman::handle_one_node_case()
{
	if (codes_.size() == 1) {
		const auto it = codes_.begin();
		char key = it->first;
		std::vector<bool>& vec = it->second;

		vec.push_back(false);
	}
}

void Huffman::write_tree(const HNode* node, BinaryWriter& writer)
{
	if (node == nullptr)
	{
		std::cout << "Warning: node is null" << std::endl;
		return;
	}
	if (node->left == nullptr && node->right == nullptr)
	{
		writer.write_bit(true);
		writer.write_byte(node->data);
		return;
	}
	writer.write_bit(false);
	write_tree(node->left, writer);
	write_tree(node->right, writer);
}

HNode * Huffman::read_tree(BinaryReader& reader)
{
	if (reader.read_bit())
	{
		return new HNode(reader.read_byte(), -1, nullptr, nullptr);
	}
	auto left = read_tree(reader);
	auto right = read_tree(reader);
	return new HNode('\0', -1, left, right);
}


void Huffman::delete_tree(HNode* node)
{
	if (node != nullptr) return;
	if (node->left) delete_tree(node->left);
	if (node->right) delete_tree(node->right);
	delete node;
	node = nullptr;
}


void Huffman::encode(const std::string& input_file, const std::string& output_file)
{
	build_tree(input_file);
	std::cout << "Root pointer: " << root_ << std::endl;
	std::vector<bool> code;
	build_codes(root_, code);
	handle_one_node_case();
	print_codes();

	BinaryWriter writer(output_file);
	write_tree(root_, writer);
	FileReader reader(input_file);
	uint32_t length = static_cast<uint32_t>(reader.size());
	writer.write_int(length);
	char data;
	while (reader.read_byte(data))
	{
		std::vector<bool> &temp = codes_[data];
		for (auto it = temp.begin();it!=temp.end();++it)
		{
			writer.write_bit(*it);
		}
	}
}

void Huffman::decode(const std::string& input_file, const std::string& output_file)
{
	BinaryReader reader(input_file);
	root_ = read_tree(reader);
	// print huffman codes
	std::vector<bool> code;
	build_codes(root_, code);
	handle_one_node_case();
	print_codes();

	uint32_t length = reader.read_int();
	FileWriter writer(output_file);
	for (uint32_t i = 0; i < length; i++)
	{
		HNode* cur = root_;
		while (cur->left != nullptr || cur->right != nullptr)
		{
			if (reader.read_bit())
			{
				cur = cur->right;
			}
			else
			{
				cur = cur->left;
			}
		}
		writer.write_byte(cur->data);
	}
}
