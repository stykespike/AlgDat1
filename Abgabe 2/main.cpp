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
	try{
		int g;
		trie1.insert(std::make_pair("hales", 13));
		trie1.insert(std::make_pair("hallo", 0));
		trie1.insert(std::make_pair("has", 21));
		trie1.insert(std::make_pair("ha", 99));
		trie1.print();
		for (auto itr1 = trie1.begin();itr1 != trie1.end(); ++itr1) {
					std::cout << *itr1 << '\n';
					std::cout << itr1.getKey() << '\n';
		}
		if (trie1.end() == trie1.end()) {
			std::cout << "iterator equal" << std::endl;
		}

		trie1.erase("ha#");
		trie1.insert(std::make_pair("ha", 22));
		trie1.print();
		std::cin >> g;
	}catch (const char* exception) {
		std::cerr << "Error: " << exception << '\n';
	}
	for (auto itr1 = trie1.begin();itr1 != trie1.end(); ++itr1) {
				std::cout << *itr1 << '\n';
				std::cout << itr1.getKey() << '\n';
			}
	return 0;
}
