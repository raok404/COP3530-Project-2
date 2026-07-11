#include "SplayTree.h"
#include "RedBlackTree.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <nlohmann/json.hpp>

void timeSplay(const RecipeBook &book, const vector <string> &ingredients);
void timeRedBlack(const RecipeBook &book, const vector <string> &ingredients);

int main() {

    // example for how to read in the data and put it in tree

    // read in json
    RecipeBook book = RecipeBook("../datasets/normalized_recipes.json");
    cout << "Read in " << book.getNumRecipes() << " different recipes" << endl;

    // put every recipe into the trees, using its ingredient as the key


    // search splay tree and rb tree for any recipe that uses chicken
    std::vector<std::string> ingredients = {
        "chicken", "chicken", "pork", "cabbage", "butter", "onion",
        "egg", "salt", "tomato", "pepper", "rice", "paper",
        "sugar", "wheat", "ribeye steak", "truffle", "truffle", "pepperoni",
        "meat", "coconut", "coconut water", "matcha", "coffee"
    };
    timeSplay(book, ingredients);
    timeRedBlack(book, ingredients);

    return 0;
}


void timeSplay(const RecipeBook &book, const vector <string> &ingredients) {
    auto start_time = std::chrono::steady_clock::now();
    SplayTree splay;
    for (const Recipe &recipe : book.recipes) {
        for (string ingredient : recipe.ingredientList) {
            splay.insert(ingredient, recipe);
        }
    }
    auto end_time = std::chrono::steady_clock::now();
    auto dur = end_time - start_time;
    auto milisec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

    cout << "Init time for split " << milisec << " ms" << endl;
    auto total = std::chrono::microseconds::zero();
    for (std::string str : ingredients) {
        start_time = std::chrono::steady_clock::now();
        SplayTreeNode* test = splay.search(str);
        end_time = std::chrono::steady_clock::now();
        dur = end_time - start_time;
        auto microsec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
        total += std::chrono::duration_cast<std::chrono::microseconds>(dur);
        cout << "Search time for " << str << " " << microsec << " us. Recipe size ";
        if (test != nullptr) {
            cout << test->recipes.size() << endl; // there's 2628 recipes that use "chicken" as an ingredient
        } else {
            cout << "0" << endl;
        }
    }
    cout << "Total search time " << total.count() << " us" << endl;

}

void timeRedBlack(const RecipeBook &book, const vector <string> &ingredients) {
    auto start_time = std::chrono::steady_clock::now();
    RedBlackTree rb = RedBlackTree();
    for (Recipe recipe : book.recipes) {
        for (string ingredient : recipe.ingredientList) {
            rb.insert(ingredient, recipe);
        }
    }
    auto end_time = std::chrono::steady_clock::now();
    auto dur = end_time - start_time;
    auto milisec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    cout << "Init time" << milisec << " ms" << endl;

    auto total = std::chrono::microseconds::zero();
    for (std::string str : ingredients) {
        start_time = std::chrono::steady_clock::now();
        RedBlackTreeNode* test2 = rb.search(str);
        end_time = std::chrono::steady_clock::now();
        dur = end_time - start_time;
        auto microsec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
        total += std::chrono::duration_cast<std::chrono::microseconds>(dur);
        cout << "Search time for " << str << " " << microsec << " us. Recipe size ";
        if (test2 != nullptr) {
            cout << test2->recipe.size() << endl;
        } else {
            cout << "0" << endl;
        }
    }
    cout << "Total search time " << total.count() << " us" << endl;
}

