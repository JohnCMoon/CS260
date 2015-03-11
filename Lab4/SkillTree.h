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
    ~SkillTree();
    void AddSkill(char *name, char *desc, int level);
    bool AddSkill(char *name, char *desc, int level, char *parentName);
    Skill *FindSkill(char *name);
    Skill *FindR(char *name, Skill *root);
    void Display(std::ostream &obj); 
    void DisplayR(std::ostream &obj, Skill *root);
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

SkillTree::~SkillTree()
{
}

/* Adds a new root to the tree. If there was already a root, it becomes a child
   of this new root. */
void SkillTree::AddSkill(char *name, char *desc, int level)
{
    if (root->GetName() == nullptr) {
        std::cout << "About to set the name." << std::endl;
        root->SetName(name);
        std::cout << "About to set the desc." << std::endl;
        root->SetDesc(desc);
        root->SetLevel(level);
    } else {
        Skill *newRoot;
        newRoot = new Skill;
        newRoot->SetName(name);
        newRoot->SetDesc(desc);
        newRoot->SetLevel(level);
        root->SetParent(newRoot);
        newRoot->SetChild(0, root);
        root = newRoot;
    }
}

bool SkillTree::AddSkill(char *name, char *desc, int level, char *parentName)
{
    Skill *parent = FindSkill(parentName);
    if (parent != nullptr) {
        if (parent->ChildIsOpen()) {
            Skill *newSkill = new Skill;
            newSkill->SetName(name);
            newSkill->SetDesc(desc);
            newSkill->SetLevel(level);
            newSkill->SetParent(parent);
            int i;
            for (i = 0; i < parent->GetMax(); i++) {
                if (parent->GetChild(i) == nullptr)
                    parent->SetChild(i, newSkill);
            }
            return true;
        }
    }
    return false;        
}
    

Skill *SkillTree::FindSkill(char *name)
{
    return FindR(name, root);
}

Skill *SkillTree::FindR(char *name, Skill *root)
{
    if (strcmp(root->GetName(), name) == 0) {
        return root;
    } else {
        int i;
        for (i = 0; i < root->GetMax(); i++) {
            if (root->GetChild(i) != nullptr)
                FindR(name, root->GetChild(i));
        }
        return nullptr;
    }
}

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
    root->Display(obj);
    int i;
    for (i = 0; i < root->GetMax(); i++) {
        if (root->GetChild(i) != nullptr)
            DisplayR(obj, root->GetChild(i));
    }
}
