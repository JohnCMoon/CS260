/*
 *
 * File: Skill.h
 *
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Impmlements the skill class. This class will be treated as a node
            class in the skill tree.
 *
 */

class Skill {
public:
    Skill();
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

Skill::Skill()
{
    name = nullptr;
    desc = nullptr;
    level = 0;
    parent = nullptr;
    maxChildren = 3;
    children = new Skill*[maxChildren];
    int i;
    for (i = 0; i < maxChildren; i++);
        children[i] = nullptr;
}

Skill::~Skill()
{
}

void Skill::Display(std::ostream &obj)
{
    std::cout << "Displaying skill: " << name << std::endl;
    int i;
    for (i = 0; i <= GetHeight(); i++)
        obj << "  ";
    obj << "- " << name;
    obj << " -- " << desc;
    obj << " [Lvl: " << level;
    obj << "]" << std::endl;
}

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

bool Skill::ChildIsOpen()
{
    int i;
    for (i = 0; i < maxChildren; i++) {
        if (children[i] == nullptr)
            return true;
    }
    return false;
}

void Skill::SetName(char *aName)
{
    std::cout << "Beginning to set name" << std::endl;
    int length = strlen(aName);
    std::cout << "Length of " << aName << " is " << length << std::endl;
    name = new char[length + 1];
    std::cout << "Mem allocated to name\n";
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
