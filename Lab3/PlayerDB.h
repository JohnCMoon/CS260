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

void PlayerDB::PrintDiagnostics()
{
}

Player *PlayerDB::FetchPlayer(char *key)
{
    node **match;
    Player *foundPlayer = table.GetPlayer(key, match);
    return foundPlayer;
}

bool PlayerDB::AddPlayer(Player newPlayer)
{
    table.Insert(newPlayer);
    return true;
}

bool PlayerDB::RemovePlayer(char *key)
{
    if (table.Remove(key))
        return false;
    else
        return true;
}
