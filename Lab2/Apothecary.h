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
    bool BuyPotion(Potion &potion);
    Apothecary();
    Apothecary(int aShelfLimit, int aOrderLimit);
private:
    stack OnShelf;
    int ShelfLimit;
    queue InQueue;
    int OrderLimit;
};

Apothecary::Apothecary()
{
    int max = 10; // Just choosing a max
    OnShelf.InitStack(max);
    ShelfLimit = max;   
    InQueue.InitQueue(max);
    OrderLimit = max;
}

Apothecary::Apothecary(int aShelfLimit, int aOrderLimit)
{
    OnShelf.InitStack(aShelfLimit);
    ShelfLimit = aShelfLimit;
    InQueue.InitQueue(aOrderLimit);
    OrderLimit = aOrderLimit;
}

/* Takes the potion type argument and adds a potion of that type to the end */
/* of the queue. */
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
    int maxCanMake = OnShelf.GetRemainingSpace();
    int i;
    for (i = 0; i < maxCanMake; i++) {
        if (!InQueue.isEmptyQueue()) {
            Potion *freshPotion = InQueue.RemPotion();
            OnShelf.push(freshPotion);
        } else {
            break;
        }
    } 
    return i;
}

/* Pops one potion off the stack */
bool Apothecary::BuyPotion(Potion &potion)
{
    if(OnShelf.pop())
        return true;
    else
        return false;
}
