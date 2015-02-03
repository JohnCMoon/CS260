class stack {
public:
    void InitStack(int max);
    bool isEmptyStack();
    bool isFullStack();
    bool push(Potion *newPotion);
    Potion *GetTop();
    bool pop();
    int GetCount();
    int GetRemainingSpace();
private:
    int maxStack;
    Potion *top;
};

void stack::InitStack(int max)
{
    maxStack = max;
    top = new Potion;
    top->next = nullptr;
    top->prev = nullptr;
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
    top->prev = newPotion;
    newPotion->next = top;
    newPotion->prev = nullptr;
    top = newPotion;
}

Potion *stack::GetTop()
{
    return top;
}

bool stack::pop()
{
    if (!isEmptyStack()) {
        Potion *tmp(top);
        top = top->next;
        top->prev = nullptr;
        delete tmp;
        tmp = nullptr;
    } else {
        return false;
    }
}

int stack::GetCount()
{
    int count = 0;
    Potion *tmp(top);
    while (tmp->next != nullptr && tmp->GetType() != UNKNOWN) {
        count++;
        tmp = tmp->next;
    }
    if (tmp->GetType() != UNKNOWN)
        count++;
    return count;
}

int stack::GetRemainingSpace()
{
    int spaceRemaining = 0;
    spaceRemaining = maxStack - GetCount();
    return spaceRemaining;
}
