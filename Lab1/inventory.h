/*
 *
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

char *StrToLower(char *string);

struct node {
    item    *data;
    node    *next;
    node    *prev;
    int     qty;
    node();
};

node::node()
{
    data = new item;
    next = NULL;
    prev = NULL;
    qty = 1;
}

class inventory {
public:
    void AddItem(item newItem);
    void RemoveItem(char *name);
    bool SearchForMatch(char *searchStr, node *searchNode);
    bool SearchForAlphaLower(char *searchStr, node *searchNode);
    void PrintInventory();
    int GetCount();
    int GetWeight();
    inventory();
    inventory(int UserMaxWeight);
private:
    node        *head;
    int         maxWeight;
};

inventory::inventory()
{
    head = new node;
    maxWeight = 100;
}

/* Able to pass max weight through this constructor */
inventory::inventory(int userMaxWeight)
{
    head = new node;
    if (userMaxWeight > 0 && userMaxWeight < INT_MAX) {
        maxWeight = userMaxWeight;
    } else {
        cout << "error: weight not within bounds - defaulting to 100" << endl;
        maxWeight = 100;
    }
}

void inventory::PrintInventory()
{

    cout << "Current inventory:" << endl;

    if (GetCount() > 0) {
        node *traverse(head);
     
        while (traverse->next != NULL) {
            cout << "\t[" << traverse->qty << "] ";
            cout << traverse->data->name << endl;
            traverse = traverse->next;
        }
        
        /* Printing last node */
        cout << "\t[" << traverse->qty << "] ";
        cout << traverse->data->name << endl;
    } else {
        cout << "\t(no items)" << endl << endl;
    }

    cout << "Total items: " << GetCount() << endl;
    cout << "Total weight: " << GetWeight() << endl << endl;
}

void inventory::AddItem(item newItem)
{
    if (head->data == NULL) {
        head->data = &newItem;
    } else {

        node *traverse(head);
        char *lowerName = StrToLower(newItem.name);

        if (GetWeight() + newItem.weight <= maxWeight) {
        
            /* If there's a match, we can just increment the qty */
            if (SearchForMatch(lowerName, traverse)) {
                traverse->qty++;
            } else {
            
                /* No matches, so time to create a new node and insert it */
                node *newNode;
                newNode = new node;
                newNode->data = &newItem;
                traverse = head; // Reset
                
                if (SearchForAlphaLower(lowerName, traverse)) {
                    if (traverse->prev == NULL) { // Head is alphabetically lower, so insert as head
                        head->prev = newNode;
                        newNode->next = head;
                        head = newNode;
                    } else {                      // Insert somewhere in the middle of the list
                        newNode->prev = traverse->prev;
                        newNode->next = traverse;
                        traverse->prev->next = newNode;
                        traverse->prev = newNode;
                    }
                } else {                          // Nothing alphabetically lower, so insert at end of list
                    traverse->next = newNode;
                    newNode->prev = traverse;
                }
            }
            traverse = NULL;
        } else {
            cout << "You're not strong enough to pick up the " << newItem.name << " with everything else you're carrying." << endl;
        }
    }
}

void inventory::RemoveItem(char *name)
{
    node *traverse(head);
    char *lowerName = StrToLower(name);

    if (SearchForMatch(lowerName, traverse)) {
        if (traverse->qty > 1) { // Can simply decrement the quantity
            traverse->qty--;
        } else {
            if (traverse->prev == NULL) {        // Traverse is head
                if (traverse->next == NULL) {    //  --- Head is the only one, so  make a new node in its place
                    node *newHead;
                    newHead = new node;
                    head = newHead;
                } else {                         //  --- Head ain't the only one
                    traverse->next->prev = NULL;
                    head = traverse->next;
                }
            } else if (traverse->next == NULL) { // Traverse is the last node
                traverse->prev->next = NULL;
            } else {                             // Traverse is not the first or last node
                traverse->next->prev = traverse->prev;
                traverse->prev->next = traverse->next;
            }
            delete traverse;
            traverse = NULL;
        }
    }
}

bool inventory::SearchForMatch(char *searchStr, node *searchNode)
{
    if (strcmp(searchStr, searchNode->data->name) == 0) {
        return true;
    } else {
        if (searchNode->next == NULL) {
            return false;
        } else {
            searchNode = searchNode->next;
            SearchForMatch(searchStr, searchNode);
        }
    }
}

bool inventory::SearchForAlphaLower(char *searchStr, node *searchNode)
{
    if (strcmp(searchStr, searchNode->data->name) < 0) {
        return true;
    } else {
        if (searchNode->next == NULL) {
            return false;
        } else {
            searchNode = searchNode->next;
            SearchForAlphaLower(searchStr, searchNode);
        }
    }
}

/* Outputs traverse number of items in the inventory */
int inventory::GetCount()
{
    int sum = 0;
    node *traverse(head);
    while (traverse->next != NULL) {
        sum++;
        traverse = traverse->next;
    }
    if (traverse->data != NULL)
        sum++;
    return sum;
}

/* Outputs current sum weight of all items in the inventory */
int inventory::GetWeight()
{
    float sum = 0;
    node *traverse(head);
    while (traverse->next != NULL) {
        sum = sum + traverse->data->weight;
        traverse = traverse->next;
    }
    if (traverse->data != NULL)
        sum = sum + traverse->data->weight; // Getting the last entry
    return sum;
}

/* Converts string to all lowercase characters */
char *StrToLower(char *string)
{
    int length = strlen(string);
    char *LowerString;
    LowerString = new char[length];
    int i;
    for (i = 0; i < length; i++)
        LowerString[i] = tolower(string[i]);    
    return LowerString;
}  
