/*
 * main.cpp
 *
 *  Created on: 03.11.2017
 *      Author: Schmidt Felix, Stefan Bommas
 */
#include <iostream>
#include <string>
#include "Student.hpp"
#include "CursorList.hpp"
void listempty(CursorList<Student> &list);
void listsize(CursorList<Student> &list);
void listpush(CursorList<Student> &list);
void listpop(CursorList<Student> &list);
void listprint(CursorList<Student> &list);
void listinsert(CursorList<Student> &list);
void listerase(CursorList<Student> &list);
void listAreaErase(CursorList<Student> &list);
void listfind(CursorList<Student> &list);
void listfront(CursorList<Student> &list);
int main(int argc, char *argv[]){
CursorList<Student> CL1;
int command;
while(command != 0){
	std::cout << "-----------------<Modify Your Student List>----------------" << '\n'
			<< "*------<Commands>--------*" << '\n'
			<< "|0: exit the programm    |" << '\n'
			<< "|1: empty()              |"	<< '\n'
			<< "|2: size()               |"	<< '\n'
			<< "|3: push()               |"	<< '\n'
			<< "|4: pop()                |"	<< '\n'
			<< "|5: print the list       |"	<< '\n'
			<< "|6: insert() vor element |"	<< '\n'
			<< "|7: erase()              |"	<< '\n'
			<< "|8: erase(von, bis)      |"	<< '\n'
			<< "|9: find(von, bis, was)  |"	<< '\n'
			<< "|10: front()             |" << '\n'
			<< "*------------------------*"	<< '\n'
			<< "Enter number here: ";
	std::cin >> command;
	try{
		if(command == 1){
			listempty(CL1);
		}
		else if(command == 2){
			listsize(CL1);
		}
		else if(command == 3){
			listpush(CL1);
		}
		else if(command == 4){
			listpop(CL1);
		}
		else if(command == 5){
			listprint(CL1);
		}
		else if(command == 6){
			listinsert(CL1);
		}
		else if(command == 7){
			listerase(CL1);
		}
		else if(command == 8){
			listAreaErase(CL1);
		}
		else if(command == 9){
			listfind(CL1);
		}
		else if(command == 10){
			listfront(CL1);
		}
	}
	catch (const char* exception){
		std::cerr << "Error: " << exception << '\n';
	}
	std::cout << '\n';
}
return 0;
}

void listempty(CursorList<Student> &list){
	std::cout << (list.empty()? "List is empty" : "List is not empty") << '\n';
}

void listsize(CursorList<Student> &list){
	std::cout << "List has " << list.size() << " elements" << '\n';
}

void listpush(CursorList<Student> &list){
	Student element;
	std::cout << "Enter first name, surename, and date of birth in this order (three inputs required)"
			  << '\n';
	std::cin >> element;
	list.push_front(element);
	std::cout << "Element stored" << '\n';
}

void listpop(CursorList<Student> &list){
	list.pop_front();
	std::cout << "Top element has been deleted" << '\n';
}

void listprint(CursorList<Student> &list){
	for(auto itr = list.begin(); itr != list.end();++itr){
		std::cout << *itr << '\n';
	}
}

void listinsert(CursorList<Student> &list){
	Student s1;
	int index;
	std::cout << "Enter first name, surename, and date of birth in this order (three inputs required)"
			  << '\n';
	std::cin >> s1;
	std::cout << "Enter position to insert at: ";
	std::cin >> index;
	auto itr = list.begin();
	for(int i = 1; i < index ; ++i){
		++itr;
	}
	list.insert(itr, s1);
	std::cout << "Student has been inserted into the list" << '\n';
}

void listerase(CursorList<Student> &list){
	std::cout << "Enter position to remove element: ";
	int index;
	std::cin >> index;
	auto itr = list.begin();
		for(int i = 1; i < index ; ++i){
			++itr;
		}
	if(index>list.size() || list.empty()){
		throw "You shouldnt delete something that doesnt exist";
	}
	list.erase(itr);
	std::cout << "Element has been removed" << '\n';
}
void listAreaErase(CursorList<Student> &list){
	int start;
	int end;
	std::cout << "Enter start & end index of deletion (two inputs required): ";
	std::cin >> start >> end;
	auto itrStart = list.begin();
	auto itrEnd = list.begin();
	for(int i = 1; i < start ; ++i){
				++itrStart;
			}
	for(int i = 1; i < end ; ++i){
				++itrEnd;
			}
	list.erase(itrStart, itrEnd);
	std::cout << "Elements have been removed" << '\n';
}

void listfind(CursorList<Student> &list){
	std::cout << "Enter Matrikelnummer: ";
	int nummer;
	std::cin >> nummer;
	std::cout << "Enter start & end index of search (two inputs required): ";
	Student s1(nummer);
	int start;
	int end;
	std::cin >> start >> end;
	auto itrStart = list.begin();
	auto itrEnd = list.begin();
	for(int i = 1; i < start ; ++i){
		++itrStart;
	}
	for(int i = 0; i < end ; ++i){
		++itrEnd;
	}
	auto position = find(itrStart, itrEnd, s1);
	std::cout << *position << '\n' << "Student found" << '\n';
}
void listfront(CursorList<Student> &list){
	std::cout << list.front() << '\n';
}


