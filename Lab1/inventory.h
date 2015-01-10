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
    item data;
    node *next;
    node *prev;
    int qty;
    node()
    {
        next = NULL;
        prev = NULL;   
    }
};

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
    int     CurrentWeight;
};

inventory::inventory()
{
    MaxWeight =     100;
    ItemCount =     0;
    CurrentWeight = 0;
}

/* Able to pass max weight through this constructor */
inventory::inventory(int UserMaxWeight)
{
    if (UserMaxWeight > 0 && UserMaxWeight < INT_MAX)
        MaxWeight = UserMaxWeight;
    ItemCount =     0;
    CurrentWeight = 0;
}

void inventory::PrintInventory()
{
    cout << "Current inventory:" << endl;

    if (ItemCount == 0)
        return;

    node *traverse;
    traverse = new node;
    traverse = head;
 
    while (traverse->link != NULL) {
        cout << "\t[" << traverse.qty << "] " 
        cout << traverse->data.name << endl;
        traverse = traverse->next;
    }
    cout << "\t[" << traverse.qty << "] " 
    cout << traverse->data.name << endl;

    cout << "Total items: " << GetCount() << endl;
    cout << "Total weight: " << GetWeight() << endl << endl;
}

void inventory::AddItem(item NewItem)
{
    if (NewItem.weight > MaxWeight - CurrentWeight) {
        cout << "error: item is too heavy.";
        return;
    }

    if (ItemCount == 0) {
        head->data      = NewItem;
        head.qty        = 1;
        ItemCount++; 
        CurrentWeight = head->data.weight;
    } else { 

        /* Check for matching node first */  
        char *LowerNewName = ToLower(NewItem.name);
        node *traverse;
        traverse = new node;
        traverse = head;
        while (traverse->next != NULL) {
            if (strcmp(LowerNewName, traverse->data.name) == 0) {
                traverse.qty++;
                ItemCount++;
                CurrentWeight = traverse->data.weight;
                return;
            } else {
                traverse->next->prev = traverse;
                traverse = traverse->next;
            }
        }
        /* One more check for the last entry */
        if (strcmp(LowerNewName, traverse->data.name) == 0) {
                traverse.qty++;
                ItemCount++;
                CurrentWeight = traverse->data.weight;
                return;
        }

        traverse = head; // Reset

        /* No existing item with that name, so time for a new node */
        node *NewNode;
        NewNode = new node;
        NewNode->data = NewItem;
        NewNode.qty = 1;

        /* Now to insert it alphabetically */
        while (traverse->next != NULL) {
            if (strcmp(NewNode->data.name, traverse->data.name) < 0) {
                if (traverse->prev == NULL) { // It's head
                    head->prev = NewNode;
                    NewNode->next = head;
                    head = NewNode;
                    ItemCount++;  
                    CurrentWeight = traverse->data.weight;
                }
                traverse->prev->next = NewNode;
                traverse->prev = NewNode;
                NewNode->next = traverse;
                ItemCount++;
                CurrentWeight = traverse->data.weight;
            } else {
                traverse->next->prev = traverse;
                traverse = traverse->next;
            }
        }
        if (strcmp(NewNode->data.name, traverse->data.name) < 0) {
            traverse->prev->next = NewNode;
            traverse->prev = NewNode;
            NewNode->next = traverse;
            ItemCount++;
            CurrentWeight = traverse->data.weight;
        } else {
            traverse->next = NewNode;
            NewNode->prev = traverse;
            NewNode->next = NULL;
            ItemCount++;
            CurrentWeight = traverse->data.weight;
        }
        delete traverse;       
}

void inventory::RemoveItem(char *name)
{
    cout << "Removing item " << name << endl;
    char *LowerName = ToLower(name);
    cout << "Lowercase item " << LowerName << endl; 
    /* Checks head for the matching name */
    if (strcmp(head->data.name, LowerName) == 0) {
        if (head->data.qty > 1) {
            head->data.qty--;
        } else {
            ItemCount--;
            delete &(head->data);
        }
    }
    
    /* If there's only one entry (already processed above) exit */
    if (head->link == NULL)
        return;
    
    /* Okay, now we can process all of the rest. */
    node *traverse;
    node *last;
    traverse = new node;
    last    = new node;
    traverse = head->link;
    last    = head;
    while (traverse->link != NULL) {
        if (strcmp(traverse->data.name, LowerName) == 0) {
            if (traverse->data.qty > 1) {
                traverse->data.qty--;
            } else {
                ItemCount--;
                last->link = traverse->link;
                delete traverse;
            }
            last    = traverse;
            traverse = traverse->link;
        }
    }
    
    /* Now for the last one */
    if (strcmp(traverse->data.name, LowerName) ==0) {
        if (traverse->data.qty > 1) {
            traverse->data.qty--;
        } else {
            ItemCount--;
            last->link = NULL;
            delete traverse;
        }
    }
    delete LowerName;
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
