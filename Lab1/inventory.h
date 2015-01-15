/*
 * File: inventory.h
 *
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Provides the inventory class. Implemented as a linked list that
 *          contains nodes of the "item" class. 
 *
 */

#include <cctype>
#include <cstring>
#include <climits>

using namespace std;

char *ToLower(char *string);

struct node {
    item    data;
    node    *next;
    node    *prev;
    int     qty;
    node();
    node(*Cnode);
};

node::node()
{
    next=NULL;
    prev=NULL;
}

class inventory {
public:
    void AddItem(item NewItem);
    void RemoveItem(char *name);
    void PrintInventory();
    int GetCount();
    int GetWeight();
    inventory();
    inventory(int UserMaxWeight);
private:
    node    *head;
    int     MaxWeight;
    int     ItemCount;
    float     CurrentWeight;
};

inventory::inventory()
{
    head = new node;
    MaxWeight = 100;
    ItemCount = 0;
    CurrentWeight = 0;
}

/* Able to pass max weight through this constructor */
inventory::inventory(int UserMaxWeight)
{
    if (UserMaxWeight > 0 && UserMaxWeight < INT_MAX) {
        MaxWeight = UserMaxWeight;
    } else {
        cout << "error: weight not within bounds - defaulting to 100" << endl;
        MaxWeight = 100;
    }
    ItemCount = 0;
    CurrentWeight = 0;
}

void inventory::PrintInventory()
{
    cout << "Current inventory:" << endl;

    if (ItemCount > 0) {
        node *traverse(head);
     
        while (traverse->next != NULL) {
            cout << "\t[" << traverse->qty << "] ";
            cout << traverse->data.name << endl;
            traverse = traverse->next;
        }
        
        /* Printing last node */
        cout << "\t[" << traverse->qty << "] ";
        cout << traverse->data.name << endl;
    }

    cout << "Total items: " << GetCount() << endl;
    cout << "Total weight: " << GetWeight() << endl << endl;
}

void inventory::AddItem(item NewItem)
{ 
    if (NewItem.weight <= MaxWeight - CurrentWeight) {
       
        ItemCount++;
        CurrentWeight = CurrentWeight + NewItem.weight; 

        if (ItemCount - 1 == 0) { // No list exists, assign to head
            head->data = NewItem;
            head->qty++;
        } else { 

            /* One or more items already in list */
            /* Check for matching node first, then we can just increment qty */  
            char *LowerNewName = ToLower(NewItem.name);
            node *traverse(head);
            while (traverse->next != NULL) {
                if (strcmp(LowerNewName, traverse->data.name) == 0) {
                    traverse->qty++;
                    return;
                } else {
                    traverse->next->prev = traverse;
                    traverse = traverse->next;
                }
            }
            /* One more check on the last entry */
            if (strcmp(LowerNewName, traverse->data.name) == 0) {
                    traverse->qty++;
                    return;
            }

            /* Bummer, no existing item with that name, so time for a new node */
            traverse = head; // Reset
            node *NewNode;
            NewNode = new node;
            NewNode->data = NewItem;
            NewNode->qty = 1;

            /* Now we must traverse the list again to find where to insert the node (alphabetically) */
            while (traverse->next != NULL) {
                if (strcmp(NewNode->data.name, traverse->data.name) < 0) { // It's alphabetically lower
                    if (traverse->prev == NULL) { // It's head
                        head->prev = NewNode;
                        NewNode->next = head;
                        head = NewNode;
                        return;
                    } else {
                        traverse->prev->next = NewNode;
                        traverse->prev = NewNode;
                        NewNode->next = traverse;
                        return;
                    }
                } else {
                    traverse->next->prev = traverse;
                    traverse = traverse->next;
                }
            }
            /* Again, a check on the last entry */
            if (strcmp(NewNode->data.name, traverse->data.name) < 0) {
                if (traverse->prev == NULL) { // It's head 
                    NewNode->next = head;
                    NewNode->prev = NULL;
                    head->next = NULL;
                    head = NewNode;
                } else {
                    traverse->prev->next = NewNode;
                    traverse->prev = NewNode;
                    NewNode->next = traverse;
                }
                return;
            }
            /* The new node isn't alphabetically lower than anything, so it should be placed last */
            else {
                traverse->next = NewNode;
                NewNode->prev = traverse;
                NewNode->next = NULL;
            }
        } 
    } else { // Too heavy to pick up
        cout << "You're not strong enough to pick up the " << NewItem.name << " with everything else you're carrying." << endl;
    }
    return;
}

void inventory::RemoveItem(char *name)
{
    char *LowerName = ToLower(name);

    if (ItemCount > 0) {
        ItemCount--;
        
        /* Traverse the list looking for node with the same name */
        node *traverse(head);

        while (traverse->next != NULL) {
            if (strcmp(LowerName, traverse->data.name) == 0) { // Found a match
                if (traverse->qty > 1) { // If there's more than one, just decrement
                    traverse->qty--;
                } else { // If there's just one, remove the node
                    if (traverse->prev == NULL) { // It's head
                        traverse->next->prev = NULL;
                        head = traverse->next;
                    } else if (traverse->next == NULL) { // It's tail
                        traverse->prev->next = NULL;
                    } else {
                        traverse->prev->next = traverse->next;
                        traverse->next->prev = traverse->prev;
                    }
                }
                CurrentWeight = CurrentWeight - traverse->data.weight;
                cout << "You dropped a " << traverse->data.name << "." << endl;
                delete traverse;
                traverse = NULL;
                return;
            }
            traverse = traverse->next;
        }
        
        /* Now for the last one */
        if (strcmp(LowerName, traverse->data.name) == 0) { // Found a match
            if (traverse->qty > 1) { // If there's more than one, just decrement
                traverse->qty--;
            } else { // If there's just one, remove the last node
                traverse->prev->next = NULL;
            }
            CurrentWeight = CurrentWeight - traverse->data.weight;
            cout << "You dropped a " << traverse->data.name << "." << endl;
            delete traverse;
            traverse = NULL;
            return;
        }
        /* Couldn't find the item anywhere in the list */
        cout << "You don't have a " << LowerName << " in your inventory." << endl;
    } else {
    /* Empty inventory */
    cout << "You don't have a " << LowerName << " in your inventory." << endl;
    }
}

/* Outputs traverse number of items in the inventory */
int inventory::GetCount()
{
    return ItemCount;
}

/* Outputs current sum weight of all items in the inventory */
int inventory::GetWeight()
{
    return CurrentWeight;
}

/* Converts string to all lowercase characters */
char *ToLower(char *string)
{
    int length = strlen(string);
    char *LowerString;
    LowerString = new char[length];
    int i;
    for (i = 0; i < length; i++)
        LowerString[i] = tolower(string[i]);    
    return LowerString;
}  
