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
    node *link;
    node()
    {
        link = NULL;   
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
    if (ItemCount == 0)
        return;

    node *current;
    current = new node;
    current = head;
    cout << current->data.name << endl;
    
    while (current->link != NULL) {
        cout << "Item: " << current->data.name << endl;
        cout << "Weight: " << current->data.weight << endl << endl;
        current = current->link;
    }
    cout << "Item: " << current->data.name << endl;
    cout << "Weight: " << current->data.weight << endl << endl;
}

void inventory::AddItem(item NewItem)
{
    node *current;
    current = new node;
    current = head;
    char *LowerNewItem = ToLower(NewItem);
    if (strcmp(LowerNewItem, current->data.name) <= 0)
       /* Here inserting aplhabetically gets tricky.... */ 
    ItemCount++;    
    return;
}

void inventory::RemoveItem(char *name)
{
    char *LowerName = ToLower(name);
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
    node *current;
    node *last;
    current = new node;
    last    = new node;
    current = head->link;
    last    = head;
    while (current->link != NULL) {
        if (strcmp(current->data.name, LowerName) == 0) {
            if (current->data.qty > 1) {
                current->data.qty--;
            } else {
                ItemCount--;
                last->link = current->link;
                delete current;
            }
            last    = current;
            current = current->link;
        }
    }
    
    /* Now for the last one */
    if (strcmp(current->data.name, LowerName) ==0) {
        if (current->data.qty > 1) {
            current->data.qty--;
        } else {
            ItemCount--;
            last->link = NULL;
            delete current;
        }
    }
    delete LowerName;
}

/* Outputs current number of items in the inventory */
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
    cout << "Made it to the ToLower function!" << endl;
    int length = strlen(string);
    char *LowerString;
    LowerString = new char[length];
    int i;
    for (i = 0; i < length; i++)
        LowerString[i] = tolower(string[i]);    
    return LowerString;
}   
