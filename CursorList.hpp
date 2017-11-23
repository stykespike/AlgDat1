/*
 * CursorList.hpp
 *
 *  Created on: 09.11.2017
 *      Author: schmi
 */

#ifndef CURSORLIST_HPP_
#define CURSORLIST_HPP_
template <class T> class CursorIterator;
template <class T>
class CursorList{
	struct Node{
		T listElement;
		int previous;
		int next;
	};
	friend class CursorIterator<T>;
	Node m_Array[10];
	int m_freeHead;
	int m_dataHead;
	int m_dataTail;
public:
	CursorList();
	typedef T value_type;
	typedef CursorIterator<T> iterator;
	bool empty() const;
	int size() const;
	T& front();
	void push_front(const T &element);
	void pop_front();
	iterator begin();
	iterator end();
	iterator insert(iterator itr, const T& value);
	iterator erase(iterator start, iterator stop);
	iterator erase(iterator itr);
};
//------------------------------------------------------------------
template<class T>
CursorList<T>::CursorList(){
	m_freeHead = 0;
	m_dataHead = -1;
	m_dataTail = -1;
	for(int index = 0; index < 10; index++){
		m_Array[index].previous = index-1;
		if(index != 9){
			m_Array[index].next = index+1;
		}
		else{
			m_Array[index].next = -1;
		}
	}
}
template<class T>
bool CursorList<T>::empty() const{
	return m_dataHead < 0;
}
template<class T>
int CursorList<T>::size() const{
	int size;
	if(empty()){
		size = 0;
	}
	else{
		size = 0;
		for(int next = m_dataHead;next != -1;size++){
			next = m_Array[next].next;
		}
	}
	return size;
}
template <class T>
T& CursorList<T>::front(){
	if(m_dataHead<0){
		throw "List is empty";
	}
	return m_Array[m_dataHead].listElement;
}
template<class T>
void CursorList<T>::push_front(const T &element){
	if(m_freeHead <0){
		throw "List is full";
	}
	else{
		m_Array[m_freeHead].listElement = element;
		int knotIndex = m_freeHead;
		if (m_dataHead < 0){//erstes element in der liste
			m_dataHead = m_freeHead;//setzen des neuen data list anfangs
			m_dataTail = m_freeHead;//setzen des neuen data list endpunkt
			m_freeHead = m_Array[knotIndex].next;
			m_Array[m_dataHead].previous = -1;
			m_Array[m_dataHead].next = -1;
			m_Array[m_freeHead].previous = -1;//neuen free head previous -1 setzen

		}
		else{
			m_Array[m_dataTail].next = knotIndex;//erweiterung der data list
			m_freeHead = m_Array[knotIndex].next;//setzen des neuen free heads
			m_Array[knotIndex].next = -1;//beenden der data list
			m_Array[knotIndex].previous = m_dataTail;//vollständige data list verlinkung
			m_dataTail = knotIndex;//neues ende der liste merken
			m_Array[m_freeHead].previous = -1;//neuen anfang von free list vervollständigen
		}
	}
}
template <class T>
void CursorList<T>::pop_front(){
	if(empty()){
		throw "List is empty";
	}
	else{
		if(m_dataTail==m_dataHead){//einzige element in der liste
			int index = m_dataTail;
			m_dataTail = m_Array[index].previous;
			m_Array[index].next = m_freeHead;//verlinkung zum frei speicher
			m_Array[m_freeHead].previous = index;//verlinkung zum freispeicher
			m_freeHead = index;
			m_dataHead = -1;
		}
		else{
			int index = m_dataTail;
			m_dataTail = m_Array[index].previous;//neuen data tail bestimmen
			m_Array[index].next = m_freeHead;
			m_Array[m_freeHead].previous = index;
			m_freeHead = index;
			m_Array[m_dataTail].next = -1;//setzt neuen schweif next -1
			m_Array[m_freeHead].previous = -1;
		}
	}
}

template<class T>
typename CursorList<T>::iterator CursorList<T>::begin(){
	int index;
	if(this->empty()){
		index = -1;
	}
	else{
		index = m_dataHead;
	}
	return iterator(*this, index);
}
template<class T>
typename CursorList<T>::iterator CursorList<T>::end(){
	return iterator(*this, -1);
}
template <class T>
typename CursorList<T>::iterator CursorList<T>::erase(iterator itr){
	if(!(itr.m_CursorList.empty())){
		int itrNext = itr.m_CursorList.m_Array[itr.m_index].next;
		int itrPrev = itr.m_CursorList.m_Array[itr.m_index].previous;
		int itrCurr = itr.m_index;
		auto dummy = ++itr;
		dummy.m_listIndex -=1;
		m_Array[itrCurr].previous = -1;//setzt zukünftigen freeHead previous -1
		m_Array[itrCurr].next =m_freeHead;//verknuepft zukünftigen freeHead mit vorherigem freeHead
		m_Array[m_freeHead].previous = itrCurr;//vollendung der verknüpfung von neuem und alten freeHead
		if(itrCurr == m_dataHead){//Prüfen ob erstes element
			if(m_dataHead != m_dataTail){//test ob es das nicht das einzige element ist
				m_Array[itrNext].previous = -1;//new dataHead previous korrigiert
				m_dataHead = itrNext;//setzt neuen listenanfang an in der liste volgende element
			}
			else{//falls es das einzige element ist müssen dataHead und dataTail angepasst werden
				m_dataHead = -1;
				m_dataTail = -1;
			}
		}
		else if(itrCurr == m_dataTail){
			m_Array[itrPrev].next = -1; //umbiegen des vorgaengigen next indeses
			m_dataTail = itrPrev;//
		}
		else{
			m_Array[itrPrev].next = itrNext;
			m_Array[itrNext].previous = itrPrev;
		}
		m_freeHead = itrCurr;
		return dummy;
	}
	else{
		return itr.m_CursorList.end();
	}
}
template <class T>
typename CursorList<T>::iterator CursorList<T>::insert(iterator itr ,const T &value){
	int itrCurr = itr.m_index;
	int itrPrev = itr.m_CursorList.m_Array[itrCurr].previous;
	int insertPoint = m_freeHead;
	if(m_freeHead <0){
		throw "List is full";
	}
	if(itr.m_CursorList.empty()){
		throw "List is Empty use a push_front instead";
	}
	else{
		m_freeHead = m_Array[insertPoint].next;
		m_Array[m_freeHead].previous = -1;
		if(itr.m_index == m_dataHead){//vors erste element
			m_Array[insertPoint].listElement = value;
			m_Array[insertPoint].previous = -1;
			m_Array[insertPoint].next = itrCurr;
			m_Array[itrCurr].previous = insertPoint;
			m_dataHead = insertPoint;
		}
		else if(itr.m_index==-1){//einfügen am ende
			m_Array[insertPoint].listElement = value;
			m_Array[insertPoint].previous = m_dataTail;
			m_Array[insertPoint].next = -1;
			m_Array[m_dataTail].next = insertPoint;
			m_dataTail = insertPoint;
		}
		else{//zwischen drinnen
			m_Array[insertPoint].listElement = value;
			m_Array[insertPoint].previous =itrPrev;
			m_Array[insertPoint].next =itrCurr;
			m_Array[itrCurr].previous = insertPoint;
			m_Array[itrPrev].next = insertPoint;
		}
		itr.m_listIndex+=1;
		return itr;
	}
}

template<class T>
typename CursorList<T>::iterator CursorList<T>::erase(iterator start, iterator stop){
	auto dummyItr = end();
	if(start == stop || start.m_listIndex > stop.m_listIndex){
		throw "Invalid erase range";
	}
	else{
		auto itr = start;
			while(itr != stop){
				itr = erase(itr);
			}
		dummyItr = itr;
	}
	return dummyItr;
}
//------------------------------------------------------------------

template <class T>
class CursorIterator{
		typedef CursorIterator<T> iterator;
		friend class CursorList<T>;
		CursorList<T> &m_CursorList;
		int m_index;
		int m_listIndex = 0;
		CursorIterator(CursorList<T> &list, int index);
public:
		int getlistIndex(){return m_listIndex;}
		T& operator *();
		iterator& operator = (const iterator& rhs);
		bool operator != (const iterator& rhs) const;
		bool operator == (const iterator& rhs) const;
		iterator& operator ++();
		iterator  operator ++(int);
	};
template<class T>
T& CursorIterator<T>::operator *(){
	if(m_index==-1){
		throw "Dereferencing memory you do not own";
	}
	return m_CursorList.m_Array[m_index].listElement;
}
template<class T>
bool CursorIterator<T>::operator ==(const iterator& rhs)const{
	return &this->m_CursorList == &rhs.m_CursorList && this->m_index == rhs.m_index;
}
template<class T>
bool CursorIterator<T>::operator !=(const iterator& rhs)const{
	return !(&this->m_CursorList == &rhs.m_CursorList && this->m_index == rhs.m_index);
}
template<class T>
CursorIterator<T>& CursorIterator<T>::operator =(const iterator& rhs){
	this->m_CursorList = rhs.m_CursorList;
	this->m_index = rhs.m_index;
	return *this;
}
template<class T>
CursorIterator<T>& CursorIterator<T>::operator ++(){
	if(m_index==m_CursorList.m_dataTail || m_index == -1){
		m_index = -1;
	}
	else{
		m_index = m_CursorList.m_Array[m_index].next;
		m_listIndex+=1;
	}
	return *this;
}
template<class T>
CursorIterator<T> CursorIterator<T>::operator ++(int){
	CursorIterator<T> dummy = *this;
	++(*this);
	return dummy;
}
template<class T>
CursorIterator<T>::CursorIterator(CursorList<T> &list,int index):m_CursorList(list), m_index(index)
{}
//------------------------------------------------------------------

template<typename Iterator, typename T>
Iterator find(Iterator start, Iterator stop, const T& value){
	if(start == stop || start.getlistIndex() > stop.getlistIndex()){
		throw "Invalid search range";
	}
	auto itr = start;
	while(itr != stop && *itr != value){
		++itr;
	}
	if(itr == stop ){//&& *itr != value){
		throw "404 Student was not found";
	}
	return itr;
}




#endif /* CURSORLIST_HPP_ */
