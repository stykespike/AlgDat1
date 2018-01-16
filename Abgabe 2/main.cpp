/*
 * main.cpp
 *
 *  Created on: 07.12.2017
 *      Author: schmi
 */

#include<iostream>
#include "Trie.hpp"

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