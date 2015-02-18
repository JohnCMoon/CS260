#ifndef DATA_H
#define DATA_H
#include <iostream>
using namespace std;
class data
{
public:
	data();
	data(char* name, char* pccId, float gpa);
	data(const data& student);		//copy constructor: make current object a copy of "student"
	~data();						//destructor: release the dynamically allocated memory

	void getName(char* name) const;
	void getPccId(char* pccId) const;
	float getGpa(void) const;

	void setName(char* name);
	void setPccId(char* pccId);
	void setGpa(float gpa);

	const data& operator=(const data& student);	 //overloading assignment operator
	friend ostream& operator<<(ostream& out, const data& student);

private:
	char*	name;
	char*	pccId;
	float	gpa;
};

bool operator< (const data& d1, const data& d2);
bool operator== (const data& d1, const data& d2);

#endif