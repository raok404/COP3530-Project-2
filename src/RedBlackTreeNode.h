#ifndef PROJECT2_REDBLACKTREENODE_H
#define PROJECT2_REDBLACKTREENODE_H
#include <string>
#include <vector>
#include <iostream>
#include "Recipe.h"
using namespace std;

struct RedBlackTreeNode {
    enum class Color: int{red=0, black=1};
    string k;
    vector<Recipe> recipe;
    Color c;
    RedBlackTreeNode *parent;
    RedBlackTreeNode *left;
    RedBlackTreeNode *right;

    RedBlackTreeNode() {
        k="";
        c=Color::red;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }

    RedBlackTreeNode(string ingredient, RedBlackTreeNode* previousN, vector<Recipe> r) {
        k=ingredient;
        parent = previousN;
        left=nullptr;
        right=nullptr;
        recipe=r;
        c=Color::red;
    }

    void printResult() {
        cout<<"Key: "<<k<<" has "<<recipe.size()<<" recipes; ";
        cout<<"Parent: ";
        if (parent!=nullptr) {
            cout<<parent->k<<endl;
        }
        else {
            cout<<"nullptr (ROOT NODE)"<<endl;
        }
        if (left!=nullptr) {
            cout<<"\tLeft child: "<<left->k;
        }
        if (right!=nullptr) {
            cout<<"\tRight child: "<<right->k;
        }
        cout<<endl;
    }

};


#endif