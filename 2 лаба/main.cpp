#include<iostream>
#include"TrieTree.h"

std::string binary(int num);
int decimal(std::string num);
void XOR(TrieTree tree, int* mas, int size);

int check();

int main()
{
	setlocale(0, "");

	TrieTree tree;
	
	std::cout << "Напишите количество чисел и количество запросов\n";
	int n = check(), q = check();

	std::cout << "Введите "<<n<<" целых чисел\n";
	int a;
	for (int i = 0; i < n; i++)
	{
		a = check();
		tree.add(binary(a));
	}

	std::cout << "Введите " << q << " чисел\n";
	int x;
	int* mas = new int[q];
	for (int i = 0; i < q; i++)
	{
		x = check();
		mas[i] = x;
	}

	XOR(tree, mas, q);

	std::cout << "Ответ:\n";
	for (int i = 0; i < q; i++)
		std::cout << mas[i] << std::endl;

	return 0;
}

std::string binary(int num)
{
	std::string result;
	int wholePart = 1, remnant;

	while (wholePart)
	{
		wholePart = num / 2;
		remnant = num % 2;
		num /= 2;
		result += remnant + '0';
	}

	return result;
}

int decimal(std::string num)
{
	int result = 0;
	for (int i = 0; i < num.size(); i++)
	{
		result += (num[i]-'0') * pow(2, i);
	}

	return result;
}

void XOR(TrieTree tree, int* mas, int size)
{
	std::string result;
	for (int i = 0; i < size; i++)
	{
		result = binary(mas[i]);
		mas[i] = decimal(tree.xOr(result));

	}
	
}

int check()
{
	int x;
	std::cin >> x;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "Нужно ввести число\n";
		std::cin >> x;
	}
	return x;
}