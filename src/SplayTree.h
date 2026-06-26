#ifndef COP3530_PROJECT_2_SPLAYTREE_H
#define COP3530_PROJECT_2_SPLAYTREE_H

#include <string>
#include "Recipe.h"
#include "TreeNode.h"

using namespace std;

class SplayTree {
    TreeNode* root;

public:
    SplayTree() : root(nullptr) {}

    // functions
    // will implement insert, delete, find, etc...

    ~SplayTree() {
        delete root;
    }
};

#endif