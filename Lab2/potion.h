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
//    friend std::ostream& operator<<(ostream&, const &Potion);
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

//std::ostream &operator<<(ostream& osOperator, const &Potion potionAddr)
//{
//    return("Potion of " << PotionTypeString(potionAddr) << endl);
//}
