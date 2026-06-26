#ifndef COP3530_PROJECT_2_TREENODE_H
#define COP3530_PROJECT_2_TREENODE_H

#include "Recipe.h"
#include <string>
#include <vector>

// TreeNode to use in Splay tree and Red Black tree

using namespace std;

struct TreeNode {
    string key; // stores ingredient name
    vector<Recipe*> recipes;

    TreeNode* left;
    TreeNode* right;

    // constructors
    TreeNode() : left(nullptr), right(nullptr) {}
    TreeNode(string ingredient) : key(ingredient), left(nullptr), right(nullptr) {}


    // functions
    void addRecipe(Recipe* recipe) {
        recipes.push_back(recipe);
    }

    // destructor
    ~TreeNode() {
        // implement postorder traversal to delete the children recursively
    }
};


#endif