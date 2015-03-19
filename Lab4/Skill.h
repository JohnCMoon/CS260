/*
 *
 * File: Skill.h
 *
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Definitions and function prototypes for the skill class. 
 *          This class will be treated as a node class in the skill tree.
 *
 */

#define MAX_CHILDREN 3 /* Per assignment requirements. */
#include <iostream>
#include <cstring>

class Skill {
public:
    Skill();
    Skill(char *aName, char *aDesc, int aLevel, Skill *aParent);
    Skill(const Skill &aSkill);
    ~Skill();
    const Skill &operator=(const Skill &aSkill);
    friend std::ostream& operator<<(std::ostream& obj, const Skill &aSkill); 
    void Display(std::ostream &obj);
    int GetHeight();
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
    char *name;         // Name of the skill.
    char *desc;         // Description of the skill.
    int level;          // Requisite level to obtain skill.
    Skill *parent;      // Parent skill.
    Skill **children;   // Array of child skills.
};
