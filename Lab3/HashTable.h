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
    void Insert(Player newPlayer);
    bool Remove(char *key);
    Player *GetPlayer(char *key, node **match);
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

void HashTable::Insert(Player newPlayer)
{
    int index = Hash(newPlayer.GetName());
    node *newNode;
    newNode = new node;
    newNode->SetPlayer(newPlayer);
    node *traverse(&indices[index]);
    while (traverse->GetNext() != nullptr)
        traverse = traverse->GetNext();
    if (traverse->GetPlayer()->GetGender() == UNKNOWN)
        traverse = newNode;
    else
        traverse->SetNext(newNode);
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
 
bool HashTable::FindNode(char *key, node *traverse, node **match)
{
    if (strcmp(traverse->GetPlayer()->GetName(), key) == 0) {
        *match = traverse;
        return true;
    } else {
        if (traverse->GetNext() == nullptr) {
            return false;
        } else {
            traverse = traverse->GetNext();
            FindNode(key, traverse, match);
        }
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
