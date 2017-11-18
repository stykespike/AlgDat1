/*
 * CursorList.hpp
 *
 *  Created on: 09.11.2017
 *      Author: schmi
 */

#ifndef CURSORLIST_HPP_
#define CURSORLIST_HPP_
template <class T>
class CursorList{
	template<class TT>
	struct Node{
		TT listElement;
		int previous;
		int next;
	};
	template <class TTT>
	class CursorIterator{

	};
	Node<T> m_Array[10];
	int m_freeHead;
	int m_dataHead;
	int m_dataTail;
public:
	CursorList();
	typedef T value_type;
	typedef CursorIterator<T> iterator;
	bool empty() const;
	int size() const;
	T& front() const;
	void push_front(const T element);
	void pop_front();
	iterator begin() const;
	iterator end() const;
	iterator insert(iterator itr, const T& value);
	iterator erase(iterator start, iterator stop);
	iterator erase(iterator itr);
};
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
//template <class T>
//T& CursorList<T>::front() const;

template<class T>
void CursorList<T>::push_front(const T element){
	if(m_freeHead <0){
		std::cout << "List is full" << '\n';
	}
	else{
		m_Array[m_freeHead].listElement = element;
		int knotIndex = m_freeHead;
		if (m_dataHead < 0){
			m_dataHead = 0;
			m_dataTail = 0;
			m_freeHead = m_Array[knotIndex].next;
			m_Array[m_dataHead].previous = -1;
			m_Array[m_dataHead].next = -1;
			m_Array[m_freeHead].previous = -1;

		}
		else{
			m_Array[m_dataTail].next = knotIndex;
			m_freeHead = m_Array[knotIndex].next;
			m_Array[knotIndex].next = -1;
			m_Array[knotIndex].previous = m_dataTail;
			m_dataTail = knotIndex;
			m_Array[m_freeHead].previous = -1;
		}
	}
}
template <class T>
void CursorList<T>::pop_front(){
	if(empty()){
		std::cout << "List is empty" << '\n';
	}
	else{
		if(m_dataTail==0){
			int index = m_dataTail;
			m_dataTail = m_Array[index].previous;
			m_Array[index].next = m_freeHead;
			m_Array[m_freeHead].previous = index;
			m_freeHead = index;
			m_Array[m_dataTail].next = -1;
			m_dataHead = -1;
		}
		else{
			int index = m_dataTail;
			m_dataTail = m_Array[index].previous;
			m_Array[index].next = m_freeHead;
			m_Array[m_freeHead].previous = index;
			m_freeHead = index;
			m_Array[m_dataTail].next = -1;//setzt neuen schweif next -1
			m_Array[m_freeHead].previous = -1;
		}
	}
}






#endif /* CURSORLIST_HPP_ */
