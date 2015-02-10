/*
 *
 *  File: potion.h
 * 
 *  Author: John Moon <john.moon1@pcc.edu>
 *
 *  Purpose: Implements the potion class includes data members for the potion
 *           and accessor methods. This acts as the linked list class.
 *
 */

#include <cstring>
#include "main.h"

class Potion {
public:
    PotionType GetType();
    Potion();
    Potion(PotionType aType);
    void SetType(PotionType aType);
    Potion *GetNext();
    Potion *GetPrev();
    void SetNext(Potion *aNext);
    void SetPrev(Potion *aPrev);
    friend std::ostream& operator<<(std::ostream& osObject, const Potion &potionAddr);
private:
    Potion *next;
    Potion *prev;
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

Potion *Potion::GetNext()
{
    return next;
}

Potion *Potion::GetPrev()
{
    return prev;
}

void Potion::SetNext(Potion *aNext)
{
    next = aNext;
}

void Potion::SetPrev(Potion *aPrev)
{
    prev = aPrev;
}

std::ostream& operator<<(std::ostream& osObject, const Potion &potionAddr)
{
    osObject << "Potion of " << PotionTypeString(potionAddr.type) << std::endl;
    return osObject;
}
