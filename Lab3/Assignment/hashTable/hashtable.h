#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "data.h"

class hashTable
{
public:
	hashTable();
	hashTable(const hashTable& aTable);
	~hashTable();

	const hashTable& operator= (const hashTable& aTable);

	void insert(char const * const key, const data& aData);
	bool remove(char const * const key);
	bool retrieve(char const * const key, data& aData)const;
	int getSize(void)const;

	friend ostream& operator<<(ostream& out, hashTable& ht);

private:
	struct node
	{
		data item;
		node * next;
		node(const data& aData) : item(aData), next(NULL) {}
	};
	node ** table;
	int capacity;
	int size;
	const static int DEFAULT_CAPACITY = 11;

	void destroyTable();
	size_t calculateIndex(char const * const key)const;
};
#endif
