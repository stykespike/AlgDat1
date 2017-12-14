/*
 * Trie.hpp
 *
 *  Created on: 07.12.2017
 *      Author: schmi
 */

#ifndef TRIE_HPP_
#define TRIE_HPP_
#include<map>
template<class T, class E=char>
class Trie{
public:
	class Knot{
	public:
		void print()=0;
	};

	class Leaf : public Knot{
	public:
		Leaf();
		void print();
	};

	class Inner : public Knot{
		std::map<E,Knot*> m_sons;
	public:
		Inner();
		void print();

	};

 //typedef basic_string<E> key_type; 							// string=basic_string<char>
 //typedef pair<const key_type, T> value_type;
 typedef T mapped_type;
 //typedef ... iterator; 										// ...: keine C/C++ Ellipse, sondern von Ihnen
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	// zu entwickeln…
 //typedef std::reverse_iterator<iterator> reverse_iterator;
 bool empty() const;
 //void insert(const value_type& value);
 //void erase(const key_type& value);
 //void clear(); // erase all
 //iterator lower_bound(const key_type& testElement); 		// first element >= testElement
 //iterator upper_bound(const key_type& testElement); 		// first element > testElement
 //iterator find(const key_type& testElement); 				// first element == testElement
 //iterator begin(); 											// returns end() if not found
 //iterator end();
 //reverse_iterator rbegin(); //wenn Sie Lust und Zeit haben…
 //reverse_iterator rend(); //wenn Sie Lust und Zeit haben…
};
/*----------------------------------------------------------------------------*/
/*template<class T, class E=char>
void Trie<T,E>::Inner::print(){
	std::cout << "I'm here" << '\n';
}*/
/*----------------------------------------------------------------------------*/
/*template<class T, class E=char>
void Trie<T,E>::Leaf::print(){

}*/

#endif /* TRIE_HPP_ */
