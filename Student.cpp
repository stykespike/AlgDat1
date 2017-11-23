/*
 * Student.cpp
 *
 *  Created on: 03.11.2017
 *      Author: Schmidt Felix, Stefan Bommas
 */
#include <iostream>
#include<cstring>
#include "Student.hpp"
int Student::m_MatrikelnummerID = 0;

Student::Student():m_Matrikelnummer(m_MatrikelnummerID)
{
	m_MatrikelnummerID++;
	strncpy(m_Vorname, ".\0",2);
	strncpy(m_Nachname, ".\0",2);
	strncpy(m_Geburtsdatum, ".\0",2);
}
Student::Student(int matrikelnummer):m_Matrikelnummer(matrikelnummer){
	strncpy(m_Vorname, ".\0",2);
	strncpy(m_Nachname, ".\n",2);
	strncpy(m_Geburtsdatum,".\0",2);
}
Student::Student(const Student& std): m_Matrikelnummer(std.m_Matrikelnummer)
{
	strncpy(m_Vorname, std.m_Vorname,sizeof(m_Vorname));
	strncpy(m_Nachname, std.m_Nachname,sizeof(m_Nachname));
	strncpy(m_Geburtsdatum,std.m_Geburtsdatum ,sizeof(m_Geburtsdatum));
}
void Student::setVorname(const char *name)
{
	strncpy (m_Vorname, name, 9);
	m_Vorname[9] = '\0';
}
void Student::setNachname(const char *name){
	strncpy(m_Nachname , name, 9);
	m_Nachname[9] = '\0';
}
void Student::setGeburtsdatum(const char *datum)
{
	strncpy (m_Geburtsdatum, datum, 8);
	m_Geburtsdatum[8] = '\0';
}
void Student::read(std::istream& istr)
{
	std::string vorname;
	std::string nachname;
	std::string datum;
	istr >> vorname >> nachname >> datum;
	this->setVorname(vorname.c_str());
	this->setNachname(nachname.c_str());
	this->setGeburtsdatum(datum.c_str());

}


void Student::write(std::ostream& out) const
{
	out << "Matrikelnummer: " << m_Matrikelnummer << '\n' << "Geburtsdatum: "
		<< m_Geburtsdatum << '\n' << "Vorname: " << m_Vorname << '\n'
		<< "Nachname: " << m_Nachname << '\n';
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


