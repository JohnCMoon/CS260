/*
 *
 * File: SkillTree.h
 *
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Definitions and function prototypes for the skill tree class.
 *
 */

#include <ostream>
#include <cstring>
#include "Skill.h"

class SkillTree {
public:
    SkillTree();
    SkillTree(char *aName);
    SkillTree(const SkillTree &aTree);
    ~SkillTree();
    const SkillTree &operator=(const SkillTree &aTree);
    void AddSkill(char *skillName, char *desc, int level);
    bool AddSkill(char *skillName, char *desc, int level, char *parentName);
    Skill *FindSkill(char *name);
    void FindR(char *name, Skill *root, Skill **matchPtr);
    void Display(std::ostream &obj); 
    void DisplayR(std::ostream &obj, Skill *root);
    char *GetName();
    Skill *GetRoot();
private:
    char *name;     // Name of the tree.
    Skill *root;    // Root of the tree.
};
