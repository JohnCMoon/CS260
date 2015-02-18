/*
 *
 * File: Player.h
 * 
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Implements the Player class. Defines and works with the player's
 *          name, gender, and level.
 *
 */

#include <cstring>

enum Gender {MALE, FEMALE, UNKNOWN}; 

class Player {
public:
    Player();
    Player(char *newName, Gender newGender);
    void LevelUp();
    void SetName(char *newName);
    char *GetName();
    void SetLevel(int newLevel);
    int GetLevel();
    void SetGender(Gender newGender);
    Gender GetGender();
private:
    char *name;
    Gender gend;
    int level;
};

Player::Player()
{
    name = nullptr;
    gend = UNKNOWN;
    level = NULL;
}

Player::Player(char *newName, Gender newGender)
{
    int nameLength = strlen(newName);
    name = new char [nameLength + 1];
    strcpy(name, newName);
    delete newName;
    newName = nullptr;
    gend = newGender;
}

void Player::LevelUp()
{
    level++;
}

void Player::SetName(char *newName)
{
    int length = strlen(newName);
    name = new char [length + 1];
    strcpy(name, newName);
    delete [] newName;
    newName = nullptr;
}

char *Player::GetName()
{
    return name;
}

void Player::SetLevel(int newLevel)
{
    level = newLevel;
}

int Player::GetLevel()
{
    return level;
}

void Player::SetGender(Gender newGender)
{
    gend = newGender;
}

Gender Player::GetGender()
{
    return gend;
}