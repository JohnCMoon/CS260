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
    Player *GetPlayer(char *key, node **match);
    int GetTableSize();
    int GetListSize(int index);
    void PrintList(int index);
    bool FindNode(char *key, node *traverse, node **match);
    int Hash(char *key);
    const HashTable &operator=(const HashTable &aTable);
    friend std::ostream &operator<<(std::ostream &out, HashTable &aTable);
private:
    int tableSize;
    node *indices;
};

HashTable::HashTable()
{
    tableSize = 3;
    indices = new node[tableSize];
}

HashTable::~HashTable()
{
    delete [] indices;
}

bool HashTable::Insert(Player newPlayer)
{
    int index = Hash(newPlayer.GetName());
    node *traverse(&indices[index]);
    node **match; // Don't really need this, just want to use FindNode().
    if (FindNode(newPlayer.GetName(), traverse, match)) {
        return false;
    } else {
        node *newNode;
        newNode = new node;
        newNode->SetPlayer(newPlayer);
        while (traverse->GetNext() != nullptr)
            traverse = traverse->GetNext();
        if (traverse->GetPlayer() == nullptr)
            traverse = newNode;
        else
            traverse->SetNext(newNode);
        return true;
    }
}

bool HashTable::Remove(char *key)
{
    node **match;
    if (FindNode(key, &indices[Hash(key)], match)) {
        (*match)->GetPrev()->SetNext((*match)->GetNext());  
        (*match)->GetNext()->SetPrev((*match)->GetPrev());
        delete *match;
        match = nullptr;
        return true;
    } else {
        match = nullptr;
        return false;
    }
}

Player *HashTable::GetPlayer(char *key, node **match)
{
    if (FindNode(key, &indices[Hash(key)], match))
        return (*match)->GetPlayer();
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
    node *traverse(&indices[index]);
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
    node *traverse(&indices[index]);
    while (traverse->GetNext() != nullptr) {
        cout << "  " << traverse->GetPlayer()->GetName() << " [" << traverse->GetPlayer()->GetLevel() << "]" << endl;
        traverse = traverse->GetNext();
    }
    if (traverse->GetPlayer() != nullptr)
        cout << "  " << traverse->GetPlayer()->GetName() << " [" << traverse->GetPlayer()->GetLevel() << "]" << endl;
    else
        cout << "  EMPTY" << endl;
}

bool HashTable::FindNode(char *key, node *traverse, node **match)
{
    if (traverse->GetPlayer() != nullptr) { 
        char *testName = traverse->GetPlayer()->GetName();
        if (testName != nullptr && strcmp(testName, key) == 0) {
            *match = traverse;
            return true;
        } else {
            if (traverse->GetNext() != nullptr) {
                traverse = traverse->GetNext();
                FindNode(key, traverse, match);
            }
        }
    } else {
        return false;
    }
}
    

int HashTable::Hash(char *key)
{
    int index = 0;
    int i = 0;
    while (key[i] != '\0' ) {    
        index = (index * 32) + key[i];
        i++;
    }
    index = index % tableSize;
    return index;
}
