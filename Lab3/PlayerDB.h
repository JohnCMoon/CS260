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
    cout << "Fetching player \"" << key << "\" -- ";
    node *playerNode = table.GetPlayerNode(key);
    Player *foundPlayer;
    if (playerNode != nullptr) {
        foundPlayer = playerNode->GetPlayer();
        cout << "Success!" << endl;
    } else {
        foundPlayer = nullptr;
        cout << "Failed." << endl;
    }
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
    cout << "Removing player \"" << key << "\" from the databse -- ";
    if (table.Remove(key)) {
        cout << "Success!" << endl;
        return true;
    } else {
        cout << "Failed." << endl;
        return false;
    }
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
    }
    return sum;
}
