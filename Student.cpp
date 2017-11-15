/*
 * Student.cpp
 *
 *  Created on: 03.11.2017
 *      Author: schmi
 */
#include <iostream>
#include<cstring>
#include "Student.hpp"
int Student::m_MatrikelnummerID = 0;

Student::Student():m_Matrikelnummer(m_MatrikelnummerID)
{
	m_MatrikelnummerID++;
	strncpy(m_NameVorname, ".\0",2);
	strncpy(m_Geburtsdatum, ".\0",2);
}
void Student::setNameVorname(const char *name)
{

	strncpy (m_NameVorname, name, 9);
	m_NameVorname[9] = '\0';
	//std::cout << m_NameVorname;
}
void Student::setGeburtsdatum(const char *datum)
{
	strncpy (m_Geburtsdatum, datum, 8);
	m_Geburtsdatum[8] = '\0';
}
void Student::read(std::istream& istr)
{
	std::string name;
	std::string datum;
	istr >> name >> datum;
	this->setNameVorname(name.c_str());
	this->setGeburtsdatum(datum.c_str());

}


void Student::write(std::ostream& out) const
{
	out << "Matrikelnummer: " << m_Matrikelnummer << '\n' << "Geburtsdatum: "
		<< m_Geburtsdatum << '\n' << "NameVorname: " << m_NameVorname << '\n';
}

bool operator== (const Student &s1, const Student &s2)
{
	return s1.m_Matrikelnummer == s2.m_Matrikelnummer;
}

bool operator>= (const Student &s1, const Student &s2)
{
	return s1.m_Matrikelnummer >= s2.m_Matrikelnummer;
}

bool operator<= (const Student &s1, const Student &s2)
{
	return s1.m_Matrikelnummer <= s2.m_Matrikelnummer;
}

bool operator!= (const Student &s1, const Student &s2)
{
	return s1.m_Matrikelnummer != s2.m_Matrikelnummer;
}

bool operator< (const Student &s1, const Student &s2)
{
	return s1.m_Matrikelnummer < s2.m_Matrikelnummer;
}

bool operator> (const Student &s1, const Student &s2)
{
	return s1.m_Matrikelnummer > s2.m_Matrikelnummer;
}

std::ostream& operator<< (std::ostream& ostr, const Student& stud)
{
	stud.write(ostr);
	return ostr;
}
std::istream& operator>> (std::istream& istr, Student& stud){
	stud.read(istr);
	return istr;
}


