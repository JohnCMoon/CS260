/*
 * File: stack.h
 *
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Implements the stack ADT.
 *
 */

class stack {
public:
    void InitStack(int max);
    bool isEmptyStack();
    bool isFullStack();
    bool push(Potion *newPotion);
    bool pop(Potion &potion);
    int GetCount();
    ~stack();
private:
    int maxStack;
    Potion *top;
};

void stack::InitStack(int max)
{
    maxStack = max;
    top = new Potion;
    top->SetNext(nullptr);
    top->SetPrev(nullptr);
}

stack::~stack()
{
    Potion *tmp(top);
    while (tmp->GetNext() != nullptr) {
        tmp = tmp->GetNext();
        delete tmp->GetPrev();
        tmp->SetPrev(nullptr);
    }
    delete tmp;
    tmp = nullptr;
    top = nullptr;
}

bool stack::isEmptyStack()
{
    if (GetCount() == 0)
        return true;
    else
        return false;
}

bool stack::isFullStack()
{
    if (GetCount() == maxStack)
        return true;
    else
        return false;
}

bool stack::push(Potion *newPotion)
{
    if (!isFullStack()) {
        top->SetPrev(newPotion);
        newPotion->SetNext(top);
        newPotion->SetPrev(nullptr);
        top = newPotion;
        return true;
    } else {
        return false;
    }
}

bool stack::pop(Potion &potion)
{
    if (!isEmptyStack()) {
        if (top->GetNext() == nullptr) {
            PotionType nullType = UNKNOWN;
            top->SetType(nullType);
        } else {
            top = top->GetNext();
            potion = *top->GetPrev();
            delete top->GetPrev();
            top->SetPrev(nullptr);
        }
        return true;
    } else {
        return false;
    }
}

int stack::GetCount()
{
    int count = 0;
    Potion *tmp(top);
    while (tmp->GetNext() != nullptr) {
        count++;
        tmp = tmp->GetNext();
    }
    if (tmp->GetType() != UNKNOWN)
        count++;
    return count;
}
