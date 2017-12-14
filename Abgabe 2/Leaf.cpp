/*
 * Leaf.cpp
 *
 *  Created on: 07.12.2017
 *      Author: schmi
 */
#include<iostream>
#include "Trie.hpp"

template<class T, class E=char>
void Trie<T,E>::Leaf::print(){
	std::cout << "I'm here" << '\n';
}
