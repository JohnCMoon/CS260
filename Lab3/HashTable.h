/*
 *
 * Filename: HashTable.h
 * 
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Implements the hash table class. Contains the hashing function
 * which is designed for strings to be hashed.
 *
 */

#include "node.h"

class HashTable {
public:
    HashTable();
    HashTable(const HashTable &aTable);
    ~HashTable();
    bool Insert(Player newPlayer);
    bool Remove(char *key);
    node *GetPlayerNode(char *key);
    int GetTableSize();
    int GetListSize(int index);
    void PrintList(int index);
    bool FindNode(char *key, node *traverse, node **match);
    int Hash(char *key);
    const HashTable &operator=(const HashTable &aTable);
    friend std::ostream &operator<<(std::ostream &out, HashTable &aTable);
private:
    int tableSize;
    node **indices;
};

HashTable::HashTable()
{
    tableSize = 3;
    indices = new node*[tableSize];
    int i;
    for (i = 0; i < tableSize; i++)
        indices[i] = new node;
}

HashTable::~HashTable()
{    
    int i;
    for (i = 0; i < tableSize; i++) {
        node *traverse(indices[i]);
        while (traverse->GetNext() != nullptr) {
            traverse = traverse->GetNext();
            traverse->GetPrev()->GetPlayer()->DeallocName();
            delete traverse->GetPrev();
        }
        traverse->GetPlayer()->DeallocName();
        delete traverse;
    }
}

bool HashTable::Insert(Player newPlayer)
{
    using namespace std;
    int index = Hash(newPlayer.GetName());
    node *traverse(indices[index]);
    node *match;
    node **matchPtr = &match; // Don't really need this, just want to use FindNode().
    if (FindNode(newPlayer.GetName(), traverse, matchPtr)) {
        return false;
    } else {
        if (traverse->GetPlayer() == nullptr) {
            traverse->SetPlayer(newPlayer);
        } else { 
            node *newNode;
            newNode = new node;
            newNode->SetPlayer(newPlayer);
            while (traverse->GetNext() != nullptr)
                traverse = traverse->GetNext();
            traverse->SetNext(newNode);
            newNode->SetPrev(traverse);
        }
        return true;
    }
}

bool HashTable::Remove(char *key)
{
    int index = Hash(key);
    node *match;
    node **matchPtr = &match;
    if (FindNode(key, indices[index], matchPtr)) {
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
        delete match;
        matchPtr = nullptr; 
        match = nullptr;
        return true;
    } else {
        return false;
    }
}

node *HashTable::GetPlayerNode(char *key)
{
    node *match;
    node **matchPtr = &match; 
    if (FindNode(key, indices[Hash(key)], matchPtr))
        return match;
    else
        return nullptr;
}

int HashTable::GetTableSize()
{
    return tableSize;
}

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
    

int HashTable::Hash(char *key)
{
    unsigned long sum = 0;
    int i = 0;
    while (key[i] != '\0' ) {    
        sum = (sum * 32) + key[i];
        i++;
    }
    int index = sum % tableSize;
    return index;
}
