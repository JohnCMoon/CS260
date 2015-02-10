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
    queue(const queue &newQueue);
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
    front->SetNext(nullptr);
    front->SetPrev(nullptr);
    Potion *back(front);
}

queue::queue(const queue &newQueue)
{
    maxQueue = newQueue.maxQueue;
    front = new Potion;
    *front = *newQueue.front;
    back = new Potion;
    *back = *newQueue.back;
}

queue::~queue()
{
    Potion *tmp(front);
    while (tmp->GetNext() != nullptr) {
        tmp = tmp->GetNext();
        delete tmp->GetPrev();
        tmp->SetPrev(nullptr);
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
            front->SetNext(newPotion->GetNext());
            front->SetPrev(newPotion->GetPrev());
            back = front;
            delete newPotion;
            newPotion = nullptr;
        } else {
            back->SetNext(newPotion);
            newPotion->SetPrev(back);
            newPotion->SetNext(nullptr);
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
    if (front->GetNext() == nullptr) {
        delete front;
        InitQueue(maxQueue); // Removing last one in queue, so reinitialize
    } else {
        front = front->GetNext();
        delete front->GetPrev();
        front->SetPrev(nullptr);
    }
    return type;
}

int queue::GetCount()
{
    int count = 0;
    Potion *tmp(front);
    while (tmp->GetNext() != nullptr) {
        count++;
        tmp = tmp->GetNext();
    }
    if (tmp->GetType() != UNKNOWN) {
        count++;
    }
    return count; 
}
