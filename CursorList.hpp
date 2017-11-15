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
public:
	CursorList();
	typedef T value_type;
	typedef CursorIterator<T> iterator;
	bool empty() const;
	int size() const;
	T& front() const;
	void push_front(const T &);
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
		for(int node = 0;node != -1;size++){
			node = m_Array[node].next;
		}
	}
	return size;
}
#endif /* CURSORLIST_HPP_ */
