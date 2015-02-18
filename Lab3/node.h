/*
 *
 * Filename: node.h
 *
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Implements the node class which will encapsulate player data in
 *          the hash table. Each node should include a linked list that will
 *          handle any collision instances that are encountered.
 *
 */

class node {
public:
    node();
    node *GetNext();
    void SetNext(node *next);
    node *GetPrev();
    void SetPrev(node *prev);
    Player *GetPlayer();
    void SetPlayer(Player newPlayer);
private:
    node *next;
    node *prev;
    Player playerData;
};

node::node()
{
    next = nullptr;
    prev = nullptr;
} 

node *node::GetNext()
{
    return next;
}

void node::SetNext(node *newNext)
{
    next = newNext;
}

node *node::GetPrev()
{
    return prev;
}

void node::SetPrev(node *newPrev)
{
    prev = newPrev;
}

Player *node::GetPlayer()
{
    return &playerData;
}

void node::SetPlayer(Player newPlayer)
{
    playerData = newPlayer;
}   
