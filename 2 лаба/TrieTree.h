#pragma once

#include<string>

class TrieTree
{
	struct TrieNode
	{
		TrieNode* alph[3];
		
		TrieNode()
		{
			for (int i = 0; i < 3; i++)
				alph[i] = nullptr;
		}
	};

	typedef TrieNode* TTrie;
	TrieNode* root;
	TrieNode* tail;

	void domesticClear(TTrie& node);
	void domesticRemove(TTrie& r, std::string num, int i, int size);
	void domesticXOR(TrieNode* r, std::string num, std::string& result, int size, int ind, int& max);

public:

	TrieTree();
	~TrieTree();

	void clear();
	void add(std::string num);
	bool numberFind(std::string num);
	void remove(std::string num);

	std::string xOr(std::string num);
};