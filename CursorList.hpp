/*
 * CursorList.hpp
 *
 *  Created on: 09.11.2017
 *      Author: Schmidt Felix, Stefan Bommas
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
//-------------------------------------------------------------------------------
//Pr�ft ob liste leer ist
//-------------------------------------------------------------------------------
template<class T>
bool CursorList<T>::empty() const{
	return m_dataHead < 0;
}
//-------------------------------------------------------------------------------
//Gibt die Listengr��e aus
//-------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------
//Gibt oberstes Listenelement zur�ck
//-------------------------------------------------------------------------------
template <class T>
T& CursorList<T>::front(){
	if(m_dataHead<0){
		throw "List is empty";
	}
	return m_Array[m_dataTail].listElement;
}
//-------------------------------------------------------------------------------
//F�gt neues Element oben an die Liste an
//-------------------------------------------------------------------------------
template<class T>
void CursorList<T>::push_front(const T &element){
	if(m_freeHead <0){								//sonderfall f�r eine leere liste
		throw "List is full";
	}
	else{
		m_Array[m_freeHead].listElement = element;	//f�gt element dem listen knoten hinzu
		int knotIndex = m_freeHead;					//Zwischenspeichern f�r sp�ter
		if (m_dataHead < 0){						//erstes element in der liste
			m_dataHead = m_freeHead;				//setzen des neuen data list anfangs
			m_dataTail = m_freeHead;				//setzen des neuen data list endpunkt
			m_freeHead = m_Array[knotIndex].next;	//free head wird um eins weiterger�ckt
			m_Array[m_dataHead].previous = -1;		//erstes element
			m_Array[m_dataHead].next = -1;			//letztes element
			m_Array[m_freeHead].previous = -1;		//neuen free head previous -1 setzen

		}
		else{
			m_Array[m_dataTail].next = knotIndex;	//erweiterung der data list
			m_freeHead = m_Array[knotIndex].next;	//setzen des neuen free heads
			m_Array[knotIndex].next = -1;			//beenden der data list
			m_Array[knotIndex].previous = m_dataTail;//vollst�ndige data list verlinkung
			m_dataTail = knotIndex;					//neues ende der liste merken
			m_Array[m_freeHead].previous = -1;		//neuen anfang von free list vervollst�ndigen
		}
	}
}
//-------------------------------------------------------------------------------
//Entfernt oberstes Element von der Liste
//-------------------------------------------------------------------------------
template <class T>
void CursorList<T>::pop_front(){
	if(empty()){									//sonderfall das liste leer ist
		throw "List is empty";
	}
	else{
		if(m_dataTail==m_dataHead){					//einzige element in der liste
			int index = m_dataTail;					//Zwischenspeichern f�r sp�ter
			m_dataTail = m_Array[index].previous;	//setzen des data list endes (-1)
			m_Array[index].next = m_freeHead;		//verlinkung zum frei speicher
			m_Array[m_freeHead].previous = index;	//verlinkung zum freispeicher
			m_freeHead = index;						//neue free head wird gesetzt
			m_dataHead = -1;						//data head wird angepasst
		}
		else{
			int index = m_dataTail;					//Zwischenspeichern f�r sp�ter
			m_dataTail = m_Array[index].previous;	//neuen data tail bestimmen
			m_Array[index].next = m_freeHead;		//an free list anh�ngen
			m_Array[m_freeHead].previous = index;	//an free list anh�ngen
			m_freeHead = index;						//neuer free head wird gesetzt
			m_Array[m_dataTail].next = -1;			//setzt neuen schweif next -1
			m_Array[m_freeHead].previous = -1;		//kopplung an free list beendet
		}
	}
}
//-------------------------------------------------------------------------------
//R�ckgabe eines Iterators der auf das erste Element in der Liste zeigt
//-------------------------------------------------------------------------------
template<class T>
typename CursorList<T>::iterator CursorList<T>::begin(){
	int index;
	if(this->empty()){				//sonderfall f�r leere liste
		index = -1;					//iterator den man erh�lt ist gleich dem iterator
	}								//der auf das ende der liste zeigt
	else{
		index = m_dataHead;
	}
	return iterator(*this, index);
}
//-------------------------------------------------------------------------------
//R�ckgabe eines Iterators der auf das Ende der Liste zeigt
//-------------------------------------------------------------------------------
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
		itr.m_CursorList.m_Array[itrCurr].previous = -1;				//setzt zuk�nftigen freeHead previous -1
		itr.m_CursorList.m_Array[itrCurr].next =m_freeHead;			//verknuepft zuk�nftigen freeHead mit vorherigem freeHead
		itr.m_CursorList.m_Array[m_freeHead].previous = itrCurr;		//vollendung der verkn�pfung von neuem und alten freeHead
		if(itrCurr == itr.m_CursorList.m_dataHead){					//Pr�fen ob erstes element
			if(itr.m_CursorList.m_dataHead != itr.m_CursorList.m_dataTail){			//test ob es das nicht das einzige element ist
				itr.m_CursorList.m_Array[itrNext].previous = -1;		//new dataHead previous korrigiert
				itr.m_CursorList.m_dataHead = itrNext;				//setzt neuen listenanfang an in der liste volgende element
			}
			else{									//falls es das einzige element ist m�ssen dataHead und dataTail angepasst werden
				itr.m_CursorList.m_dataHead = -1;
				itr.m_CursorList.m_dataTail = -1;
			}
		}
		else if(itrCurr == itr.m_CursorList.m_dataTail){				//fals es das letzte element ist
			itr.m_CursorList.m_Array[itrPrev].next = -1; 			//umbiegen des vorgaengigen next indeses
			itr.m_CursorList.m_dataTail = itrPrev;					//setzen des neuen data tails
		}
		else{										//l�schen aus der mitte
			itr.m_CursorList.m_Array[itrPrev].next = itrNext;
			itr.m_CursorList.m_Array[itrNext].previous = itrPrev;
		}
		itr.m_CursorList.m_freeHead = itrCurr;						//stezen de neuen free heads
		return dummy;
	}
	else{											//Liste ist leer
		return itr.m_CursorList.end();
	}
}
//-------------------------------------------------------------------------------
//Einf�gen eines Elements in die Liste an der eingegebenen Position
//-------------------------------------------------------------------------------
template <class T>
typename CursorList<T>::iterator CursorList<T>::insert(iterator itr ,const T &value){
	int itrCurr = itr.m_index;
	int itrPrev = itr.m_CursorList.m_Array[itrCurr].previous;
	int insertPoint = m_freeHead;
	if(itr.m_CursorList.m_freeHead <0){									//sonderfall wenn die liste voll ist
		throw "List is full";
	}
	if(itr.m_CursorList.empty()){						//sonderfall wenn die liste kein element hat
		throw "List is Empty use a push_front instead";
	}
	else{
		itr.m_CursorList.m_freeHead = m_Array[insertPoint].next;			//weiterr�cken des free heads um eins
		itr.m_CursorList.m_Array[m_freeHead].previous = -1;				//vollendung des weiterr�ckens
		if(itr.m_index == m_dataHead){					//vors erste element
			itr.m_CursorList.m_Array[insertPoint].listElement = value;	//einf�gen des elements
			itr.m_CursorList.m_Array[insertPoint].previous = -1;			//setzen des neuen ersten elements
			itr.m_CursorList.m_Array[insertPoint].next = itrCurr;		//verkn�pfung an das n�chste element
			itr.m_CursorList.m_Array[itrCurr].previous = insertPoint;	//verkn�pfung an das eingef�gte element
			itr.m_CursorList.m_dataHead = insertPoint;					//setzen des neuen data heads
		}
		else if(itr.m_index==-1){						//einf�gen am ende
			itr.m_CursorList.m_Array[insertPoint].listElement = value;	//einf�gen des elements
			itr.m_CursorList.m_Array[insertPoint].previous = m_dataTail;	//verbinden an die data list
			itr.m_CursorList.m_Array[insertPoint].next = -1;				//setzen des neuen data list ende
			itr.m_CursorList.m_Array[m_dataTail].next = insertPoint;		//verkn�pft auf das neue letzte element
			itr.m_CursorList.m_dataTail = insertPoint;					//setzen des neuen data tails
		}
		else{											//zwischen drinnen
			itr.m_CursorList.m_Array[insertPoint].listElement = value;	//einf�gen des elements
			itr.m_CursorList.m_Array[insertPoint].previous = itrPrev;	//verkn�pfen mit voherigem listen element
			itr.m_CursorList.m_Array[insertPoint].next =itrCurr;			//verkn�pfen mit n�chstem listen element
			itr.m_CursorList.m_Array[itrCurr].previous = insertPoint;	//verbindet das volgende element mit dem eingef�gten
			itr.m_CursorList.m_Array[itrPrev].next = insertPoint;		//verbinde das vorherige element mit dem eingef�gten
		}
		itr.m_listIndex+=1;
		return itr;
	}
}
//-------------------------------------------------------------------------------
//L�scht Elemente von bis (bis ausgeschlossen)
//-------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------

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
//-------------------------------------------------------------------------------
//�berladen des Dereferenzierungsoperators
//-------------------------------------------------------------------------------
template<class T>
T& CursorIterator<T>::operator *(){
	if(m_index==-1){
		throw "Dereferencing memory you do not own";
	}
	return m_CursorList.m_Array[m_index].listElement;
}
//-------------------------------------------------------------------------------
//�berladen der logischen Operatoren
//-------------------------------------------------------------------------------
template<class T>
bool CursorIterator<T>::operator ==(const iterator& rhs)const{
	return &this->m_CursorList == &rhs.m_CursorList && this->m_index == rhs.m_index;
}
template<class T>
bool CursorIterator<T>::operator !=(const iterator& rhs)const{
	return !(&this->m_CursorList == &rhs.m_CursorList && this->m_index == rhs.m_index);
}
//-------------------------------------------------------------------------------
//�berladung des Zuweisungsoperators
//-------------------------------------------------------------------------------
template<class T>
CursorIterator<T>& CursorIterator<T>::operator =(const iterator& rhs){
	this->m_CursorList = rhs.m_CursorList;
	this->m_index = rhs.m_index;
	return *this;
}
//-------------------------------------------------------------------------------
//�berladen der Increment operatoren
//-------------------------------------------------------------------------------
template<class T>
CursorIterator<T>& CursorIterator<T>::operator ++(){
	if(m_index==m_CursorList.m_dataTail || m_index == -1){ 	//fall falls iterator auf das letzte element zeigt
		m_index = -1;										//oder dieser bereits auf das ende zeigt
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
//-------------------------------------------------------------------------------
//Construcktor f�r CursorIterator
//-------------------------------------------------------------------------------
template<class T>
CursorIterator<T>::CursorIterator(CursorList<T> &list,int index):m_CursorList(list), m_index(index)
{}
//-------------------------------------------------------------------------------
//Sucht eingegebenen value in der Liste in einem spezifizierten Bereich
//-------------------------------------------------------------------------------
template<typename Iterator, typename T>
Iterator find(Iterator start, Iterator stop, const T& value){
	if(start == stop || start.getlistIndex() > stop.getlistIndex()){
		throw "Invalid search range";
	}
	auto itr = start;
	while(itr != stop && *itr != value){
		++itr;
	}
	if(itr == stop ){
		throw "404 Student was not found";
	}
	return itr;
}




#endif /* CURSORLIST_HPP_ */
