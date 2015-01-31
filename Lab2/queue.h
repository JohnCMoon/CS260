class queue {
public:
    void InitQueue(int max);
    bool isEmptyQueue();
    bool isFullQueue();
    Potion *GetFront();
    Potion *GetBack();
    bool AddPotion(Potion *newPotion);
    Potion *RemPotion();
    int GetCount();
private:
    int MaxQueue;
    Potion *front;
    Potion *back;
};


void queue::InitQueue(int max)
{
    MaxQueue = max;
    front = new Potion;
    Potion *back(front);
}

bool queue::isEmptyQueue()
{
    if (GetCount() == 0)
        return true;
    else
        return false;
}

bool queue::isFullQueue()
{
    if (GetCount() == MaxQueue)
        return true;
    else
        return false;
}

Potion *queue::GetFront()
{
    return front;
}

Potion *queue::GetBack()
{
    return back;
}

bool queue::AddPotion(Potion *newPotion)
{
    if (!isFullQueue()) {
        if (isEmptyQueue()) {
            front = newPotion;
            back = newPotion;
        } else {
            back->next = newPotion;
            newPotion->prev = back;
            newPotion->next = nullptr;
            back = newPotion;
        }
        return true;
    } else {
        delete newPotion;
        newPotion = nullptr;
        return false;
    }
}

Potion *queue::RemPotion()
{
    Potion *tmp(front);
    front = front->next;
    front->prev == nullptr;
    return tmp;
}

int queue::GetCount()
{
    int count = 0;
    Potion *tmp(front);
    while (tmp->next != nullptr) {
        count++; 
        tmp = tmp->next;
    }
    if (tmp->GetType() != UNKNOWN)
        count++;
    return count;
}
