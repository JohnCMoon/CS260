/*
 *
 * File: SkillTree.h
 *
 * Author: John Moon <john.moon1@pcc.edu>
 *
 * Purpose: Implements the skill tree class.
 *
 */

#include <iostream>
#include <cstring>
#include "Skill.h"

class SkillTree {
public:
    SkillTree();
    SkillTree(char *aName);
    SkillTree(SkillTree &aTree);
    ~SkillTree();
    const SkillTree &operator=(SkillTree &aTree);
    void AddSkill(char *skillName, char *desc, int level);
    bool AddSkill(char *skillName, char *desc, int level, char *parentName);
    Skill *FindSkill(char *name);
    void FindR(char *name, Skill *root, Skill **matchPtr);
    void Display(std::ostream &obj); 
    void DisplayR(std::ostream &obj, Skill *root);
    char *GetName();
    Skill *GetRoot();
private:
    char *name;
    Skill *root;
};

SkillTree::SkillTree()
{
    name = nullptr;
    root = new Skill;
}

SkillTree::SkillTree(char *aName)
{
    int length = strlen(aName);
    name = new char[length + 1];
    strcpy(name, aName);
    root = new Skill;
}

SkillTree::SkillTree(SkillTree &aTree)
{
    int length = strlen(aTree.GetName());
    name = new char[length + 1];
    strcpy(name, aTree.GetName());
    root = aTree.GetRoot();
}

SkillTree::~SkillTree()
{
    delete [] name;
    delete root;
}

const SkillTree &SkillTree::operator=(SkillTree &aTree)
{
    if (this == &aTree) {
        return *this;
    } else {
        delete [] name;
        delete root;
        
        int length = strlen(aTree.GetName());
        name = new char[length + 1];
        strcpy(name, aTree.GetName());
        
        root = new Skill;
        root = aTree.GetRoot();
    }
}

/* Adds a new root to the tree. If there was already a root, it becomes a child
   of this new root. */
void SkillTree::AddSkill(char *skillName, char *desc, int level)
{
    if (root->GetName() == nullptr) {
        root->SetName(skillName);
        root->SetDesc(desc);
        root->SetLevel(level);
    } else {
        Skill *newRoot = new Skill(skillName, desc, level, nullptr);
        root->SetParent(newRoot);
        newRoot->SetChild(0, root);
        root = newRoot;
    }
}

/* Adds a new skill to the tree under the passed parentName. Fails if parent is not found
   or if there is not child open. */   
bool SkillTree::AddSkill(char *skillName, char *desc, int level, char *parentName)
{
    Skill *parent = FindSkill(parentName);
    if (parent != nullptr) {
        if (parent->ChildIsOpen()) {
            Skill *newSkill = new Skill(skillName, desc, level, parent);
            for (int i = 0; i < parent->GetMax(); i++) {
                if (parent->GetChild(i) == nullptr) {
                    parent->SetChild(i, newSkill);
                    return true;
                }
            }
        }
    }
    return false; 
}
    
/* Recursively traverses the tree finding a skill with the given name.
   returns NULL if no such skill is found in the tree. */
Skill *SkillTree::FindSkill(char *name)
{
    Skill *match = nullptr;
    Skill **matchPtr = &match;
    FindR(name, root, matchPtr);
    return match;
}

void SkillTree::FindR(char *name, Skill *node, Skill **matchPtr)
{
    if (strcmp(node->GetName(), name) == 0) {
        *matchPtr = node;
    } else {
        for (int i = 0; i < root->GetMax(); i++) {
            if (node->GetChild(i) != nullptr) {
                FindR(name, node->GetChild(i), matchPtr);
                if (*matchPtr != nullptr)
                    return;
            }
        }
    }
}

/* Displays every skill in the tree using a recursive method. */
void SkillTree::Display(std::ostream &obj)
{
    obj << "Skill Tree: " << name << std::endl;
    Skill *traverse(root);
    if (traverse->GetName() == nullptr)
        obj << "  Empty" << std::endl;
    else    
        DisplayR(obj, root);
}

void SkillTree::DisplayR(std::ostream &obj, Skill *root)
{
    for (int i = 0; i <= root->GetHeight(); i++)
        obj << "  ";
    obj << "- ";
    root->Display(obj);
    obj << std::endl;
    for (int i = 0; i < root->GetMax(); i++) {
        if (root->GetChild(i) != nullptr) {
            DisplayR(obj, root->GetChild(i));
        }
    }
}

char *SkillTree::GetName()
{
    return name;
}

Skill *SkillTree::GetRoot()
{
    return root;
}
