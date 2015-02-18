#include "data.h"
#include <iostream>
#include <iomanip>
using namespace std;
#pragma warning(disable:4996)		// allow call to strcpy
/*************************
private:
	char* name;
	char* pccId;
	float gpa;
*************************/
data::data():name(NULL), pccId(NULL), gpa(0)
{
}

data::data(char* name, char* pccId, float gpa) :
	name(NULL),
	pccId(NULL),
	gpa(gpa)
{
	setName(name);
	setPccId(pccId);
}
	
data::data(const data& student) : name(NULL), pccId(NULL)
{
	setName(student.name);
	setPccId(student.pccId);
	setGpa(student.gpa);
}

const data& data::operator=(const data& student)
{
	//if it is a self copy, don't do anything
	if(this == &student)
		return *this;
	//make current object *this a copy of the passed in student
	else
	{
		setName(student.name);
		setPccId(student.pccId);
		setGpa(student.gpa);
		return *this;
	}
}

data::~data()
{
	if(name)
		delete[] name;
	if(pccId)
		delete[] pccId;
}

void data::getName(char * name) const
{
	strcpy(name, this->name);
}

void data::getPccId(char * pccId) const
{
	strcpy(pccId, this->pccId);
}

float data::getGpa(void) const
{
	return gpa;
}

void data::setName(char * name)
{
	//release the exisisting memory if there is any
	if(this->name)
		delete [] this->name;

	//set new name
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
}

void data::setPccId(char * pccId)
{
	//release the exisisting memory if there is any
	if(this->pccId)
		delete [] this->pccId;

	//set new Id
	this->pccId = new char[strlen(pccId)+1];
	strcpy(this->pccId, pccId);
}

void data::setGpa(float gpa)
{
	this->gpa = gpa;
}

bool operator<(const data& d1, const data& d2)
{
	char name1[100];
	char name2[100];

	d1.getName(name1);
	d2.getName(name2);

	if(strcmp(name1, name2) < 0)
		return true;
	else
		return false;
}

bool operator==(const data& d1, const data& d2)
{
	char id1[100];
	char id2[100];

	d1.getPccId(id1);
	d2.getPccId(id2);

	if(strcmp(id1, id2) == 0)
		return true;
	else
		return false;
}

ostream& operator<<(ostream& out, const data& student)
{
	out << setw(20) << student.name
		<< setw(15) << student.pccId
		<< setw(8) << fixed << setprecision(2) << student.gpa;
	return out;
}