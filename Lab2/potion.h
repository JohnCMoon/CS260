/*
 *
 *  File: potion.h
 * 
 *  Author: John Moon <john.moon1@pcc.edu>
 *
 *  Purpose: Implements the potion class includes data members for the potion
 *           and accessor methods
 *
 */

#include "main.h"

class Potion {
public:
    PotionType GetType();
    Potion();
    Potion *next;
    Potion *prev;
private:
    PotionType type;
};

Potion::Potion()
{
    type = UNKNOWN;
    next = nullptr;
    prev = nullptr;
}

PotionType Potion::GetType()
{
    return type;
}
