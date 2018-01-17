/*
 * main.cpp
 *
 *  Created on: 07.12.2017
 *      Author: schmi
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
    int i;
    int g;
    int command;
    while(command != 0){
	std::cout << "-----------------<Modify Your Trie>----------------" << '\n'
			<< "*------<Commands>--------*" << '\n'
			<< "|0: exit the programm    |" << '\n'
			<< "|1: empty()              |"	<< '\n'
			<< "|2: insert()             |"	<< '\n'
			<< "|3: erase()              |"	<< '\n'
			<< "|4: clear()              |"	<< '\n'
                	<< "|5: print()              |"	<< '\n'
                	<< "|6: lower_bound()        |"	<< '\n'
                	<< "|7: upper_bound()        |"	<< '\n'
			<< "|8: find()               |"	<< '\n'
			<< "|9: begin()              |" << '\n'
			<< "|10: end()               |" << '\n'
			<< "*------------------------*"	<< '\n'
			<< "Enter number here: ";
	std::cin >> command;
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
		std::cerr << "Error: " << exception << '\n';
	}
	std::cout << '\n';
    }
    //trie1.insert(std::make_pair("hallo", 99));
    //trie1.insert(std::make_pair("hales", 13));
    //trie1.insert(std::make_pair("has", 0));
    //trie1.print();
    //trie1.erase("has");
    //std::cin >> i;
    //trie1.clear();
    //trie1.print();
    //std::cin >> g;
    return 0;
}

void trieempty(Trie<int> &trie){
    std::cout << (trie.empty()? "Trie is empty" : "Trie is not empty") << '\n';
}

void trieinsert(Trie<int> &trie){
    std::string input;
    int index;
    std::cout << "Enter input" << '\n';
	std::cin >> input;
	std::cout << "Enter position to insert at: ";
	std::cin >> index;
    trie.insert(std::make_pair(index, input));
}

void trieerase(Trie<int> &trie){
    
}

void trieclear(Trie<int> &trie){
    
}

void trieprint(Trie<int> &trie){
    
}

void trielower(Trie<int> &trie){
    
}

void trieupper(Trie<int> &trie){
    
}

void triefind(Trie<int> &trie){
    
}

void triebegin(Trie<int> &trie){
    
}

void trieend(Trie<int> &trie){
    
}