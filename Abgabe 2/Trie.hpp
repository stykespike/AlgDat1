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
	friend class Iterator;
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
		T& getValue();
		virtual ~Leaf();
	};

	class Inner : public IKnot{
		friend class Trie;
		std::map<E,std::shared_ptr<IKnot>> m_Sons;
	public:
		Inner();
		virtual void print();
		bool isEnd(typename std::map<E,std::shared_ptr<Trie<T, E>::IKnot>>::iterator& itr) const;
		void insert(std::pair<E,std::shared_ptr<IKnot>> value);
		int count(E key) const;
		bool isEmpty() const;
		void clear();
		int size() const;
		void erase(const char delChar);
		virtual ~Inner();
	};
	class Iterator{
		friend class Trie;
		std::stack<std::weak_ptr<Inner>> m_refStack;
		std::stack<typename std::map<E,std::shared_ptr<Trie<T, E>::IKnot> >::iterator> m_itrStack;
		std::string m_key;
		Iterator();
		void push(typename std::weak_ptr<Inner>& wptr,const char& key);
	public:
		std::string getKey();
		T& operator *();
		Trie<T, E>::Iterator& operator = (const Trie<T, E>::Iterator& rhs);
		bool operator == (const Trie<T, E>::Iterator& rhs) const;
		bool operator != (const Trie<T, E>::Iterator& rhs) const;
		Trie<T, E>::Iterator& operator ++();
		Trie<T, E>::Iterator operator ++(int);
	};
	private:
	std::shared_ptr<IKnot> m_Root = nullptr;
	public:
	Trie();

 typedef std::basic_string<E> key_type; 							// string=basic_string<char>
 typedef std::pair<const key_type, T> value_type;
 typedef T mapped_type;
 typedef Trie<T, E>::Iterator iterator; 										// ...: keine C/C++ Ellipse, sondern von Ihnen
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	// zu entwickeln…
 //typedef std::reverse_iterator<iterator> reverse_iterator;
 bool empty() const;
 void insert(const value_type& value);
 void erase(const key_type& value);
 void print() const;
 void clear(); // erase all
 //iterator lower_bound(const key_type& testElement); 		// first element >= testElement
 //iterator upper_bound(const key_type& testElement); 		// first element > testElement
 //iterator find(const key_type& testElement); 				// first element == testElement
 iterator begin(); 											// returns end() if not found
 iterator end();
 //reverse_iterator rbegin(); //wenn Sie Lust und Zeit haben…
 //reverse_iterator rend(); //wenn Sie Lust und Zeit haben…
};


/**Constructor for the Trie*/
template<class T,class E>
Trie<T,E>::Trie() : m_Root(std::make_shared<Inner>()) {
}

/** Prints the howl trie*/
template<class T, class E>
void Trie<T,E>::print() const {
	m_Root->print();
	std::cout << '\n';
}

/**Looks if the Trie (map of the root) is empty
 * @return true if the root map contains nothing false in case it contains something
 * */
template<class T,class E>
bool Trie<T,E>::empty() const{
	return (std::static_pointer_cast<Inner>(m_Root))->isEmpty();//füge eine empty funktion in inner ein
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
	std::stack<std::weak_ptr<Inner>> rStack;
	std::shared_ptr<Inner> dPtr = std::static_pointer_cast<Inner>(m_Root);
	if (deleteKey.length() > 0) {
		std::weak_ptr<Inner> wPtr = dPtr;
		rStack.push(wPtr);
	} else {
		//exception word is not in the trie
		//todo
	}
	while (dPtr->count(deleteKey[index])) {
		std::shared_ptr<Inner> sPtr = std::static_pointer_cast<Inner>(dPtr->m_Sons.at(deleteKey[index]));
		std::weak_ptr<Inner> wPtr = sPtr;
		rStack.push(wPtr);
		++index;
		dPtr = sPtr;
	}
	if (index < deleteKey.length()) {
		// exception word is not in trie
		//todo
	}
	std::string delString = value + '~';
	std::cout << delString << '\n';
	int rIndex = delString.length()-1;
	//std::shared_ptr<Inner> dWPtr = std::static_pointer_cast<Inner>(rStack.top().lock());
	while (rStack.top().lock()->size() < 2 && rIndex > 0) {
		rStack.pop();
		--rIndex;
	}
	rStack.top().lock()->erase(delString[rIndex]);
}

/** returns an iterator to the left lowest element*/
template<class T, class E>
typename Trie<T,E>::Iterator Trie<T,E>::begin() {
	Trie<T,E>::Iterator itr;
	if (this->empty()) {
		itr = end();
	} else {
		itr = Iterator();
		std::weak_ptr<Inner> wptr = std::static_pointer_cast<Inner>(m_Root);
		itr.push(wptr,'#');
		while (itr.m_itrStack.top()->first != '~') {
			std::weak_ptr<Inner> wPtr = std::static_pointer_cast<Inner>(itr.m_itrStack.top()->second);
			itr.push(wPtr, itr.m_itrStack.top()->first);
		}
	}
	++itr.m_itrStack.top();
	return itr;
}

/** creates an iterator to one element past the last element in the trie*/
template<class T, class E>
typename Trie<T,E>::Iterator Trie<T,E>::end() {
	return Iterator();
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
void Trie<T,E>::Inner::erase(const char delChar) {
	m_Sons.erase(delChar);
}
/** checks size of the map */
template<class T, class E>
int Trie<T,E>::Inner::size() const {
	return m_Sons.size();
}

/** checks if an iterator is an end iterator*/
template<class T, class E>
bool Trie<T,E>::Inner::isEnd(typename std::map<E,std::shared_ptr<Trie<T, E>::IKnot>>::iterator& itr)const {
	return itr == m_Sons.end();
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
T& Trie<T,E>::Leaf::getValue() {
	return m_Value;
}

template<class T, class E>
Trie<T,E>::Leaf::~Leaf(){
	std::cout << "Leaf destroyed \n";
}
//-------------------------------------------------------------------------------------------
//Iterator class Stuff
//-------------------------------------------------------------------------------------------
/** returns the key the iterator is currently pointing*/
template<class T, class E>
std::string Trie<T,E>::Iterator::getKey() {
	return m_key;
}

/** constructor for iterator*/
template<class T, class E>
Trie<T,E>::Iterator::Iterator() {

}
/** push a new weak_ptr and itr to the stacks*/
template<class T, class E>
void Trie<T,E>::Iterator::push(typename std::weak_ptr<Inner>& wptr, const char& key) {
	m_refStack.push(wptr);
	m_itrStack.push(m_refStack.top().lock()->m_Sons.begin());
	m_key += key;
}

/** Dereferencing operator will return the value of the leaf*/
template<class T, class E>
T& Trie<T,E>::Iterator::operator *(){
	if (m_refStack.empty()) {
		std::cout << "dont do it" << '\n';
	}else{
	return std::static_pointer_cast<Leaf>(m_refStack.top().lock()->m_Sons.at('~'))->getValue();
	}
}

/** copy assign operator for post increment operator*/
template<class T, class E>
typename Trie<T, E>::Iterator& Trie<T,E>::Iterator::operator = (const Trie<T, E>::Iterator& rhs) {
	//todo
}

/** logical equals operator*/
template<class T, class E>
bool Trie<T,E>::Iterator::operator == (const Trie<T, E>::Iterator& rhs) const {
	return this->m_key == rhs.m_key;
}

/** logical not equals operator*/
template<class T, class E>
bool Trie<T,E>::Iterator::operator != (const Trie<T, E>::Iterator& rhs) const {
	return this->m_key != rhs.m_key;
}

/** preincrement operator*/
template<class T, class E>
typename Trie<T, E>::Iterator& Trie<T,E>::Iterator::operator ++() {
	while (!m_refStack.empty() && m_refStack.top().lock()->isEnd(m_itrStack.top())) {
		m_refStack.pop();
		m_itrStack.pop();
		m_key.pop_back();
		if (!m_refStack.empty()){
			++m_itrStack.top();
		}
	}
	while (!m_refStack.empty() && m_itrStack.top()->first != '~') {
		std::weak_ptr<Inner> wPtr = std::static_pointer_cast<Inner>(m_itrStack.top()->second);
		push(wPtr,m_itrStack.top()->first);
	}
	if (!m_refStack.empty()) {
		++m_itrStack.top();
	}
}
/** postincrement operator*/
template<class T, class E>
typename Trie<T, E>::Iterator Trie<T,E>::Iterator::operator ++(int) {
	//todo
}
#endif /* TRIE_HPP_ */
