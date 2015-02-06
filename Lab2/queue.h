/*
 * File: queue.h
 *
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Implements the queue ADT.
 *
 */

class queue {
public:
    void InitQueue(int max);
    bool isEmptyQueue();
    bool isFullQueue();
    bool AddPotion(Potion *newPotion);
    PotionType RemPotion();
    int GetCount();
    ~queue();
private:
    int maxQueue;
    Potion *front;
    Potion *back;
};


void queue::InitQueue(int max)
{
    maxQueue = max;
    front = new Potion;
    front->next = nullptr;
    front->prev = nullptr;
    Potion *back(front);
}

queue::~queue()
{
    Potion *tmp(front);
    while (tmp->next != nullptr) {
        tmp = tmp->next;
        delete tmp->prev;
        tmp->prev = nullptr;
    }
    delete tmp;
    tmp = nullptr;
    front = nullptr;
    back = nullptr;
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
    if (GetCount() == maxQueue)
        return true;
    else
        return false;
}

bool queue::AddPotion(Potion *newPotion)
{
    if (!isFullQueue()) {
        if (isEmptyQueue()) {
            front->SetType(newPotion->GetType());
            front->next = newPotion->next;
            front->prev = newPotion->prev;
            back = front;
            delete newPotion;
            newPotion = nullptr;
        } else {
            back->next = newPotion;
            newPotion->prev = back;
            newPotion->next = nullptr;
            back = newPotion;
        }
        return true;
    } else {
        return false;
    }
}

PotionType queue::RemPotion()
{
    PotionType type = front->GetType();
    if (front->next == nullptr) {
        delete front;
        InitQueue(maxQueue); // Removing last one in queue, so reinitialize
    } else {
        front = front->next;
        delete front->prev;
        front->prev = nullptr;
    }
    return type;
}

int queue::GetCount()
{
    int count = 0;
    Potion *tmp(front);
    while (tmp->next != nullptr) {
        count++;
        tmp = tmp->next;
    }
    if (tmp->GetType() != UNKNOWN) {
        count++;
    }
    return count; 
}
