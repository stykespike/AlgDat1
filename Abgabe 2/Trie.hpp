/*
 * Trie.hpp
 *
 *  Created on: 07.12.2017
 *      Author: Schmidt Felix IF3B
 */

#ifndef TRIE_HPP_
#define TRIE_HPP_
#include<map>
#include<stack>
#include<memory>
template<class T, class E=char>
class Trie{
private:
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
		Trie<T,E>& m_trie;
		Iterator(Trie<T,E>& trie);
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

 typedef std::basic_string<E> key_type;
 typedef std::pair<const key_type, T> value_type;
 typedef T mapped_type;
 typedef Trie<T, E>::Iterator iterator;

 bool empty() const;
 iterator insert(const value_type& value);
 void erase(const key_type& value);
 void print() const;
 void clear(); // erase all
 iterator lower_bound(const key_type& testElement);
 iterator upper_bound(const key_type& testElement);
 iterator find(const key_type& testElement);
 iterator begin();
 iterator end();
};
//--------------------------------------------------------------------------------
//lambdas for upper & lower bound
//--------------------------------------------------------------------------------
auto biggerOrEqual = [](const std::string& itrKey, const std::string& testElement)->bool {
	return itrKey >= testElement;
};

auto bigger = [](const std::string& itrKey, const std::string& testElement) -> bool {
	return itrKey > testElement;
};
//--------------------------------------------------------------------------------
/**Constructor for the Trie*/
template<class T,class E>
Trie<T,E>::Trie() : m_Root(std::make_shared<Inner>()) {
}

/** Prints the full trie*/
template<class T, class E>
void Trie<T,E>::print() const {
	m_Root->print();
	std::cout << std::endl;
}

/**Looks if the Trie (map of the root) is empty
 * @return true if the root map contains nothing false in case it contains something
 * */
template<class T,class E>
bool Trie<T,E>::empty() const{
	return (std::static_pointer_cast<Inner>(m_Root))->isEmpty();
}

/**Erases all nodes from the trie except the root */
template<class T, class E>
void Trie<T,E>::clear() {
	(std::static_pointer_cast<Inner>(m_Root))->clear();
}

/** Inserts new element into the trie
 *  no empty key and no '#' */
template<class T,class E>
typename Trie<T,E>::Iterator Trie<T,E>::insert(const value_type& value){
	std::string insertKey = value.first;

	//test for an empty key
	if (insertKey.length() == 0) {
		throw "Dont insert with an empty Key";
	}

	//test for # since it represents a leaf and is not allowed in the key
	for (unsigned int index = 0; index < insertKey.length(); ++index) {
		if (insertKey[index] == '#') {
			throw "Key contains invalid char #";
		}
	}
	auto currentPosition = m_Root;

	// steps the trie twig creates inner nodes if no previous node with the corresponding char existed
	for (unsigned int index = 0; index < insertKey.length();++index) {
		std::shared_ptr<Inner> dptr = std::static_pointer_cast<Inner>(currentPosition);

		//checks if the node doesnt exist if so it creates the node
		if (dptr->count(insertKey.at(index)) < 1) {
			dptr->m_Sons.insert(std::make_pair(insertKey.at(index), std::make_shared<Inner>()));
		}

		//steps into the next node
		currentPosition = dptr->m_Sons.at(insertKey.at(index));
	}
	std::shared_ptr<Inner> dptr = std::static_pointer_cast<Inner>(currentPosition);
	//if the leaf is already in the trie the current value is overwriten
	if (dptr->count('#')) {
		std::shared_ptr<Leaf> lptr =std::static_pointer_cast<Leaf>(dptr->m_Sons.at('#'));
		lptr->setValue(value.second);
	}

	//creates the leaf if it did not exist prior
	else {
		dptr->insert(std::make_pair('#', std::make_shared<Leaf>(value.second)));
	}

	//searches the inserted key
	std::string trueKey = "#" + insertKey;
	auto itr = begin();
	while (itr.getKey() != trueKey) {
		++itr;
	}
	return itr;
}

/** Deletes element from the trie*/
template<class T,class E>
void Trie<T,E>::erase(const key_type& value) {
	std::string deleteKey = value;
	unsigned int index = 0;
	std::stack<std::weak_ptr<Inner>> rStack;
	std::shared_ptr<Inner> dPtr = std::static_pointer_cast<Inner>(m_Root);
	//checks if the key is not empty
	if (deleteKey.length() > 0) {

		//check if the key contains #
		for (unsigned int index = 0; index < deleteKey.length(); ++index) {
			if (deleteKey[index] == '#') {
				throw "Invalide key was given";
			}
		}
		std::weak_ptr<Inner> wPtr = dPtr;
		rStack.push(wPtr);
	} else {

		//exception word is not in the trie since empty words are not allowed
		throw "input was empty";
	}

	//construction of a stack containing weak_ptr to the corresponding Innernodes
	while (dPtr->count(deleteKey[index])) {
		std::shared_ptr<Inner> sPtr = std::static_pointer_cast<Inner>(dPtr->m_Sons.at(deleteKey[index]));
		std::weak_ptr<Inner> wPtr = sPtr;
		rStack.push(wPtr);
		++index;
		dPtr = sPtr;

	}

	//case if the key does not exist in the trie
	if (rStack.top().lock()->count('#') < 1 || index < deleteKey.length()) {

		// exception word is not in trie
		throw "The Key you are trying to delete does not exist in this trie";
	}

	//since the leaf can be the only thing that needs to be removed # is added
	std::string delString = value + '#';
	int rIndex = delString.length()-1;

	//unwinding of the stack until a inner node with branches is reached
	while (rStack.top().lock()->size() < 2 && rIndex > 0) {
		rStack.pop();
		--rIndex;
	}
	rStack.top().lock()->erase(delString[rIndex]);
}

/** returns an iterator to the left lowest element*/
template<class T, class E>
typename Trie<T,E>::Iterator Trie<T,E>::begin() {
	Trie<T,E>::Iterator itr = Iterator(*this);

	//checks case if the trie is empty if so returned itr will represent end()
	if (!this->empty()) {

		//pushes the root to the iterator intern stack
		std::weak_ptr<Inner> wptr = std::static_pointer_cast<Inner>(m_Root);
		itr.push(wptr,'#');

		//will construct iterator intern stacks and key untill it hits a leaf
		while (itr.m_itrStack.top()->first != '#') {
			std::weak_ptr<Inner> wPtr = std::static_pointer_cast<Inner>(itr.m_itrStack.top()->second);
			itr.push(wPtr, itr.m_itrStack.top()->first);
		}

		//increments top map iterator to point to the next node or end()
		++itr.m_itrStack.top();
	}
	return itr;
}

/** creates an iterator to one element past the last element in the trie*/
template<class T, class E>
typename Trie<T,E>::Iterator Trie<T,E>::end() {
	//an end iterator in this case has an empty key and 2 empty stacks
	return Iterator(*this);
}

/** returns iterator to the first element with a key bigger or equal to the test element */
template<class T, class E>
typename Trie<T,E>::Iterator Trie<T,E>::lower_bound(const key_type& testElement) {

	//important since each iterator key starts with # representing the root
	std::string searchedKey = "#" + testElement;
	auto itr = begin();
	while(itr != end() && !biggerOrEqual(itr.getKey(), searchedKey)) {
		++itr;
	}
	return itr;
}

/** returns iterator to the first element with a key bigger then the test element*/
template<class T, class E>
typename Trie<T,E>::Iterator Trie<T,E>::upper_bound(const key_type& testElement) {

	//important since each iterator key starts with # representing the root
	std::string searchedKey = "#" +testElement;
	auto itr = begin();
	while (itr != end() && !bigger(itr.getKey(), searchedKey)) {
		++itr;
	}
	return itr;
}

/** returns iterator to the searched element or end()*/
template<class T, class E>
typename Trie<T,E>::Iterator Trie<T,E>::find(const key_type& testElement) {
	auto itrLow = lower_bound(testElement);
	auto itrUpper = upper_bound(testElement);
	auto itrFound = end();
	if (itrLow != itrUpper) {
		itrFound = itrLow;
	}
	return itrFound;
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

/** erases an entry of the map with the respective key */
template<class T, class E>
void Trie<T,E>::Inner::erase(const char delChar) {
	m_Sons.erase(delChar);
}
/** checks size of the map */
template<class T, class E>
int Trie<T,E>::Inner::size() const {
	return m_Sons.size();
}

/** checks if an iterator is an end iterator of a map*/
template<class T, class E>
bool Trie<T,E>::Inner::isEnd(typename std::map<E,std::shared_ptr<Trie<T, E>::IKnot>>::iterator& itr)const {
	return itr == m_Sons.end();
}

/**  Inserts new element into the map*/
template<class T, class E>
void Trie<T,E>::Inner::insert(std::pair<E,std::shared_ptr<IKnot>> value){
	m_Sons.insert(value);
}

/** returns the number of times key appears in the map*/
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
/** constructor for leaf*/
template<class T, class E>
Trie<T,E>::Leaf::Leaf(T value){
	m_Value = value;
}

/** prints leaf contents*/
template<class T, class E>
void Trie<T,E>::Leaf::print(){
	std::cout << m_Value;
}

/** setter for the leaf value*/
template<class T, class E>
void Trie<T,E>::Leaf::setValue(T value){
	m_Value = value;
}

/** getter for the leaf value*/
template<class T, class E>
T& Trie<T,E>::Leaf::getValue() {
	return m_Value;
}

/** destructor of leaf*/
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
Trie<T,E>::Iterator::Iterator(Trie<T,E>& trie) : m_trie(trie) {

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
	//checks if iterator is pointing to end()
	if (m_refStack.empty()) {
		throw "iterator may already at the end";
	}

	//checks if the element the iterator was pointing to has been deleted
	if (m_refStack.top().expired()) {
			throw "Iterator expired";
	}

	//checks if the element the iterator was pointing to has been deleted
	if (m_refStack.top().lock()->count('#') < 1) {
		throw "Iterator expired";
	}
	return std::static_pointer_cast<Leaf>(m_refStack.top().lock()->m_Sons.at('#'))->getValue();
}

/** copy assign operator for post increment operator*/
template<class T, class E>
typename Trie<T, E>::Iterator& Trie<T,E>::Iterator::operator = (const Trie<T, E>::Iterator& rhs) {
	this->m_refStack = rhs.m_refStack;
	this->m_itrStack = rhs.m_itrStack;
	this->m_key = rhs.m_key;
	return *this;
}

/** logical equals operator*/
template<class T, class E>
bool Trie<T,E>::Iterator::operator == (const Trie<T, E>::Iterator& rhs) const {
	return &this->m_trie == &rhs.m_trie && this->m_key == rhs.m_key;
}

/** logical not equals operator*/
template<class T, class E>
bool Trie<T,E>::Iterator::operator != (const Trie<T, E>::Iterator& rhs) const {
	return this->m_key != rhs.m_key;
}

/** preincrement operator*/
template<class T, class E>
typename Trie<T, E>::Iterator& Trie<T,E>::Iterator::operator ++() {
	//checks if the element the iterator was pointing to has been deleted
	if (!m_refStack.empty() && m_refStack.top().expired()) {
		throw "Iterator expired";//todo
	}
	//checks if the element the iterator was pointing to has been deleted
	if (!m_refStack.empty() && m_refStack.top().lock()->count('#') < 1) {
		throw "Iterator expired";
	}

	//unwinding the stack until an inner node with a branch is found
	while (!m_refStack.empty() && m_refStack.top().lock()->isEnd(m_itrStack.top())) {
		m_refStack.pop();
		m_itrStack.pop();
		m_key.pop_back();
		if (!m_refStack.empty()){
			++m_itrStack.top();
		}
	}

	//constructing stacks with the next branch until a leaf is found
	while (!m_refStack.empty() && m_itrStack.top()->first != '#') {
		std::weak_ptr<Inner> wPtr = std::static_pointer_cast<Inner>(m_itrStack.top()->second);
		push(wPtr,m_itrStack.top()->first);
	}
	if (!m_refStack.empty()) {
		++m_itrStack.top();
	}
	return *this;
}
/** postincrement operator*/
template<class T, class E>
typename Trie<T, E>::Iterator Trie<T,E>::Iterator::operator ++(int) {
	Trie<T,E>::Iterator dummy = *this;
	++(*this);
	return dummy;
}
#endif /* TRIE_HPP_ */
