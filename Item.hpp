#pragma once
#include <string>
#include <vector>

struct Item 
{
	int id;
	int inv;
	Item* next;	
	std::string to_string();
	Item(int a_id, int a_inv, Item* a_next) : id(a_id), inv(a_inv), next(a_next) {}
};
typedef std::string string;
typedef Item* Item_ptr;

string make_string_even(string arg);
std::vector<string> fold(string arg);
int calculate_hash(std::vector<string> fold, int id, int capacity);
int hash(int id, int capacity);

string make_string_even(string arg)
{
	if(arg.length() % 2 != 0)
		return arg + "0";
	else
		return arg;
}

std::vector<string> fold(string arg)
{
	std::vector<string> result;
	int folded_index = 1;
	for(int i = 0; i < arg.length(); i++)
	{
		if((i+1) & 2 == 0)
			result.push_back(arg.substr(i-1, 2));
	}
	return result;
}

int calculate_hash(std::vector<string> fold, int id, int capacity)
{
	int hash = 1;
	for(string i : fold)
		hash = hash * std::stoi(i);
	hash += id;
	hash = hash % (capacity-1);
	return hash;
}

int hash(int id, int capacity)
{
	string str_id = std::to_string(id);
	str_id = make_string_even(str_id);
	std::vector<string> folded_id = fold(str_id);
	return calculate_hash(folded_id, id, capacity);
}

string Item::to_string()
{
	string result = "";
	result += "ID:";
	result += std::to_string(this->id);
	result += " ";
	result += "INV:";
	result += std::to_string(this->inv);
	return result;
}

