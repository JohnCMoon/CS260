// enable Visual Studio's memory leak checking
#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#pragma warning(disable:4305)		// allow conversion of double constants to floats

#include "hashtable.h"

int main()
{
	hashTable*	students = new hashTable();

	// insert students
	students->insert("900123456", data("Blue, Stella", "900123456", 4.0));
	students->insert("900456222", data("Red, Panama", "900456222", 3.8));
	students->insert("900233678", data("White, Barry", "900233678", 3.9));
	students->insert("900333444", data("Gray, Earl", "900333444", 3.6));
	cout << "\noriginal data set -- " << *students;

	students->insert("907654321", data("Violet, Ultra", "907654321", 2.6));
	cout << "\nafter insert -- " << *students;

	// separate block here so that temp will go out of scope
	// and its destructor will be called BEFORE we list memeory leaks
	{
	data	temp;

	if(! students->retrieve("907654321", temp))
		cout << "\ndata not present!" << endl << endl ;
	else
		cout << "\nthe newly added student: " << temp << endl;

	if(! students->remove("907654321"))
		cout << "\nstack is empty!" << endl << endl;
	else
		cout << "\nafter remove -- " << *students;
	}
	
	//test copy constructor
	hashTable *copy = new hashTable(*students);
	cout << "\ncopy of the data set --" << *copy;

	cout << "\nThank you for testing me!" << endl << endl;

	delete copy;
	delete students;

// in Visual Studio, report on memory leaks in the Output window
#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}