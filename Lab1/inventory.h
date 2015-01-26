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
#include <cstddef>

using namespace std;

char *StrToLower(char *string);

struct node {
    item    data;
    node    *next;
    node    *prev;
    int     qty;
    node();
    ~node();
};

node::node()
{
    next = nullptr;
    prev = nullptr;
    qty = 1;
}

node::~node()
{   
    data.deleteName();
    next = nullptr;
    prev = nullptr;
    qty = 0;
}

class inventory {
public:
    void AddItem(item newItem);
    void RemoveItem(char *name);
    bool SearchForMatch(char *searchStr, node *searchNode, node **match);
    bool SearchForAlphaLower(char *searchStr, node *searchNode, node **match);
    void PrintInventory();
    int GetCount();
    float GetWeight();
    void delNode(node *toDel);
    void delList(node *head);
    inventory();
    inventory(int UserMaxWeight);
    ~inventory();
private:
    node    *head;
    int     maxWeight;
    bool    headActive;
};

inventory::inventory()
{
    head = new node;
    headActive = false;
    maxWeight = 100;
}

/* Able to pass max weight through this constructor */
inventory::inventory(int userMaxWeight)
{
    head = new node;
    headActive = false;
    if (userMaxWeight > 0 && userMaxWeight < INT_MAX) {
        maxWeight = userMaxWeight;
    } else {
        cout << "error: weight not within bounds - defaulting to 100" << endl;
        maxWeight = 100;
    }
}

inventory::~inventory()
{
    node *traverse(head);
    while (traverse->next != nullptr) {
        traverse = traverse->next;
        delete traverse->prev;
        traverse->prev = nullptr;
    }
    delete traverse;
    traverse = nullptr;
    head = nullptr;
    headActive = false;
}

void inventory::PrintInventory()
{

    cout << endl << "Current inventory:" << endl;

    if (GetCount() > 0) {
        node *traverse(head); 
        while (traverse->next != nullptr) {
            cout << "\t[" << traverse->qty << "] ";
            cout << traverse->data.name << endl;
            traverse = traverse->next;
        }
        
        /* Printing last node */
        cout << "\t[" << traverse->qty << "] ";
        cout << traverse->data.name << endl;
    
        cout << "Total items: " << GetCount() << endl;
        cout << "Total weight: " << GetWeight() << endl << endl;
    } else {
        cout << "\t(no items)" << endl << endl;
    }
}

void inventory::AddItem(item newItem)
{
    if (!headActive) {
        head->data = newItem;
        headActive = true;
        cout << "You picked up a " << newItem.name << "." << endl;
    } else {
        if (GetWeight() + newItem.weight <= maxWeight) {
        
            char *lowerName = StrToLower(newItem.name);
            node *traverse(head);
            node *match;
            node **matchPtr = &match;

            /* If there's a match, we can just increment the qty */
            if (SearchForMatch(lowerName, traverse, matchPtr)) {
                if (newItem.weight == match->data.weight) {
                    match->qty++;
                    cout << "You picked up a " << newItem.name << "." << endl;
                } else {
                    cout << "ERROR: tried to add a duplicate item with wrong weight!" << endl;
                }
                newItem.deleteName();
            } else {
            
                /* No matches, so time to create a new node and insert it */
                node *newNode;
                newNode = new node;
                newNode->data = newItem;
                traverse = head; // Reset

                if (SearchForAlphaLower(lowerName, traverse, matchPtr)) {
                    if (match->prev == nullptr) { // newNode is lower than head, so insert as head
                        head->prev = newNode;
                        newNode->next = head;
                        head = newNode;
                        head->prev = nullptr;
                    } else {                      // Insert one position lower than traverse
                        newNode->prev = match->prev;
                        newNode->next = match;
                        match->prev->next = newNode;
                        match->prev = newNode;
                    }
                } else {                          // newNode highest alphabetically, so insert at end of list
                    match->next = newNode;
                    newNode->prev = match;
                } 
                cout << "You picked up a " << newItem.name << "." << endl;
                newNode = nullptr;
            }
            match = nullptr;
            traverse = nullptr;
            delete [] lowerName;
            lowerName = nullptr;
        } else {
            cout << "You're not strong enough to pick up the " << newItem.name << " with everything else you're carrying." << endl;
            delete [] newItem.name;
        }
    }
}

void inventory::RemoveItem(char *name)
{
    node *traverse(head);
    node *match;
    node **matchPtr = &match;
    char *lowerName = StrToLower(name);

    if (SearchForMatch(lowerName, traverse, matchPtr)) {
        if (match->qty > 1) { // Can simply decrement the quantity
            match->qty--;
        } else {
            match->data.deleteName();
            if (match == head) {
                if (head->next == nullptr) {
                    headActive = false;          // Head is the only one, so delete its data       
                } else {                         // Head is not the only one.
                    head = traverse->next;
                    head->prev = nullptr;
                    delete match;
                    match = nullptr;
                }
            } else if (match->next == nullptr) { // match is the last node
                match->prev->next = nullptr;
                delete match;
                match = nullptr;
            } else {                             // match is not the first or last node
                match->next->prev = match->prev;
                match->prev->next = match->next;
                delete match;
                match = nullptr;
            }
            matchPtr = nullptr;
            traverse = nullptr;
        }
        cout << "You dropped a " << name << "." << endl;
    } else {
        cout << "You don't have a " << name << " in your inventory." << endl;
    }
    delete [] lowerName;
    lowerName = nullptr;
}

bool inventory::SearchForMatch(char *searchStr, node *searchNode, node **matchPtr)
{
    if (strcmp(searchStr, searchNode->data.name) == 0) {
        *matchPtr = searchNode;
        return true;
    } else {
        if (searchNode->next == nullptr) {
            *matchPtr = searchNode;
            return false;
        } else {
            searchNode = searchNode->next;
            SearchForMatch(searchStr, searchNode, matchPtr);
        }
    }
}

bool inventory::SearchForAlphaLower(char *searchStr, node *searchNode, node **matchPtr)
{
    if (strcmp(searchStr, searchNode->data.name) < 0) {
        *matchPtr = searchNode;
        return true;
    } else {
        if (searchNode->next == nullptr) {
            return false;
        } else {
            searchNode = searchNode->next;
            SearchForAlphaLower(searchStr, searchNode, matchPtr);
        }
    }
}

/* Outputs traverse number of items in the inventory */
int inventory::GetCount()
{
    int sum = 0;
    node *traverse(head);
    if (headActive) {
        while (traverse->next != nullptr) {
            sum = sum + traverse->qty;
            traverse = traverse->next;
        }
        sum = sum + traverse->qty;
    }
    return sum;
}

/* Outputs current sum weight of all items in the inventory */
float inventory::GetWeight()
{
    float sum = 0;
    if (headActive) {
        node *traverse(head);
        while (traverse->next != nullptr) {
            sum = sum + traverse->data.weight * traverse->qty;
            traverse = traverse->next;
        }
        sum = sum + traverse->data.weight * traverse->qty; // Getting the last entry
    }
    return sum;
}

/* Converts string to all lowercase characters */
char *StrToLower(char *string)
{
    int length = strlen(string);
    char *lowerString;
    lowerString = new char[length + 1];
    int i;
    for (i = 0; i < length; i++)
        lowerString[i] = tolower(string[i]);
    return lowerString;
} 
