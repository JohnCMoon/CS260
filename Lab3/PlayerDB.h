/*
 *
 * File: PlayerDB.h
 *
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Implements the PlayerDB class. Deals with io operations on the
 *          hashing table.
 *
 */

class PlayerDB {
public:
    void PrintDiagnostics();
    Player *FetchPlayer(char *key);
    bool AddPlayer(Player newPlayer);
    bool RemovePlayer(char *key);
    int GetTableSize();
    int GetEntryCount();
private:
    HashTable table;
}; 

using namespace std;

void PlayerDB::PrintDiagnostics()
{
    cout << "===================" << endl;
    cout << "Hash Table Diagnostics" << endl << endl;
    cout << "Table Size: " << GetTableSize() << endl;
    cout << "Number of Entries: " << GetEntryCount() << endl;
    int i;
    for (i = 0; i < GetTableSize(); i++) {
        cout << "Slot[" << i << "]:" << endl;
        table.PrintList(i);
    }
    cout << "===================" << endl;
}

Player *PlayerDB::FetchPlayer(char *key)
{
    node **match;
    Player *foundPlayer = table.GetPlayer(key, match);
    return foundPlayer;
}

bool PlayerDB::AddPlayer(Player newPlayer)
{
    cout << "Attempting to add player \"" << newPlayer.GetName() << "\" to the database -- ";
    if (table.Insert(newPlayer)) {
        cout << "Success!" << endl;
        return true;
    } else {
        cout << "Failed." << endl;
        return false;
    }
}

bool PlayerDB::RemovePlayer(char *key)
{
    if (table.Remove(key))
        return false;
    else
        return true;
}

int PlayerDB::GetTableSize()
{
   return table.GetTableSize();
} 

int PlayerDB::GetEntryCount()
{
    int sum = 0;
    int i;
    for (i = 0; i < GetTableSize(); i++) {
        sum = sum + table.GetListSize(i);
        cout << "So the list size in " << i << " is " << table.GetListSize(i) << endl;
    }
    return sum;
}
