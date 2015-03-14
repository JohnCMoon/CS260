/*
 *
 * File: Skill.h
 *
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Impmlements the skill class. This class will be treated as a node
 *          class in the skill tree.
 *
 */

#define MAX_CHILDREN 3 /* Just to meet assignment requirements. Can be any int. */

class Skill {
public:
    Skill();
    Skill(char *aName, char *aDesc, int aLevel, Skill *aParent);
    ~Skill();
    void Display(std::ostream &obj);
    int GetHeight();
    int GetMax();
    void SetName(char *aName);
    char *GetName();
    void SetDesc(char *aDesc);
    void SetLevel(int level);
    void SetParent(Skill *aParent);
    Skill *GetParent();
    void SetChild(int index, Skill *child);
    Skill *GetChild(int index);
    bool ChildIsOpen();
private:
    char *name;
    char *desc;
    int level;
    Skill *parent;
    int maxChildren;
    Skill **children;
};

/* Default constructor. Doesn't do much but set things to NULL. */
Skill::Skill()
{
    name = nullptr;
    desc = nullptr;
    level = 0;
    parent = nullptr;
    maxChildren = MAX_CHILDREN;
    children = new Skill*[maxChildren];
    for (int i = 0; i < maxChildren; i++)
        children[i] = nullptr;
}

/* Full constructor. Passes with it parameters for every class variable. */
Skill::Skill(char *aName, char *aDesc, int aLevel, Skill *aParent)
{
    maxChildren = MAX_CHILDREN;
    parent = aParent;

    int nameLen = strlen(aName);
    name = new char[nameLen + 1];
    strcpy(name, aName);

    int descLen = strlen(aDesc);
    desc = new char[descLen + 1];
    strcpy(desc, aDesc);

    level = aLevel;

    children = new Skill*[maxChildren];
    for (int i = 0; i < maxChildren; i++)
        children[i] = nullptr;
}

/* Destructor. Deletes data on node and all its children. */
Skill::~Skill()
{
    delete [] name;
    delete [] desc;
    for (int i = 0; i < maxChildren; i++)
        delete children[i];
    delete [] children;
}

/* Displays skill information. */
void Skill::Display(std::ostream &obj)
{
    obj << name;
    obj << " -- " << desc;
    obj << " [Lvl: " << level;
    obj << "]";
}

/* Returns the skill's height on the overall tree. */
int Skill::GetHeight()
{
    int height = 0;
    Skill *traverse(parent);
    while (traverse != nullptr) {
        height++;
        traverse = traverse->parent;
    }
    return height;
}

int Skill::GetMax()
{
    return maxChildren;
}

/* Boolean for if a child node is available on this skill. */
bool Skill::ChildIsOpen()
{
    for (int i = 0; i < maxChildren; i++) {
        if (children[i] == nullptr)
            return true;
    }
    return false;
}

void Skill::SetName(char *aName)
{
    int length = strlen(aName);
    name = new char[length + 1];
    strcpy(name, aName);
}

char *Skill::GetName()
{
    return name;
}

void Skill::SetDesc(char *aDesc)
{
    int length = strlen(aDesc);
    desc = new char[length + 1];
    strcpy(desc, aDesc);
}

void Skill::SetLevel(int aLevel)
{
    level = aLevel;
} 

void Skill::SetParent(Skill *aParent)
{
    parent = aParent;
}

Skill *Skill::GetParent()
{
    return parent;
}

void Skill::SetChild(int index, Skill *child)
{
    children[index] = child;
}

Skill *Skill::GetChild(int index)
{
    return children[index];
}
