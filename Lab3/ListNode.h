/*
 *
 * Filename: ListNode.h
 *
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Implements the node class for the linked lists attached to each
 *          table index.
 *
 */

class ListNode {
public:
    ListNode();
    ListNode *GetNext();
    void SetNext(ListNode *node);
private:
    Player player;
    ListNode *next;
};

ListNode::ListNode()
{
    next = nullptr;
}
    
ListNode *ListNode::GetNext()
{
    return next;
}

void ListNode::SetNext(ListNode *node)
{
    next = node;
}
