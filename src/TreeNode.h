#ifndef COP3530_PROJECT_2_TREENODE_H
#define COP3530_PROJECT_2_TREENODE_H

#include "Recipe.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct SplayTreeNode {
    string key; // stores ingredient name
    vector<Recipe> recipes;

    SplayTreeNode* parent;

    SplayTreeNode* left;
    SplayTreeNode* right;

    // constructors
    SplayTreeNode() : left(nullptr), right(nullptr), parent(nullptr) {}
    SplayTreeNode(string ingredient, SplayTreeNode* p) : key(ingredient), left(nullptr), right(nullptr), parent(p) {}
    SplayTreeNode(string ingredient, SplayTreeNode* p, SplayTreeNode* l, SplayTreeNode* r) : key(ingredient), left(l), right(r), parent(p) {}
    SplayTreeNode(string ingredient, vector<Recipe> rec) : key(ingredient), left(nullptr), right(nullptr), recipes(rec) {}
    SplayTreeNode(string ingredient, SplayTreeNode* p, vector<Recipe> rec) : key(ingredient), parent(p), recipes(rec), left(nullptr), right(nullptr) {}
    // functions
    void addRecipe(Recipe recipe) {
        recipes.push_back(recipe);
    }

    void updateParent(SplayTreeNode* newParent) {
        parent = newParent;
    }

    void updateChild(SplayTreeNode* newChild) {
        if (newChild == nullptr) {
            return;
        }
        if (newChild->key < key) {
            left = newChild;
        }
        else {
            right = newChild;
        }
    }

    void unconnectChild(SplayTreeNode* childToUnconnect) {
        if (left == childToUnconnect) {
            left = nullptr;
        }
        else if (right == childToUnconnect) {
            right = nullptr;
        }
    }

    void printNode() {
        cout << "Key: " << key << " has " << recipes.size() << " recipes; ";
        cout << "Parent: ";
        if (parent != nullptr) {
            cout << parent->key << endl;
        }
        else {
            cout << "nullptr (ROOT NODE)" << endl;
        }
        if (left != nullptr) {
            cout << "\tLeft child: " << left->key;
        }
        if (right != nullptr) {
            cout << "\tRight child: " << right->key;
        }
        cout << endl;

    }
};

#endif