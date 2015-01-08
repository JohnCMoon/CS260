/*
 * 
 *  File: item.h
 *
 *  Author: John Moon <john.moon1@pcc.edu>
 *
 *  Purpose: Defines the item class and all the functions/vars that go with it.
 *
 */

#include <cstring>

class item {
public:
    item(char *name, double weight);
    item();
    char *name;
    double weight;
    int qty;
};

item::item(char *aName, double aWeight)
{
    strcpy(name, aName);
    weight = weight;
}

item::item()
{
    weight = 0;
    qty = 1;
}
