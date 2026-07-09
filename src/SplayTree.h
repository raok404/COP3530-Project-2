#ifndef COP3530_PROJECT_2_SPLAYTREE_H
#define COP3530_PROJECT_2_SPLAYTREE_H

#include <string>
#include <unordered_set>
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
        node = rotateLeft(node);
        return rotateLeft(node);
    }

    SplayTreeNode* rotateRightRight(SplayTreeNode* node) {
        node = rotateRight(node);
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
    SplayTreeNode* insertHelper(SplayTreeNode* root, string ingredient, Recipe recipe) {
        // this will return the inserted node
        if (root == nullptr) {
            root = new SplayTreeNode(ingredient, nullptr, {recipe});
            return root;
        }
        if (ingredient < root->key) {
            if (root->left == nullptr) {
                root->left = new SplayTreeNode(ingredient, root, {recipe});
                return root->left;
            }
            return insertHelper(root->left, ingredient, recipe);
        }
        else if (ingredient > root->key) {
            if (root->right == nullptr) {
                root->right = new SplayTreeNode(ingredient, root, {recipe});
                return root->right;
            }
            return insertHelper(root->right, ingredient, recipe);
        }
        else {
            root->addRecipe(recipe);
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

    // SplayTreeNode* partialSearchHelper(SplayTreeNode* node, SplayTreeNode* prevNode, string ingredient, vector<SplayTreeNode*> result) {
    //     if (node == nullptr) {
    //         return prevNode;
    //     }
    //     if (node->key) {
    //         return node;
    //     }
    //     else if (ingredient < node->key) {
    //         return searchHelper(node->left, node, ingredient);
    //     }
    //     else {
    //         return searchHelper(node->right, node, ingredient);
    //     }
    // }

    SplayTreeNode* removeHelper(SplayTreeNode* node, SplayTreeNode* prevNode, string ingredient) {
        if (node == nullptr) {
            return prevNode;
        }
        if (ingredient == node->key) {
            return removeNode(node);
        }
        else if (ingredient < node->key) {
            return removeHelper(node->left, node, ingredient);
        }
        else {
            return removeHelper(node->right, node, ingredient);
        }
    }

    SplayTreeNode* removeNode(SplayTreeNode* node) {
        // returns the node to splay up;

        // deleting node with 0 children: just delete the node, update parent's left/right to not point to it
        if (node->left == nullptr && node->right == nullptr) {
            SplayTreeNode* p = node->parent;
            p->unconnectChild(node);
            delete node;
            return p;
        }
        else if (node->left != nullptr && node->right != nullptr) {
            // deleting node with 2 children: find inorder successor and copy its data to the current node...
            // then delete the inorder successor BUT need to return inorder successor's parent
            SplayTreeNode* inorderSuccessor = findInorderSuccessor(node);
            node->key = inorderSuccessor->key;
            node->recipes = inorderSuccessor->recipes;

            return removeHelper(inorderSuccessor, inorderSuccessor->parent, inorderSuccessor->key);
        }
        else {
            // deleting node with 1 child: delete the node and connect the deleted's parent to the deleted's child (update child's parent too)
            SplayTreeNode* p = node->parent;
            if (node->left != nullptr) {
                SplayTreeNode* c = node->left;
                p->updateChild(c);
                c->updateParent(p);
                delete node;
                return p;
            }
            else {
                SplayTreeNode* c = node->right;
                p->updateChild(c);
                c->updateParent(p);
                delete node;
                return p;
            }
        }
    }

    SplayTreeNode* findInorderSuccessor(SplayTreeNode* node) {
        // only call on nodes with a right child
        SplayTreeNode* inorderSuccessor = node->right;
        while (inorderSuccessor->left != nullptr) {
            inorderSuccessor = inorderSuccessor->left;
        }

        return inorderSuccessor;
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

    void inorderTraversalHelper(SplayTreeNode* node, unordered_set<string>& ingredientList) {
        if (node == nullptr) {
            return;
        }
        inorderTraversalHelper(node->left, ingredientList);
        ingredientList.insert(node->key);
        inorderTraversalHelper(node->right, ingredientList);
    }

public:
    SplayTree() : root(nullptr) {}
    SplayTree(SplayTreeNode* r) : root(r) {}

    SplayTreeNode* getRoot() {
        return root;
    }

    // functions
    // will implement insert, delete, find, etc...

    SplayTreeNode* insert(string ingredient, Recipe recipe) {
        return splay(insertHelper(root, ingredient, recipe));
    }

    SplayTreeNode* search(string ingredient) {
        return splay(searchHelper(root, nullptr, ingredient));
    }

    // SplayTreeNode* partialSearchString(string ingredient) {
    //     return splay(partialSearchHelper())
    // }

    SplayTreeNode* remove(string ingredient) {
        return splay(removeHelper(root, nullptr, ingredient));
    }

    unordered_set<string> getIngredients() {
        unordered_set<string> ingredients;
        inorderTraversalHelper(root, ingredients);
        return ingredients;
    }

    void printTree() {
        printTree(root);
    }

    ~SplayTree() {
        destructorHelper(root);
    }
};

#endif