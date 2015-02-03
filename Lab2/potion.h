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
    Potion(PotionType aType);
    void SetType(PotionType aType);
    Potion *next;
    Potion *prev;
    friend std::ostream& operator<<(std::ostream& osObject, const Potion &potionAddr);
    private:
    PotionType type;
};


Potion::Potion()
{
    type = UNKNOWN;
    next = nullptr;
    prev = nullptr;
}

Potion::Potion(PotionType aType)
{
    type = aType;
    next = nullptr;
    prev = nullptr;
}

PotionType Potion::GetType()
{
    return type;
}

void Potion::SetType(PotionType aType)
{
    type = aType;
}  

std::ostream& operator<<(std::ostream& osObject, const Potion &potionAddr)
{
    osObject << "Potion of " << PotionTypeString(potionAddr.type) << std::endl;
    return osObject;
}

