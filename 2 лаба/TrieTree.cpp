#include "TrieTree.h"


void TrieTree::domesticClear(TTrie &node)
{
	if (node->alph[0] != nullptr)domesticClear(node->alph[0]);
	node->alph[0] = nullptr;

	if (node->alph[1] != nullptr)domesticClear(node->alph[1]);
	node->alph[1] = nullptr;

	if (node->alph[2] != nullptr) domesticClear(node->alph[2]);
	node->alph[2] = nullptr;

	for (int i = 0; i < 3; i++) {
		delete node->alph[i];
		node->alph[i] = nullptr;
	}
	
}

void TrieTree::domesticRemove(TTrie &r, std::string num, int i, int size)
{
	if (i < size)
		domesticRemove(r->alph[num[i] - '0'], num, i + 1, size);
	
	if (i == size)
		r->alph[2] = nullptr;

	if (r->alph[0] == nullptr && r->alph[1] == nullptr && r->alph[2] == nullptr)
	{
		for (int i = 0; i < 3; i++) {
			delete r->alph[i];
			r->alph[i] = nullptr;
		}
	}


}

TrieTree::TrieTree() : root(new TrieNode), tail(new TrieNode) {};


TrieTree::~TrieTree()
{
	clear();
	delete root;
	delete tail;
}

void TrieTree::clear()
{
	domesticClear(root);

	root = new TrieNode;
	tail = new TrieNode;
}

void TrieTree::add(std::string num)
{
	TrieNode* newRoot = root;
	for (int i = 0; i < num.size(); i++)
	{
		if (newRoot->alph[num[i] - '0'] != nullptr)
		{
			newRoot = newRoot->alph[num[i] - '0'];
		}
		else
		{
			newRoot->alph[num[i] - '0'] = new TrieNode;
			newRoot = newRoot->alph[num[i] - '0'];
		}

	}
	newRoot->alph[2] = tail;
}

bool TrieTree::numberFind(std::string num)
{
	bool flag = true;
	TrieNode* newRoot = root;
	int i = 0;
	while (flag && i < num.size())
	{
		if (newRoot->alph[num[i] - '0'] == nullptr)
			flag = false;
		else {
			newRoot = newRoot->alph[num[i] - '0'];
			i++;
		}
	}
	if (newRoot->alph[2] != tail)
		flag = false;
	return flag;
}

void TrieTree::remove(std::string num)
{
	if (numberFind(num) == true)
		domesticRemove(root, num, 0, num.size());
}

std::string TrieTree::xOr(std::string num)
{
	std::string result;
	int max = 0;
	domesticXOR(root, num, result, num.size(), 0,max);
	return result;

}


void TrieTree::domesticXOR(TrieNode* r,std::string num,std::string& result, int size,int ind,int& max)
{
	static int countDif = 0;
	static std::string str;

	if (r->alph[2] == tail) {

		int curDif = 0;
		if (ind <num.size())
			for (int i = ind; i < num.size(); i++) {
				if (num[i] == '1')
					curDif++;
			}


		if (curDif+countDif+1 > max)
		{
			max = countDif+curDif;
			result = str;
		}

	}

	/////////////////////////

	if (r->alph[0] != nullptr)
	{
		if (ind<num.size()&&num[ind] == '1')countDif++;

		if (countDif > max)
			max = countDif;

		str += '0';
		domesticXOR(r->alph[0], num, result, size, ind+1,max);

	}
	if (ind < num.size() && r->alph[0] != nullptr && num[ind] != '0')
		countDif--;

	if (r->alph[0] != nullptr)
		str.pop_back();
	


	///////////////////////////////

	if (r->alph[1] != nullptr)
	{
		if (ind < num.size() && num[ind] == '0')countDif++;

		if (ind >= num.size())
			countDif++;

		if (countDif > max)
			max = countDif;

		str += '1';
		domesticXOR(r->alph[1], num, result, size, ind+1,max);

	}
	if (ind < num.size() && r->alph[1] != nullptr && num[ind] != '1')
		countDif--;
	if (ind >= num.size() && r->alph[1] != nullptr)
		countDif--;

	if (r->alph[1] != nullptr)
		str.pop_back();

}
