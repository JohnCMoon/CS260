/*
 *
 * File: stack.h
 *
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Implements the stack ADT.
 *
 */

class stack {
public:
    bool isEmptyStack();
    bool isFullStack();
    bool push(Potion *newPotion);
    bool pop(Potion &potion);
    void SetLimit(int limit);
    int GetCount();
    stack();
    stack(const stack &newStack);
    stack &operator = (const stack &newStack);
    ~stack();
private:
    int maxStack;
    Potion *top;
};

stack::stack()
{
    top = new Potion;
}
    
stack::stack(const stack &newStack)
{
    maxStack = newStack.maxStack;
    top = new Potion;
    *top = *newStack.top;
}

stack &stack::operator = (const stack &otherStack)
{
    maxStack = otherStack.maxStack;
    top = new Potion;
    *top = *otherStack.top;
    return *this;
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

void stack::SetLimit(int limit)
{
    maxStack = limit;
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
