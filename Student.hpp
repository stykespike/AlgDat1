/*
 * Student.hpp
 *
 *  Created on: 03.11.2017
 *      Author: Schmidt Felix, Stefan Bommas
 */

#ifndef STUDENT_HPP_
#define STUDENT_HPP_
class Student{
	static int m_MatrikelnummerID;
	int m_Matrikelnummer;
	char m_Vorname[10];
	char m_Nachname[10];
	char m_Geburtsdatum[9];

public:
	Student();
	Student(int matrikelnummer);
	Student(const Student& std );

	int getMatrikelnummer()const {return m_Matrikelnummer;}
	const char* getVorname() const {return m_Vorname;}
	const char* getGeburtsdatum() const {return m_Geburtsdatum;}
	const char* getNachname() const {return m_Nachname;}
private:
	void setVorname(const char *name);
	void setGeburtsdatum(const char *datum);
	void setNachname(const char *name);
public:
	friend bool operator== (const Student &s1, const Student &s2);
	friend bool operator>= (const Student &s1, const Student &s2);
	friend bool operator<= (const Student &s1, const Student &s2);
	friend bool operator!= (const Student &s1, const Student &s2);
	friend bool operator< (const Student &s1, const Student &s2);
	friend bool operator> (const Student &s1, const Student &s2);
private:
	void read(std::istream& istr);
	void write(std::ostream& out) const;
public:
	friend std::ostream& operator<< (std::ostream &ostr, const Student& stud);
	friend std::istream& operator>> (std::istream &istr, Student& stud);
};


#endif /* STUDENT_HPP_ */
