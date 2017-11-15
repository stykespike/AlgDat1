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
if(CL1.empty()){
	std::cout << CL1.size();
	std::cout << CL1.empty();
}
return 0;
}




