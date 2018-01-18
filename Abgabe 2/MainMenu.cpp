/*
 * main.cpp
 *
 *  Created on: 07.12.2017
 *      Author: Stefan Bommas, Felix Schmidt
 */

#include<iostream>
#include <string>
#include "Trie.hpp"

void trieempty(Trie<int> &trie);
void trieinsert(Trie<int> &trie);
void trieerase(Trie<int> &trie);
void trieclear(Trie<int> &trie);
void trieprint(Trie<int> &trie);
void trielower(Trie<int> &trie);
void trieupper(Trie<int> &trie);
void triefind(Trie<int> &trie);
void triebegin(Trie<int> &trie);
void trieend(Trie<int> &trie);

int main(int argc, char* argv[]){
    Trie<int> trie1;
    int command;
    while(command != 0){
	std::cout << "-----------------<Modify Your Trie>----------------" << '\n'
			  << "*------<Commands>--------*"	<< std::endl
			  << "|0: exit the programm    |"	<< std::endl
			  << "|1: empty()              |"	<< std::endl
			  << "|2: insert()             |"	<< std::endl
			  << "|3: erase()              |"	<< std::endl
			  << "|4: clear()              |"	<< std::endl
              << "|5: print()              |"	<< std::endl
              << "|6: lower_bound()        |"	<< std::endl
              << "|7: upper_bound()        |"	<< std::endl
			  << "|8: find()               |"	<< std::endl
			  << "|9: begin()              |"	<< std::endl
			  << "|10: end()               |"	<< std::endl
			  << "*------------------------*"	<< std::endl
			  << "Enter number here: ";
	std::cin >> command;
        std::cout << std::endl;
        try{
		if(command == 1){
			trieempty(trie1);
		}
		else if(command == 2){
			trieinsert(trie1);
		}
		else if(command == 3){
			trieerase(trie1);
		}
		else if(command == 4){
			trieclear(trie1);
		}
		else if(command == 5){
			trieprint(trie1);
		}
		else if(command == 6){
			trielower(trie1);
		}
		else if(command == 7){
			trieupper(trie1);
		}
		else if(command == 8){
			triefind(trie1);
		}
		else if(command == 9){
			triebegin(trie1);
		}
		else if(command == 10){
			trieend(trie1);
		}
	}
	catch (const char* exception){
		std::cerr << "Error: " << exception << std::endl;
	}
	std::cout << std::endl;
    }
    return 0;
}

void trieempty(Trie<int> &trie){
    std::cout << (trie.empty()? "Trie is empty" : "Trie is not empty") << std::endl;
}

void trieinsert(Trie<int> &trie) {
    std::string input;
    int index;
    std::cout << "Enter key: ";
	std::cin >> input;
	std::cout << std::endl;
	std::cout << "Enter value: ";
	std::cin >> index;
    std::cout << std::endl;
    auto itr = trie.insert(std::make_pair(input, index));
    std::cout << itr.getKey() << "->" << *itr << std::endl;
    std::cout << "Element has been inserted" << std::endl;
}

void trieerase(Trie<int> &trie){
    std::string eraser;
    std::cout << "Enter key to delete" << std::endl;
    std::cin >> eraser;
    trie.erase(eraser);
    std::cout << "Element has been removed" << std::endl;
}

void trieclear(Trie<int> &trie){
    trie.clear();
    std::cout << "Trie cleared!" << std::endl;
}

void trieprint(Trie<int> &trie){
	trie.print();
    for (auto itr = trie.begin(); itr != trie.end(); itr++) {
    	std::cout << itr.getKey() << "->" << *itr << std::endl;
    }
}

void trielower(Trie<int> &trie){
    std::string lower;
    std::cout << "Enter key to get first position" << std::endl;
    std::cin >> lower;
    auto itrfind = trie.lower_bound(lower);
    std::cout << itrfind.getKey() << "->" <<*itrfind << std::endl;
}

void trieupper(Trie<int> &trie){
    std::string upper;
    std::cout << "Enter key to get last position" << std::endl;
    std::cin >> upper;
    auto itrfind = trie.upper_bound(upper);
    std::cout<< itrfind.getKey() << "->" << *itrfind << std::endl;
}

void triefind(Trie<int> &trie){
    std::string find;
    std::cout << "Enter element to receive position" << std::endl;
    std::cin >> find;
    auto itrfind = trie.find(find);
    std::cout << *itrfind << std::endl;
}

void triebegin(Trie<int> &trie){
    auto itr1 = trie.begin();
    std::cout << "Beginning iterator: " << itr1.getKey() << "->" <<*itr1 << std::endl;
}

void trieend(Trie<int> &trie){
    auto itr2 = trie.end();
    std::cout << "End iterator: " << itr2.getKey() << "->" << *itr2 << '\n';
}
