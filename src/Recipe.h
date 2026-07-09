#ifndef COP3530_PROJECT_2_RECIPE_H
#define COP3530_PROJECT_2_RECIPE_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

using namespace std;

struct Recipe {
    string recipeName;
    vector<string> ingredientList;
    string instructions;

    Recipe(string name, vector<string> ingredients, string ins) {
        recipeName = name;
        ingredientList = ingredients;
        instructions = ins;
    }
};

struct RecipeBook {
    // RecipeBook book = RecipeBook("../datasets/normalized_recipes.json");
    // to load the recipes from the json

    vector<Recipe> recipes;

    RecipeBook(string filename) {
        ifstream jsonFile(filename);
        json allRecipes = json::parse(jsonFile);

        auto it = allRecipes.begin();
        std::cout << it.key() << std::endl;
        std::cout << it.value() << std::endl;

        for (auto& [key, recipe] : allRecipes.items()) {
            try {
                if (recipe.contains("title") && recipe.contains("norm_ingredients") && recipe.contains("instructions")) {
                    recipes.push_back(Recipe(recipe["title"], recipe["norm_ingredients"], recipe["instructions"]));
                }
            }
            catch (...) {
                cout << "Data missing for recipe :" << key << endl;
            }
        }
    }

    int getNumRecipes() {
        return recipes.size();
    }
};
#endif