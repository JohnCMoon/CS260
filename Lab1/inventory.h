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
    item    *data;
    node    *next;
    node    *prev;
    int     qty;
    node();
    ~node();
};

node::node()
{
    data = nullptr;
    next = nullptr;
    prev = nullptr;
    qty = 1;
}

node::~node()
{
    delete [] data->name;
    delete data;
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
    inventory();
    inventory(int UserMaxWeight);
    ~inventory();
private:
    node    *head;
    int     maxWeight;
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

inventory::~inventory()
{
    node *traverse(head);
    while (traverse->next != nullptr) {
        head = traverse->next;
        delete traverse;
        traverse = head;
        head->prev = nullptr;
    }
    delete head->data;
    head->data = nullptr;
    head->prev = nullptr;
}

void inventory::PrintInventory()
{

    cout << "Creating a new item." << endl;
    item *newItem;
    newItem = new item;
    cout << "Deleting the new item." << endl;
    delete newItem;
    newItem = nullptr;
    
    cout << endl << "Current inventory:" << endl;

    if (GetCount() > 0) {
        node *traverse(head); 
        while (traverse->next != nullptr) {
            cout << "\t[" << traverse->qty << "] ";
            cout << traverse->data->name << endl;
            traverse = traverse->next;
        }
        
        /* Printing last node */
        cout << "\t[" << traverse->qty << "] ";
        cout << traverse->data->name << endl;
    
        cout << "Total items: " << GetCount() << endl;
        cout << "Total weight: " << GetWeight() << endl << endl;
    } else {
        cout << "\t(no items)" << endl << endl;
    }
}

void inventory::AddItem(item newItem)
{
    /* Allocating own memory since newItem wasn't passed by ref */
    item *newItemP;
    newItemP = new item;
    *newItemP = newItem;    

    if (head->data == nullptr) {
        head->data = newItemP;
        cout << "You picked up a " << newItem.name << "." << endl;
    } else {
        if (GetWeight() + newItemP->weight <= maxWeight) {
        
            char *lowerName = StrToLower(newItem.name);
            node *traverse(head);
            node *match;
            node **matchPtr = &match;

            /* If there's a match, we can just increment the qty */
            if (SearchForMatch(lowerName, traverse, matchPtr)) {
                if (newItemP->weight == match->data->weight) {
                    match->qty++;
                    cout << "You picked up a " << newItem.name << "." << endl;
                } else {
                    cout << "ERROR: tried to add a duplicate item with wrong weight!" << endl;
                }
            } else {
            
                /* No matches, so time to create a new node and insert it */
                node *newNode;
                newNode = new node;
                newNode->data = newItemP;
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
            if (match->prev == nullptr) {        // match is head
                if (match->next == nullptr) {    //  --- Head is the only one, so  make a new node in its place
                    head = new node;
                } else {                         //  --- Head ain't the only one
                    match->next->prev = nullptr;
                    head = traverse->next;
                }
            } else if (match->next == nullptr) { // match is the last node
                match->prev->next = nullptr;
            } else {                             // match is not the first or last node
                match->next->prev = match->prev;
                match->prev->next = match->next;
            }
            delete match;
            match = nullptr;
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
    if (strcmp(searchStr, searchNode->data->name) == 0) {
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
    if (strcmp(searchStr, searchNode->data->name) < 0) {
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
    if (head->data != nullptr) {
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
    node *traverse(head);
    while (traverse->next != nullptr) {
        sum = sum + traverse->data->weight * traverse->qty;
        traverse = traverse->next;
    }
    if (traverse->data != nullptr)
        sum = sum + traverse->data->weight * traverse->qty; // Getting the last entry
    return sum;
}

/* Converts string to all lowercase characters */
char *StrToLower(char *string)
{
    int length = strlen(string);
    char *lowerString;
    lowerString = new char[length];
    int i;
    for (i = 0; i < length; i++)
        lowerString[i] = tolower(string[i]);
    return lowerString;
} 
