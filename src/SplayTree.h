#ifndef COP3530_PROJECT_2_SPLAYTREE_H
#define COP3530_PROJECT_2_SPLAYTREE_H

#include <string>
#include "Recipe.h"
#include "TreeNode.h"

using namespace std;

class SplayTree {
    SplayTreeNode* root;

    SplayTreeNode* rotateLeft(SplayTreeNode* node) {
        // need to rotate AND update applicable parent nodes
        // call on the parent of the node you want to move up

        SplayTreeNode* newRoot = node->right;
        SplayTreeNode* temp = node;
        temp->updateParent(newRoot);

        temp->right = newRoot->left;
        if (temp->right != nullptr) {
            temp->right->updateParent(temp);
        }

        newRoot->left = temp;

        newRoot->updateParent(nullptr);

        root = newRoot;
        return root;
        // for zig and zag, they end up being the root of the whole tree (since no grandparent)
    }

    SplayTreeNode* rotateRight(SplayTreeNode* root) {

    }

    SplayTreeNode* rotateLeftLeft(SplayTreeNode* root) {}

    SplayTreeNode* rotateRightRight(SplayTreeNode* root) {}

    SplayTreeNode* rotateLeftRight(SplayTreeNode* root) {}

    SplayTreeNode* rotateRightLeft(SplayTreeNode* root) {}

    // helper methods for other stuff: insert, remove, search
    SplayTreeNode* insertHelper(SplayTreeNode* root, string ingredient, vector<Recipe*> recipes) {
        if (root == nullptr) {
            return new SplayTreeNode(ingredient, recipes);
        }
        if (ingredient < root->key) {
            root->left = insertHelper(root->left, ingredient, recipes);
            root->left->updateParent(root);
        }
        else {
            root->right = insertHelper(root->right, ingredient, recipes);
            root->right->updateParent(root);
        }

        root->updateParent(nullptr);
        return root;
        // this doesn't cover case where insert duplicate key, what to do then?
        // it just gets added again to right side currently...

        // need to add splaying after insert, as well...
    }

    void destructorHelper(SplayTreeNode* root) {
        if (root == nullptr) {
            return;
        }

        destructorHelper(root->left);
        destructorHelper(root->right);

        delete root;
        return;
    }

    void printTree(SplayTreeNode* root) {
        if (root == nullptr) {
            return;
        }
        else {
            printTree(root->left);
            printTree(root->right);
            root->printNode();
        }
    }

public:
    SplayTree() : root(nullptr) {}
    SplayTree(SplayTreeNode* r) : root(r) {}

    SplayTreeNode* getRoot() {
        return root;
    }

    // functions
    // will implement insert, delete, find, etc...
    // need splay()
    // which needs rotateLeft, rotateRight, rotateLeftRight, etc...
    SplayTreeNode* splay(SplayTreeNode* node) {
        // call on node to move up
        if (node->parent == nullptr) {
            return node;
        }
        if (node->parent->parent == nullptr) {
            if (node == node->parent->right) {
                return rotateLeft(node->parent);
            }
        }
    }

    SplayTreeNode* insert(string ingredient, vector<Recipe*> recipes) {
        root = insertHelper(root, ingredient, recipes);
        return root;
    }

    void printTree() {
        printTree(root);
    }

    ~SplayTree() {
        destructorHelper(root);
    }
};

#endif