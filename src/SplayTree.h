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
        SplayTreeNode* parentOfNode = node->parent;
        SplayTreeNode* newRoot = node->right;
        SplayTreeNode* temp = node;
        temp->updateParent(newRoot);

        temp->right = newRoot->left;
        if (temp->right != nullptr) {
            temp->right->updateParent(temp);
        }

        newRoot->left = temp;

        newRoot->updateParent(parentOfNode);
        if (parentOfNode != nullptr) {
            parentOfNode->updateChild(newRoot);
        }

        return newRoot;
        // for zig and zag, the calling function will need to make it root of the whole tree (since no grandparent)
    }

    SplayTreeNode* rotateRight(SplayTreeNode* node) {
        SplayTreeNode* parentOfNode = node->parent;
        SplayTreeNode* newRoot = node->left;
        SplayTreeNode* temp = node;
        temp->updateParent(newRoot);

        temp->left = newRoot->right;
        if (temp->left != nullptr) {
            temp->left->updateParent(temp);
        }

        newRoot->right = temp;

        newRoot->updateParent(parentOfNode);
        if (parentOfNode != nullptr) {
            parentOfNode->updateChild(newRoot);
        }
        return newRoot;
    }

    SplayTreeNode* rotateLeftLeft(SplayTreeNode* node) {
        node->right = rotateLeft(node->right);
        return rotateLeft(node);
    }

    SplayTreeNode* rotateRightRight(SplayTreeNode* node) {
        node->left = rotateRight(node->left);
        return rotateRight(node);
    }

    SplayTreeNode* rotateLeftRight(SplayTreeNode* node) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    SplayTreeNode* rotateRightLeft(SplayTreeNode* node) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    SplayTreeNode* splay(SplayTreeNode* node) {
        // call on node to move up
        if (node->parent == nullptr) { // base case
            root = node;
            return node;
        }
        if (node->parent->parent == nullptr) {
            if (node == node->parent->right) {
                root = rotateLeft(node->parent);
                return root;
            }
            else if (node == node->parent->left) {
                root = rotateRight(node->parent);
                return root;
            }
        }
        else {
            // need to splay until it goes up to root recursively
            if (node->parent->parent->right != nullptr && node == node->parent->parent->right->right) {
                return splay(rotateLeftLeft(node->parent->parent));
            }
            else if (node->parent->parent->right != nullptr && node == node->parent->parent->right->left) {
                return splay(rotateRightLeft(node->parent->parent));
            }
            else if (node->parent->parent->left != nullptr && node == node->parent->parent->left->left) {
                return splay(rotateRightRight(node->parent->parent));
            }
            else {
                return splay(rotateLeftRight(node->parent->parent));
            }
        }
    }

    // helper methods for other stuff: insert, remove, search
    SplayTreeNode* insertHelper(SplayTreeNode* root, string ingredient, vector<Recipe*> recipes) {
        // this will return the inserted node
        if (ingredient < root->key) {
            if (root->left == nullptr) {
                root->left = new SplayTreeNode(ingredient, root,recipes);
                return root->left;
            }
            return insertHelper(root->left, ingredient, recipes);
        }
        else if (ingredient > root->key) {
            if (root->right == nullptr) {
                root->right = new SplayTreeNode(ingredient, root, recipes);
                return root->right;
            }
            return insertHelper(root->right, ingredient, recipes);
        }
        else {
            // for duplicate key, just return it
            return root;
        }
    }

    SplayTreeNode* searchHelper(SplayTreeNode* node, SplayTreeNode* prevNode, string ingredient) {
        if (node == nullptr) {
            return prevNode;
        }
        if (ingredient == node->key) {
            return node;
        }
        else if (ingredient < node->key) {
            return searchHelper(node->left, node, ingredient);
        }
        else {
            return searchHelper(node->right, node, ingredient);
        }
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

    SplayTreeNode* insert(string ingredient, vector<Recipe*> recipes) {
        return splay(insertHelper(root, ingredient, recipes));
    }

    SplayTreeNode* search(string ingredient) {
        return splay(searchHelper(root, nullptr, ingredient));
    }

    void printTree() {
        printTree(root);
    }

    ~SplayTree() {
        destructorHelper(root);
    }
};

#endif