/*
 *
 *  File: Apothecary.h
 *
 *  Author: John Moon <john.moon1@pcc.edu>
 *
 *  Purpose: Implements the apothecary class using stacks and queues. Allows
 *           order submission, making potions, and buying potions.
 *
 */

#include "potion.h"
#include "stack.h"
#include "queue.h"

using namespace std;

class Apothecary {
public:
    bool OrderPotion(PotionType potion);
    int MakePotions();
    void RecursiveMake(int *potionsMade);
    bool BuyPotion(Potion &potion);
    Apothecary();
    Apothecary(int ShelfLimit, int OrderLimit);
private:
    stack OnShelf;
    queue InQueue;
};

Apothecary::Apothecary(int OrderLimit, int ShelfLimit)
{
    OnShelf.SetLimit(ShelfLimit);
    InQueue.SetLimit(OrderLimit);
}

/* Takes the potion type argument and adds a potion of that type to the end
   of the queue. */
bool Apothecary::OrderPotion(PotionType newPotionType)
{
    Potion *newPotion;
    newPotion = new Potion;
    newPotion->SetType(newPotionType);
    if (InQueue.AddPotion(newPotion)) {
        return true;
    } else {
        delete newPotion;
        newPotion = nullptr;
        return false;
    }
}

/* Takes the queue of orders and turns them into on the shelf potions. */
int Apothecary::MakePotions()
{
    int *tmpPtr;
    tmpPtr = new int;
    *tmpPtr = 0;
    RecursiveMake(tmpPtr);
    int potionsMade = *tmpPtr;
    delete tmpPtr;
    tmpPtr = nullptr;
    return potionsMade;
}

void Apothecary::RecursiveMake(int *potionsMade)
{
    if (!InQueue.isEmptyQueue() && !OnShelf.isFullStack()) {
        Potion *freshPotion;
        freshPotion = new Potion;
        freshPotion->SetType(InQueue.RemPotion());
        OnShelf.push(freshPotion);
        cout << "Made a " << PotionTypeString(freshPotion->GetType()) << " potion." << endl;    
        (*potionsMade)++;
        RecursiveMake(potionsMade);
    } else {
        if (OnShelf.isFullStack())
            cout << "The shelf of potions is full.  You can't make any more until somebody buys some." << endl;
    }
} 

/* Pops one potion off the stack */
bool Apothecary::BuyPotion(Potion &potion)
{
    if(OnShelf.pop(potion))
        return true;
    else
        return false;
}
