/*
 * Student.hpp
 *
 *  Created on: 03.11.2017
 *      Author: schmi
 */

#ifndef STUDENT_HPP_
#define STUDENT_HPP_
class Student{
	static int m_MatrikelnummerID;
	const int m_Matrikelnummer;
	char m_NameVorname[10];
	char m_Geburtsdatum[9];

public:
	Student();

	int getMatrikelnummer(){return m_Matrikelnummer;}
	const char* getNameVorname() const {return m_NameVorname;}
	const char* getGeburtsdatum() const {return m_Geburtsdatum;}

	//void setMartrikelnummer();
	void setNameVorname(const char *name);
	void setGeburtsdatum(const char *datum);


	friend bool operator== (const Student &s1, const Student &s2);
	friend bool operator>= (const Student &s1, const Student &s2);
	friend bool operator<= (const Student &s1, const Student &s2);
	friend bool operator!= (const Student &s1, const Student &s2);
	friend bool operator< (const Student &s1, const Student &s2);
	friend bool operator> (const Student &s1, const Student &s2);

	void read(std::istream& istr);
	void write(std::ostream& out) const;

	friend std::ostream& operator<< (std::ostream &ostr, const Student& stud);
	friend std::istream& operator>> (std::istream &istr, Student& stud);
};


#endif /* STUDENT_HPP_ */
