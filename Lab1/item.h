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
    char *name;
    double weight;
    item();
};

item::item(char *aName, double aWeight)
{
    int length = strlen(aName);
    name = new char[length + 1];
    strcpy(name, aName);
    weight = aWeight;
}

item::item()
{
    weight = 0;
    name = NULL;
}
