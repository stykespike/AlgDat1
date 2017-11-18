/*
 * main.cpp
 *
 *  Created on: 03.11.2017
 *      Author: schmi
 */
#include <iostream>
//#include <cstring>
#include <string>
#include "Student.hpp"
#include "CursorList.hpp"
int main(int argc, char *argv[]){
CursorList<Student> CL1;
Student s1 ;
Student s2;

CL1.push_front(s1);
std::cout << CL1.size() << '\n'; //1
CL1.pop_front();
std::cout << CL1.size() << '\n';//0
CL1.push_front(s2);
CL1.push_front(s2);
CL1.push_front(s1);
std::cout << CL1.size() << '\n';//3
CL1.pop_front();
CL1.pop_front();
std::cout << CL1.size() << '\n';//1
return 0;
}




