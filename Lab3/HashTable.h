/*
 *
 * Filename: HashTable.h
 * 
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Implements the hash table class. Contains the hashing function
 *          which is designed for strings to be hashed.
 *
 */

#include "node.h"

class HashTable {
public:
    HashTable();
    HashTable(const HashTable &aTable);
    ~HashTable();
    void DestroyTable();
    const HashTable &operator=(const HashTable &aTable);
    bool Insert(Player newPlayer);
    bool Remove(char *key);
    node *GetPlayerNode(char *key);
    int GetTableSize() const;
    int GetListSize(int index);
    void PrintList(int index);
    bool FindNode(char *key, node *traverse, node **match);
    int Hash(char *key);
private:
    int tableSize;
    
    /* Dynamic array of "heads" of linked lists. */
    node **indices;
};

HashTable::HashTable()
{
    tableSize = 3; // This is simply the value for the assignment. Easy to change.
    indices = new node*[tableSize];
    
    /* Allocates memory to each node in the array of "heads". */
    int i;
    for (i = 0; i < tableSize; i++)
        indices[i] = new node;
}

HashTable::HashTable(const HashTable &aTable)
{
    indices = new node*[tableSize];
    
    int i;
    for (i = 0; i < tableSize; i++) {
        if (aTable.indices[i] == nullptr) {
            indices[i] = nullptr;
        } else {
            indices[i] = new node;
            indices[i]->SetPlayer(*(aTable.indices[i]->GetPlayer()));
            
            node *srcNode = aTable.indices[i]->GetNext();
            node *destNode = indices[i];
            while (srcNode) {
                destNode->SetNext(new node);
                destNode->GetNext()->SetPlayer(*(srcNode->GetPlayer()));
                srcNode = srcNode->GetNext();
            }
            destNode->SetNext(nullptr);
        }
    }
}

HashTable::~HashTable()
{
    DestroyTable();
}

/* Makes it easier to manually destroy a table outside the destructor. */
void HashTable::DestroyTable()
{    
    int i;
    for (i = 0; i < tableSize; i++) {
        node *traverse(indices[i]);
        while (traverse->GetNext() != nullptr) {
            traverse = traverse->GetNext();
            traverse->GetPrev()->GetPlayer()->DeallocName();
            delete traverse->GetPrev()->GetPlayer();
            delete traverse->GetPrev();
        }
        if (traverse->GetPlayer() != nullptr) {
            traverse->GetPlayer()->DeallocName();
            delete traverse->GetPlayer();
        }
        delete traverse;
    }
    delete [] indices;
}

/* Mostly taken from the example code posted on D2L */
const HashTable &HashTable::operator=(const HashTable& aTable)
{
	if(this == &aTable) {
		return *this;
    } else {
		//release dynamically allocated memory held by current object
		DestroyTable();

		//make *this a deep copy of "aTable"
		indices = new node*[tableSize];
        tableSize = aTable.GetTableSize();

		//copy the array of linked list
		int i;	
		for(i = 0; i < tableSize; i++) {
			//copy each linked list in the array
			if (aTable.indices[i] == nullptr) {
				indices[i] = nullptr;
            } else {
				//copy the first node in current chain
				indices[i] = new node;
                indices[i]->SetPlayer(*(aTable.indices[i]->GetPlayer()));

				//copy the rest of the chain
				node *srcNode = aTable.indices[i]->GetNext();
				node *destNode = indices[i];
				while(srcNode) {
					destNode->SetNext(new node);
                    destNode->GetNext()->SetPlayer(*(srcNode->GetPlayer()));
					destNode = destNode->GetNext();
					srcNode = srcNode->GetNext();
				}
				destNode->SetNext(nullptr);
			}
		}		
		return *this;
	}
}

/* Inserts a player into the head of its hashed index. Sort of a "stack" scheme. */
bool HashTable::Insert(Player newPlayer)
{
    int index = Hash(newPlayer.GetName());
    node *traverse(indices[index]);
    node *match;
    node **matchPtr = &match; // Don't really need this, just want to use FindNode().
    if (FindNode(newPlayer.GetName(), traverse, matchPtr)) {
        newPlayer.DeallocName();
        return false;
    } else {
        if (traverse->GetPlayer() == nullptr) { // There's no data in the head of the list.
            traverse->SetPlayer(newPlayer);
        } else { 
            node *newNode;
            newNode = new node;
            newNode->SetPlayer(newPlayer);
            traverse->SetPrev(newNode);
            newNode->SetNext(traverse);
            indices[index] = newNode;
        }
        return true;
    }
}

/* Removes a player from the table if the player is there. */
bool HashTable::Remove(char *key)
{
    int index = Hash(key);
    node *match;
    node **matchPtr = &match;
    if (FindNode(key, indices[index], matchPtr)) {
        /* At this point, found a player in the table with the same name. That player's
           data is stored in "match". Make sure list sanity is maintained, then delete
           the "match" data. */
        if (match->GetPrev() != nullptr)
            match->GetPrev()->SetNext(match->GetNext());
        if (match->GetNext() != nullptr)
            match->GetNext()->SetPrev(match->GetPrev());
        if (match == indices[index]) {
            if (match->GetNext() != nullptr)
                indices[index] = match->GetNext();
            else
                indices[index] = new node;
        }
        match->GetPlayer()->DeallocName();
        delete match->GetPlayer();
        delete match;
        matchPtr = nullptr; 
        match = nullptr;
        return true;
    } else {
        return false;
    }
}

/* Quick helper function that returns the node for a player with name "key". */
node *HashTable::GetPlayerNode(char *key)
{
    node *match;
    node **matchPtr = &match; 
    match == nullptr;
    FindNode(key, indices[Hash(key)], matchPtr);
    return match;
}

int HashTable::GetTableSize() const
{
    return tableSize;
}

/* Counts up the number of nodes in the linked list starting at "index". */
int HashTable::GetListSize(int index)
{
    int count = 0;
    node *traverse(indices[index]);
    while (traverse->GetNext() != nullptr) {
        count++;
        traverse = traverse->GetNext();
    }
    if (traverse->GetPlayer() != nullptr)
        count++;
    return count;
}

/* Prints linked list starting at "index" using format in expected.txt. */
void HashTable::PrintList(int index)
{
    using namespace std;
    node *traverse(indices[index]);
    while (traverse->GetNext() != nullptr) {
        cout << "  " << traverse->GetPlayer()->GetName() << " [" << traverse->GetPlayer()->GetLevel() << "]" << endl;
        traverse = traverse->GetNext();
    }
    if (traverse->GetPlayer() != nullptr)
        cout << "  " << traverse->GetPlayer()->GetName() << " [" << traverse->GetPlayer()->GetLevel() << "]" << endl;
    else
        cout << "  EMPTY" << endl;
}

/* Checks if node with player name "key" exists in table. If so, will set
   "match" to the matching node. */
bool HashTable::FindNode(char *key, node *traverse, node **matchPtr)
{
    if (traverse->GetPlayer() != nullptr) { 
        char *testName = traverse->GetPlayer()->GetName();
        if (testName != nullptr && strcmp(testName, key) == 0) {
            *matchPtr = traverse;
            return true;
        } else {
            if (traverse->GetNext() != nullptr) {
                traverse = traverse->GetNext();
                FindNode(key, traverse, matchPtr);
            }
        }
    } else {
        return false;
    }
}
    
/* Hash function. Input a string, it will output that string's index */
int HashTable::Hash(char *key)
{
    unsigned int sum = 0; // This overflows, but matches expected text.
    int i = 0;
    while (key[i] != '\0') {
        sum = (sum * 32) + key[i];
        i++;
    }
    int index = sum % tableSize;
    return index;
}
