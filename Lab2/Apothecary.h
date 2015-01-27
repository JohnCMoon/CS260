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

bool Apothecary::OrderPotion(PotionType potion)
{
    return true;
}

int Apothecary::MakePotions()
{
    return 5;
}

bool Apothecary::BuyPotion(Potion &potion)
{
    return true;
}
