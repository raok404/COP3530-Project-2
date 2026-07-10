#ifndef PROJECT2_REDBLACKTREE_H
#define PROJECT2_REDBLACKTREE_H
#include <string>
#include <vector>
#include "Recipe.h"
#include "RedBlackTreeNode.h"
using namespace std;

class RedBlackTree {
    RedBlackTreeNode* root;

    RedBlackTreeNode* insertHelper(RedBlackTreeNode* current, string ingredient, vector<Recipe> r) {
        if (current==nullptr) {
            current=new RedBlackTreeNode(ingredient, nullptr, r);
            current->c=RedBlackTreeNode::Color::red;
            return current;
        }
        else if (ingredient<current->k) {
            if (current->left==nullptr) {
                current->left=new RedBlackTreeNode(ingredient, current, r);
                current->left->c=RedBlackTreeNode::Color::red;
                return current->left;
            }
            else {
                return insertHelper(current->left, ingredient, r);
            }
        }
        else if (ingredient==current->k) {
            for (int i=0; i<r.size(); i++) {
                current->recipe.push_back(r[i]);
            }
            return current;
        }
        else {
            if (current->right==nullptr) {
                current->right=new RedBlackTreeNode(ingredient, current, r);
                current->right->c=RedBlackTreeNode::Color::red;
                return current->right;
            }
            else {
                return insertHelper(current->right, ingredient, r);
            }
        }
    }

    RedBlackTreeNode* searchHelper(string ingredient, RedBlackTreeNode* current, RedBlackTreeNode* a) {
        if (current==nullptr) {
            return a;
        }
        else if (ingredient<current->k) {
            return searchHelper(ingredient, current->left, current);
        }
        else if (ingredient==current->k) {
            return current;
        }
        else {
            return searchHelper(ingredient, current->right, current);
        }
    }

    RedBlackTreeNode* leftRotation(RedBlackTreeNode* current) {
        RedBlackTreeNode* temp=current->parent;
        RedBlackTreeNode* newR=current->right;
        current->right=newR->left;
        if (newR->left!=nullptr) {
            newR->left->parent=current;
        }
        newR->left=current;
        current->parent=newR;
        newR->parent=temp;
        if (temp!=nullptr) {
            if (newR->k<temp->k) {
                temp->left=newR;
            }
            else {
                temp->right=newR;
            }
        }
        return newR;
    }

    RedBlackTreeNode* rightRotation(RedBlackTreeNode* current) {
        RedBlackTreeNode* temp=current->parent;
        RedBlackTreeNode* newR=current->left;
        current->left=newR->right;
        if (newR->right!=nullptr) {
            newR->right->parent=current;
        }
        newR->right=current;
        current->parent=newR;
        newR->parent=temp;
        if (temp!=nullptr) {
            if (newR->k<temp->k) {
                temp->left=newR;
            }
            else {
                temp->right=newR;
            }
        }
        return newR;
    }

    void correctTree(RedBlackTreeNode* current) {
        while (current!=root && current->c==RedBlackTreeNode::Color::red && current->parent->c==RedBlackTreeNode::Color::red) {
            RedBlackTreeNode* parent=current->parent;
            RedBlackTreeNode* grandparent=parent->parent;
            if (parent==grandparent->left) {
                RedBlackTreeNode* uncle=grandparent->right;
                if (uncle!=nullptr && uncle->c==RedBlackTreeNode::Color::red) {
                    parent->c=RedBlackTreeNode::Color::black;
                    uncle->c=RedBlackTreeNode::Color::black;
                    grandparent->c=RedBlackTreeNode::Color::red;
                    current=grandparent;
                }
                else {
                    if (current==parent->right) {
                        current=parent;
                        leftRotation(current);
                        parent=current->parent;
                    }
                    rightRotation(grandparent);
                    parent->c=RedBlackTreeNode::Color::black;
                    grandparent->c=RedBlackTreeNode::Color::red;
                }
            }
            else {
                RedBlackTreeNode* uncle=grandparent->left;
                if (uncle!=nullptr && uncle->c==RedBlackTreeNode::Color::red) {
                    parent->c=RedBlackTreeNode::Color::black;
                    uncle->c=RedBlackTreeNode::Color::black;
                    grandparent->c=RedBlackTreeNode::Color::red;
                    current=grandparent;
                }
                else {
                    if (current==parent->left) {
                        current=parent;
                        rightRotation(current);
                        parent=current->parent;
                    }
                    leftRotation(grandparent);
                    parent->c=RedBlackTreeNode::Color::black;
                    grandparent->c=RedBlackTreeNode::Color::red;
                }
            }
        }
        root->c=RedBlackTreeNode::Color::black;
    }

    void printRBT(RedBlackTreeNode* root) {
        if (root==nullptr) {
            return;
        }
        else {
            printRBT(root->left);
            printRBT(root->right);
            root->printResult();
        }
    }

    void clear(RedBlackTreeNode* current) {
        if (current==nullptr) {
            return;
        }
        clear(current->left);
        clear(current->right);
        delete current;
    }

public:
    RedBlackTree() {
        root=nullptr;
    }

    RedBlackTree(RedBlackTreeNode* input) {
        root=input;
    }

    RedBlackTreeNode* insert(string ingredient, vector<Recipe> r) {
        if (root==nullptr) {
            root=new RedBlackTreeNode(ingredient, nullptr, r);
            root->c=RedBlackTreeNode::Color::black;
            return root;
        }
        else {
            RedBlackTreeNode* insertVal=insertHelper(root, ingredient, r);
            if (insertVal->c==RedBlackTreeNode::Color::red) {
                correctTree(insertVal);
            }
            while (root->parent != nullptr) {
                root=root->parent;
            }
            return insertVal;
        }
    }

    RedBlackTreeNode* search(string ingredient) {
        RedBlackTreeNode* temp=searchHelper(ingredient, root, nullptr);
        if (temp!=nullptr) {
            if (temp->k==ingredient) {
                return temp;
            }
        }
        return nullptr;
    }

    void printTree() {
        printRBT(root);
    }

    ~RedBlackTree() {
        clear(root);
    }
};


#endif //PROJECT2_REDBLACKTREE_H