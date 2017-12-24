/*
 * main.cpp
 *
 *  Created on: 07.12.2017
 *      Author: schmi
 */

#include<iostream>
#include "Trie.hpp"

int main(int argc, char* argv[]){
	int i;
	int g;
	Trie<int> trie1;
	trie1.insert(std::make_pair("hallo", 99));
	trie1.insert(std::make_pair("hales", 13));
	trie1.insert(std::make_pair("has", 0));
	trie1.print();
	trie1.erase("has");
	//std::cin >> i;
	//trie1.clear();
	trie1.print();
	std::cin >> g;
	return 0;
}
