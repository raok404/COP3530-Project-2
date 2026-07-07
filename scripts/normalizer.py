# this is the format of one recipe in the normalized json file
# norm_ingredients has just the ingredient name

# "rmK12Uau.ntP510KeImX506H6Mr6jTu": {
#         "title": "Slow Cooker Chicken and Dumplings",
#         "ingredients": [
#             "4 skinless, boneless chicken breast halves ADVERTISEMENT",
#             "2 tablespoons butter ADVERTISEMENT",
#             "2 (10.75 ounce) cans condensed cream of chicken soup ADVERTISEMENT",
#             "1 onion, finely diced ADVERTISEMENT",
#             "2 (10 ounce) packages refrigerated biscuit dough, torn into pieces ADVERTISEMENT",
#             "ADVERTISEMENT"
#         ],
#         "instructions": "Place the chicken, butter, soup, and onion in a slow cooker, and fill with enough water to cover.\nCover, and cook for 5 to 6 hours on High. About 30 minutes before serving, place the torn biscuit dough in the slow cooker. Cook until the dough is no longer raw in the center.\n",
#         "picture_link": "55lznCYBbs2mT8BTx6BTkLhynGHzM.S",
#         "norm_ingredients": [
#             "skinless boneless chicken halves",
#             "butter",
#             "condensed cream chicken soup",
#             "onion",
#             "biscuit dough torn"
#         ]
#     },

import ingredient_slicer
import json

def get_ingredient(ingredient_str:str)->str:
    slicer = ingredient_slicer.IngredientSlicer(ingredient_str)
    return slicer.food()

def write_normalized_file():
    with open("./datasets/recipes_raw_nosource_ar.json", "r", encoding="utf-8") as file1:
        data:dict = json.load(file1)
    with open("./datasets/recipes_raw_nosource_epi.json", "r", encoding="utf-8") as file2:
        data.update(json.load(file2))
    with open("./datasets/recipes_raw_nosource_fn.json", "r", encoding="utf-8") as file3:
        data.update(json.load(file3))

    no_ingredient_items = []

    for item in data:
        recipe = data[item]
        ingredients = recipe.get("ingredients")
        if not ingredients:
            no_ingredient_items.append(item)
        else:
            recipe["norm_ingredients"] = []
            for ingredient in ingredients:
                if (ingredient == "ADVERTISEMENT"):
                    continue
                ingredient = ingredient.strip(" ADVERTISEMENT")
                try:
                    norm_ingred = get_ingredient(ingredient)
                    recipe["norm_ingredients"].append(norm_ingred)
                except Exception as e:
                    print(f"Error occurred at {item}, {e}")

    for item in no_ingredient_items:
        data.pop(item, None)
    
    with open("./datasets/normalized_recipes.json", "w") as file:
        json.dump(data, file, indent=4)

    print(len(data))



write_normalized_file()