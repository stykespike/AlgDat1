/*
 * Trie.hpp
 *
 *  Created on: 07.12.2017
 *      Author: schmi
 */

#ifndef TRIE_HPP_
#define TRIE_HPP_
#include<map>
#include<stack>
#include<memory>
template<class T, class E=char>
class Trie{
	friend class Inner;
public:
	class IKnot{
	public:
		virtual void print()=0;
		virtual ~IKnot(){}
	};

	class Leaf : public IKnot{
		T m_Value;
	public:
		Leaf(T value);
		virtual void print();
		void setValue(T value);
		virtual ~Leaf();
	};

	class Inner : public IKnot{
		friend class Trie;
		std::map<E,std::shared_ptr<IKnot>> m_Sons;
	public:
		Inner();
		virtual void print();
		void insert(std::pair<E,std::shared_ptr<IKnot>> value);
		int count(E key) const;
		bool isEmpty() const;
		void clear();
		int size() const;
		void erase(const char& delChar);
		virtual ~Inner();
	};
	private:
	std::shared_ptr<IKnot> m_Root = nullptr;
	public:
	Trie();

 typedef std::basic_string<E> key_type; 							// string=basic_string<char>
 typedef std::pair<const key_type, T> value_type;
 typedef T mapped_type;
 //typedef ... iterator; 										// ...: keine C/C++ Ellipse, sondern von Ihnen
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	// zu entwickeln�
 //typedef std::reverse_iterator<iterator> reverse_iterator;
 bool empty() const;
 void insert(const value_type& value);
 void erase(const key_type& value);
 void print() const;
 void clear(); // erase all
 //iterator lower_bound(const key_type& testElement); 		// first element >= testElement
 //iterator upper_bound(const key_type& testElement); 		// first element > testElement
 //iterator find(const key_type& testElement); 				// first element == testElement
 //iterator begin(); 											// returns end() if not found
 //iterator end();
 //reverse_iterator rbegin(); //wenn Sie Lust und Zeit haben�
 //reverse_iterator rend(); //wenn Sie Lust und Zeit haben�
};


/**Constructor for the Trie*/
template<class T,class E>
Trie<T,E>::Trie() : m_Root(std::make_shared<Inner>()) {
}

/** */
template<class T, class E>
void Trie<T,E>::print() const {
	m_Root->print();
}

/**Looks if the Trie (map of the root) is empty
 * @return true if the root map contains nothing false in case it contains something
 * */
template<class T,class E>
bool Trie<T,E>::empty() const{
	return (std::static_pointer_cast<Inner>(m_Root))->isEmpty();//f�ge eine empty funktion in inner ein
}

/**Erases all nodes from the trie except the root */
template<class T, class E>
void Trie<T,E>::clear() {
	(std::static_pointer_cast<Inner>(m_Root))->clear();
}

/** Inserts new element into the trie  */
template<class T,class E>
void Trie<T,E>::insert(const value_type& value){
	std::string insertKey = value.first;
	auto currentPosition = m_Root;
	for (int index = 0; index < insertKey.length();++index) {
		std::shared_ptr<Inner> dptr = std::static_pointer_cast<Inner>(currentPosition);
		if (dptr->count(insertKey.at(index))) {
			currentPosition = dptr->m_Sons.at(insertKey.at(index));
		} else {
			dptr->m_Sons.insert(std::make_pair(insertKey.at(index), std::make_shared<Inner>()));
			currentPosition = dptr->m_Sons.at(insertKey.at(index));
		}
	}
	std::shared_ptr<Inner> dptr = std::static_pointer_cast<Inner>(currentPosition);
	if (dptr->count('~')) {
		dptr->m_Sons.at('~');
	} else {
		dptr->insert(std::make_pair('~', std::make_shared<Leaf>(value.second)));
	}
}

/** Deletes element from the trie*/
template<class T,class E>
void Trie<T,E>::erase(const key_type& value) {
	std::string deleteKey = value;
	int index = 0;
	int rIndex = deleteKey.length()-1;
	std::stack<std::weak_ptr<IKnot>> rStack;
	std::shared_ptr<Inner> dPtr = std::static_pointer_cast<Inner>(m_Root);
	if (deleteKey.length() > 0) {
		std::weak_ptr<IKnot> wPtr = m_Root;
		rStack.push(wPtr);
	} else {
		//exception word is not in the trie
	}
	while (dPtr->count(deleteKey[index])) {
		std::weak_ptr<IKnot> wPtr = dPtr->m_Sons.at(deleteKey[index]);
		rStack.push(wPtr);
		++index;
		dPtr = dPtr->m_Sons.at(deleteKey[index]);
	}
	if (index < deleteKey.length()) {
		// exception word is not in trie
	}
	std::shared_ptr<Inner> dWPtr = std::static_pointer_cast<Inner>(rStack.top().lock());
	while (dWPtr->size() > 1 && rIndex >0) {
		dWPtr->erase(deleteKey[rIndex]);
		--rIndex;
		rStack.pop();
		dWPtr = rStack.top().lock();
	}
}
//-------------------------------------------------------------------------------------------
//Inner class Stuff
//-------------------------------------------------------------------------------------------
/** Constructor for inner */
template<class T, class E>
Trie<T,E>::Inner::Inner(){
	std::cout << "Inner constructed" << '\n';
}

/** Prints content of Inner */
template<class T, class E>
void Trie<T,E>::Inner::print(){
		for (auto itr = m_Sons.begin(); itr != m_Sons.end();++itr) {
			if (m_Sons.size() > 1) {
				std::cout << '[';
			}
			std::cout << '{' << itr->first << '}';
			std::cout << "->";
			itr->second->print();
			if (m_Sons.size() > 1) {
				std::cout << ']';
			}
		}
	}

/**checks if map is empty */
template<class T, class E>
bool Trie<T,E>::Inner::isEmpty() const {
	return m_Sons.empty();
}

/** clears the map contents of an inner */
template<class T, class E>
void Trie<T,E>::Inner::clear() {
	m_Sons.clear();
}

/** erases an entry of the map with teh respective key */
template<class T, class E>
void Trie<T,E>::Inner::erase(const char& delChar) {
	m_Sons.erase(delChar);
}
/** checks size of the map */
template<class T, class E>
int Trie<T,E>::Inner::size() const {
	return m_Sons.size();
}

/**  Inserts new element into the map*/
template<class T, class E>
void Trie<T,E>::Inner::insert(std::pair<E,std::shared_ptr<IKnot>> value){
	m_Sons.insert(value);
}

template<class T, class E>
int Trie<T,E>::Inner::count(E key) const {
	return m_Sons.count(key);
}

/** Destructor of Inner*/
template<class T, class E>
Trie<T,E>::Inner::~Inner(){
	std::cout <<"Inner destroyed \n";
}
//-------------------------------------------------------------------------------------------
//Leaf class Stuff
//-------------------------------------------------------------------------------------------
template<class T, class E>
Trie<T,E>::Leaf::Leaf(T value){
	m_Value = value;
}

template<class T, class E>
void Trie<T,E>::Leaf::print(){
	std::cout << /*"I'm a Leaf and hold: " <<*/ m_Value /*<< '\n'*/;
}

template<class T, class E>
void Trie<T,E>::Leaf::setValue(T value){
	m_Value = value;
}

template<class T, class E>
Trie<T,E>::Leaf::~Leaf(){
	std::cout << "Leaf destroyed \n";
}
//-------------------------------------------------------------------------------------------
//Iterator class Stuff
//-------------------------------------------------------------------------------------------

#endif /* TRIE_HPP_ */