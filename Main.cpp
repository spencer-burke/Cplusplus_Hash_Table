#include "Item.hpp"
#include <iostream>
#include <vector>
#include "Hash-Table.hpp"
#include <ostream>
#include <string>
#include <fstream>
#include <iomanip>

Hash_Table* load_file();
void find(Hash_Table* arg);
double calculate_nulls(Hash_Table* arg);
double avg_length_linked_lists(Hash_Table* arg);
void stats(Hash_Table* arg);

double calculate_nulls(Hash_Table* arg) { return 100 * ((double)arg->get_nulls() / (double)arg->get_capacity()); }
double avg_length_linked_lists(Hash_Table* arg) { return (double)(arg->get_capacity() - arg->get_nulls()) / 400; }

Hash_Table* load_file()
{
	Hash_Table* result = new Hash_Table(600);
	std::ifstream infile;
	infile.open("400.txt");
	if(!infile)
		std::cout << "System could not find file specified" << std::endl;
	else
	{
		int id;
		int inv;
		Item* item;
		while(infile.good())
		{
			infile >> id;
			infile >> inv;
			result->add(new Item(id, inv, 0));
		}
	}	
	infile.close();
	return result;
}

void find(Hash_Table* arg)
{
	int find_id;
	Item* location; std::cout << "Testing search algorithm" << std::endl;
	std::cout << "Enter id to search for(-1 to quit): ";
	std::cin >> find_id;

	while(find_id >= 0)
	{
		location = arg->find(find_id);
		if(location == 0)
			std::cout << "Id = " << find_id << " No such part in stock" << std::endl;
		else
			std::cout << "Id = " << location->id << " Inv = " << location->inv << std::endl;
		std::cout << std::endl;
		std::cout << "Enter id to search for(-1 to quit): ";
		std::cin >> find_id;
	} 
}

void stats(Hash_Table* arg)
{
	std::cout << "The \% of null pointers in the hash table: " << std::setprecision(4) << calculate_nulls(arg) << std::endl;
	std::cout << "The average length of(non-null) linked lists: " << std::setprecision(2) <<  avg_length_linked_lists(arg) << std::endl;
	std::cout << "The longest linked list in the hash table: " << arg->get_longest_list() << std::endl; 
}

int main()
{
	Hash_Table* table = load_file();
	int input;
	do
	{
		std::cout << "Hash Table menu" << std::endl;
		std::cout << "(1) Display Hash Table contents" << std::endl;
		std::cout << "(2) Display Hash Table stats" << std::endl;
		std::cout << "(3) Search Hash table" << std::endl;	
		std::cout << "(-1) Quit" << std::endl;
		std::cout << "Option: ";
		std::cin >> input;
		switch(input) 
		{ 
			case 1:
				table->display_contents();
				break;
			case 2:
				stats(table);
				break;
			case 3:
				find(table);
				break;	
		}
	}
	while(input != -1);
}

