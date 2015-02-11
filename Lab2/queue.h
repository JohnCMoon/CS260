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
    bool isEmptyQueue();
    bool isFullQueue();
    bool AddPotion(Potion *newPotion);
    PotionType RemPotion();
    int GetCount();
    void SetLimit(int limit);
    queue();
    queue(const queue &newQueue);
    queue &operator = (const queue &newQueue);
    ~queue();
private:
    int maxQueue;
    Potion *front;
    Potion *back;
};

queue::queue()
{
    front = new Potion;
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

queue &queue::operator = (const queue &otherQueue)
{
    maxQueue = otherQueue.maxQueue;
    front = new Potion;
    *front = *otherQueue.front;
    back = new Potion;
    *back = *otherQueue.back;
    return *this;
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
            front->SetNext(nullptr);
            front->SetPrev(nullptr);
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
        delete front; // Removing last one in queue, so delete and realloc
        front = new Potion;
        back = front;
    } else {
        front = front->GetNext();
        delete front->GetPrev();
        front->SetPrev(nullptr);
    }
    return type;
}

void queue::SetLimit(int limit)
{
    maxQueue = limit;
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
