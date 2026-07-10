#include "SplayTree.h"
#include "RedBlackTree.h"
#include <iostream>
#include <nlohmann/json.hpp>
int main() {

    // example for how to read in the data and put it in tree

    // read in json
    RecipeBook book = RecipeBook("../datasets/normalized_recipes.json");
    cout << "Read in " << book.getNumRecipes() << " different recipes" << endl;

    // put every recipe into the trees, using its ingredient as the key
    RedBlackTree rb = RedBlackTree();
    SplayTree splay;
    for (Recipe recipe : book.recipes) {
        for (string ingredient : recipe.ingredientList) {
            splay.insert(ingredient, recipe);
            rb.insert(ingredient, recipe);
        }
    }

    // search splay tree and rb tree for any recipe that uses chicken
    SplayTreeNode* test = splay.search("chicken");
    if (test != nullptr) {
        cout << test->recipes.size() << endl; // there's 2628 recipes that use "chicken" as an ingredient
    }

    RedBlackTreeNode* test2 = rb.search("chicken");
    if (test2 != nullptr) {
        cout << test2->recipe.size() << endl;
    }

    return 0;
}