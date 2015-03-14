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

#define MAX_CHILDREN 3

class Skill {
public:
    Skill();
    Skill(char *aName, char *aDesc, int aLevel, Skill *aParent);
    Skill(Skill &aSkill);
    ~Skill();
    const Skill &operator=(Skill &aSkill);
    void Display(std::ostream &obj);
    int GetHeight();
    int GetMax();
    void SetName(char *aName);
    char *GetName();
    void SetDesc(char *aDesc);
    char *GetDesc();
    void SetLevel(int level);
    int GetLevel();
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
    Skill **children;
};

/* Default constructor. Doesn't do much but set things to NULL. */
Skill::Skill()
{
    name = nullptr;
    desc = nullptr;
    level = 0;
    parent = nullptr;
    children = new Skill*[MAX_CHILDREN];
    for (int i = 0; i < MAX_CHILDREN; i++)
        children[i] = nullptr;
}

/* Full constructor. Passes with it parameters for every class variable. */
Skill::Skill(char *aName, char *aDesc, int aLevel, Skill *aParent)
{
    parent = aParent;

    int nameLen = strlen(aName);
    name = new char[nameLen + 1];
    strcpy(name, aName);

    int descLen = strlen(aDesc);
    desc = new char[descLen + 1];
    strcpy(desc, aDesc);

    level = aLevel;

    children = new Skill*[MAX_CHILDREN];
    for (int i = 0; i < MAX_CHILDREN; i++)
        children[i] = nullptr;
}

Skill::Skill(Skill &aSkill)
{
    parent = aSkill.GetParent();

    int nameLen = strlen(aSkill.GetName());
    name = new char[nameLen + 1];
    strcpy(name, aSkill.GetName());

    int descLen = strlen(aSkill.GetDesc());
    desc = new char[descLen + 1];
    strcpy(desc, aSkill.GetDesc());

    level = aSkill.GetLevel();
    
    children = new Skill*[MAX_CHILDREN];
    for (int i = 0; i < MAX_CHILDREN; i++)
        children[i] = aSkill.GetChild(i);
}

Skill::~Skill()
{
    delete [] name;
    delete [] desc;
    for (int i = 0; i < MAX_CHILDREN; i++)
        delete children[i];
    delete [] children;
}

const Skill &Skill::operator=(Skill &aSkill)
{
    if (this == &aSkill) {
        return *this;
    } else {
        delete [] name;
        delete [] desc;
        for (int i = 0; i < MAX_CHILDREN; i++)
            delete children[i];
        delete [] children;

        int length = strlen(aSkill.GetName());
        name = new char[length + 1];
        strcpy(name, aSkill.GetName());

        length = strlen(aSkill.GetDesc());
        desc = new char[length + 1];
        strcpy(name, aSkill.GetDesc());

        level = aSkill.GetLevel();

        children = new Skill*[MAX_CHILDREN];
        for (int i = 0; i < MAX_CHILDREN; i++)
            children[i] = aSkill.GetChild(i);
    }
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
    return MAX_CHILDREN;
}

/* Boolean for if a child node is available on this skill. */
bool Skill::ChildIsOpen()
{
    for (int i = 0; i < MAX_CHILDREN; i++) {
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

char *Skill::GetDesc()
{
    return desc;
}

void Skill::SetLevel(int aLevel)
{
    level = aLevel;
} 

int Skill::GetLevel()
{
    return level;
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
