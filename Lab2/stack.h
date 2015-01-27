class stack {
public:
    void InitStack(int max);
    bool isEmptyStack();
    bool isFullStack();
    bool push(Potion *newPotion);
    Potion *GetTop();
    Potion *pop();
    int GetCount();
private:
    int MaxStack;
    Potion *top;
};

void stack::InitStack(int max)
{
    int MaxStack = max;
    top = new Potion;
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
    if (GetCount() == MaxStack)
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

Potion *stack::pop()
{
    Potion *tmp(top);
    top = top->next;
    top->prev = nullptr;
    return tmp;
}

int stack::GetCount()
{
    int count = 0;
    Potion *tmp(top);
    while (tmp->next != nullptr) {
        count++;
        tmp = tmp->next;
    }
    if (tmp->GetType() != UNKNOWN)
        count++;
    return count;
}
