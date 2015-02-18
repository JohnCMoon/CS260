#include "hashtable.h"
#include <iostream>
#include <fstream>
using namespace std;

/************************
private:
	node ** table;
	int capacity;
	int size;
	const static int DEFAULT_CAPACITY = 11;
************************/
hashTable::hashTable() :
	size(0),
	capacity(DEFAULT_CAPACITY),
	table(new node*[DEFAULT_CAPACITY])
{
	//initialize each head of the individual linked list
	for(int i=0; i<capacity; i++)
		table[i] = NULL;
}

hashTable::hashTable(const hashTable& aTable):capacity(aTable.capacity), size(aTable.size)
{
	table = new node*[capacity];

	//copy the array of linked list
	int i;	
	for(i=0; i<capacity; i++)
	{
		//copy each linked list in the array
		if (aTable.table[i] == NULL)
			table[i] = NULL;
		else
		{
			//copy the first node in current chain
			table[i] = new node(aTable.table[i]->item);

			//copy the rest of the chain
			node * srcNode = aTable.table[i]->next;
			node * destNode = table[i];
			while(srcNode)
			{
				destNode->next = new node(srcNode->item);
				destNode = destNode->next;
				srcNode = srcNode->next;
			}
			destNode->next = NULL;
		}
	}
}

const hashTable& hashTable::operator= (const hashTable& aTable)
{
	if(this == &aTable)
		return *this;
	else
	{
		//release dynamically allocated memory held by current object
		destroyTable(); 

		//make *this a deep copy of "aTable"
		table = new node*[capacity];
		capacity = aTable.capacity;
		size = aTable.size;

		//copy the array of linked list
		int i;	
		for(i=0; i<capacity; i++)
		{
			//copy each linked list in the array
			if (aTable.table[i] == NULL)
				table[i] = NULL;
			else
			{
				//copy the first node in current chain
				table[i] = new node(aTable.table[i]->item);

				//copy the rest of the chain
				node * srcNode = aTable.table[i]->next;
				node * destNode = table[i];
				while(srcNode)
				{
					destNode->next = new node(srcNode->item);
					destNode = destNode->next;
					srcNode = srcNode->next;
				}
				destNode->next = NULL;
			}
		}		
		return *this;
	}
}

void hashTable::destroyTable ()
{
	//delete each chain
	int i;
	for(i=0; i<capacity; i++)
	{
		node * head = table[i];
		node * curr;
		while(head)
		{
			curr = head->next;
			head->next = NULL;
			delete head;
			head = curr;
		}
	}

	//delete the array
	delete [] table;
}
hashTable::~hashTable()
{
	destroyTable(); 
}

void hashTable::insert (char const * const key, const data& aData)
{
	//calculate the insertion position (the index of the array)
	size_t index = calculateIndex(key);

	//create a new node to hold data
	node * newNode = new node(aData);

	//insert the new node at the beginning of the linked list
	newNode->next = table[index];
	table[index] = newNode;
	size++;
}

bool hashTable::remove (char const * const key)
{
	//calculate the removal position (the index of the array)
	size_t index = calculateIndex(key);	

	//search for the data to be removed in the chain (linked list)
	node * curr = table[index];
	node * prev = NULL;
	char id[100];
	while (curr)
	{
		curr->item.getPccId (id);
		if(strcmp(key, id) == 0)
		{
			//find match and remove the node
			if(!prev)
				table[index] = curr->next;
			else
				prev->next = curr->next;

			curr->next = NULL;
			delete curr;
			size--;
			return true;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return false;
}

bool hashTable::retrieve (char const * const key, data & aData)const
{
	//calculate the retrieval position (the index of the array)
	size_t index = calculateIndex(key);

	//search for the data in the chain (linked list)
	node * curr = table[index];
	char id[100];
	while (curr)
	{
		curr->item.getPccId (id);
		if(strcmp(key, id) == 0)
		{
			//find match and return the data
			aData = curr->item;
			return true;
		}
		else
			curr = curr->next;
	}

	//data is not in the table
	return false;
}

ostream& operator<<(ostream& out, hashTable& ht)
{
	int i;
	hashTable::node * curr;

	cout << "Data in the table: " << endl << endl;
	for(i=0; i < ht.capacity; i++)
	{
		for(curr = ht.table[i]; curr; curr = curr->next)		
			//we can use << on data object because we overload << in the data class
			cout << '\t' << curr->item << endl;
	}

	return out;
}

int hashTable::getSize (void) const
{
	return size;
}

size_t hashTable::calculateIndex (char const * const key)const
{
	// something is very wrong with this hash function -- what?
	size_t length = strlen(key);
	size_t hashValue = 0;

	for(size_t i=0; i<length; i++)
		hashValue += key[i];
	return hashValue % capacity;
}







	


