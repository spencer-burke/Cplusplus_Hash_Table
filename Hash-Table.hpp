#pragma once
#include "Item.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using std::vector;

class Hash_Table 
{
	private:
		const int capacity;
		int size;
		vector<Item*> hash_table;		
		Item* find_at_index(int find_id, int index);
		int get_length_at_index(Item* arg);
		std::string list_to_string(int index);
		std::string node_to_string(Item* arg);
	public:
		Hash_Table(int a_capacity);	
		int get_capacity() const;
		int get_size();
		void display_contents();
		void add(Item* arg);
		Item* find(int find_id);	
		int get_nulls();
		int get_longest_list();
		void load_file();
};

Hash_Table::Hash_Table(int a_capacity) : size(0), capacity(a_capacity) 
{ 
	hash_table.resize(capacity); 
	for(int i = 0; i < this->capacity; i++)
		hash_table.at(i) = 0;
}

int Hash_Table::get_capacity() const { return this->capacity; }
int Hash_Table::get_size() { return this->size; }

void Hash_Table::add(Item* arg)
{
	int index = hash(arg->id, this->capacity);
	if(this->hash_table.at(index) == 0)	
		this->hash_table.at(index) = arg;
	else
	{
		Item* curr = this->hash_table.at(index);
		while(curr->next != 0)
			curr = curr->next;
		curr->next = arg;
	}
	size++;
}

void Hash_Table::display_contents()
{
	for(int i = 0; i < this->capacity; i++)
	{
		if(i < 99)
		{
			if(i < 9)
				std::cout << "00" << i + 1 << ": " << this->list_to_string(i) << std::endl; 	
			else
				std::cout << "0" << i + 1 <<  ": " << this->list_to_string(i) << std::endl; 
		}
		else
			std::cout << i + 1 << ": " << this->list_to_string(i) << std::endl; 
	}
}

Item* Hash_Table::find(int find_id)
{
	Item* result; 
	Item* curr;
	int index = hash(find_id, this->capacity);
	curr = this->hash_table.at(index);
	if(curr != 0)
	{	
		if(curr->id == find_id)
			return  this->hash_table.at(index);	
		else 
			return  this->find_at_index(find_id, index);	
	}
	else
		return 0;	
}

Item* Hash_Table::find_at_index(int find_id, int index)
{
	Item* curr = this->hash_table.at(index)->next;
	while(curr != 0)
	{
		if(curr->id == find_id)
			return curr;
		curr = curr->next;
	}
	return 0;
}

int Hash_Table::get_nulls()
{
	int result = 0;
	for(int i = 0; i < this->capacity; i++)
		if(this->hash_table.at(i) == 0)
			result++;
	return result;
}

int Hash_Table::get_length_at_index(Item* arg)
{
	int result = 0;
	while(arg != 0)
	{
		arg = arg->next;
		result++;
	}	
	return result;
}

int Hash_Table::get_longest_list()
{
	int result = 0;
	if(this->hash_table.at(0) != 0)
		result = get_length_at_index(this->hash_table.at(0));
	for(int i = 0; i < this->capacity; i++)
		if(this->hash_table.at(i) != 0)
			if(this->get_length_at_index(this->hash_table.at(i)) >= result)
				result = get_length_at_index(this->hash_table.at(i));
	return result;
}

std::string Hash_Table::list_to_string(int index)
{
	Item* curr = this->hash_table.at(index);
	std::string result = "";
	if(curr != 0)
	{
		result += this->node_to_string(curr);
		if(curr->next != 0)
		{
			curr = curr->next;
			while(curr != 0)
			{
				result += this->node_to_string(curr);
				curr = curr->next;
			}
		}	
	}
	else
		result = " ";
	return result;
}

std::string Hash_Table::node_to_string(Item* arg)
{
	std::string result = "[";
	result += arg->to_string();	
	result += "] ";
	return result;
}

