#ifndef COP3530_PROJECT_2_TREENODE_H
#define COP3530_PROJECT_2_TREENODE_H

#include "Recipe.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct SplayTreeNode {
    string key; // stores ingredient name
    vector<Recipe*> recipes;

    SplayTreeNode* parent;

    SplayTreeNode* left;
    SplayTreeNode* right;

    // constructors
    SplayTreeNode() : left(nullptr), right(nullptr), parent(nullptr) {}
    SplayTreeNode(string ingredient, SplayTreeNode* p) : key(ingredient), left(nullptr), right(nullptr), parent(p) {}
    SplayTreeNode(string ingredient, SplayTreeNode* p, SplayTreeNode* l, SplayTreeNode* r) : key(ingredient), left(l), right(r), parent(p) {}
    SplayTreeNode(string ingredient, vector<Recipe*> rec) : key(ingredient), left(nullptr), right(nullptr), recipes(rec) {}
    // functions
    void addRecipe(Recipe* recipe) {
        recipes.push_back(recipe);
    }

    void updateParent(SplayTreeNode* newParent) {
        parent = newParent;
    }

    void printNode() {
        cout << "Parent: ";
        if (parent != nullptr) {
            cout << parent->key;
        }
        else {
            cout << "null";
        }
        cout << "; Key: " << key << " has " << recipes.size() << " recipes" << endl;
    }
};

#endif