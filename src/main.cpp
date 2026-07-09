#include "SplayTree.h"
#include <iostream>
#include <nlohmann/json.hpp>
int main() {

    // example for how to read in the data and put it in tree

    // read in json
     RecipeBook book = RecipeBook("../datasets/normalized_recipes.json");
     cout << "Read in " << book.getNumRecipes() << " different recipes" << endl;

    // put every recipe into the tree, using its ingredient as the key
     SplayTree tree;
     for (Recipe recipe : book.recipes) {
         for (string ingredient : recipe.ingredientList) {
             tree.insert(ingredient, recipe);
         }
     }

    // search for any recipe that uses chicken
     SplayTreeNode* test = tree.search("chicken");
     if (test != nullptr) {
         cout << test->recipes.size() << endl; // there's 2628 recipes that use "chicken" as an ingredient
     }

     return 0;
}