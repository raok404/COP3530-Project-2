#include "recipemodel.h"
#include "data.h"

RecipeModel::RecipeModel(data_structure* data, QObject *parent)
    : QAbstractListModel(parent)
{
    m_data = data;
}


int RecipeModel::rowCount(const QModelIndex &parent) const
{
    return m_recipes.size();
}


QVariant RecipeModel::data(
    const QModelIndex &index,
    int role
    ) const
{
    if (!index.isValid())
        return {};


    recipeValue recipe = m_recipes[index.row()];


    switch(role)
    {
    case NameRole:
        return recipe.name;

    case IngredientsRole:
        return recipe.ingredients;

    case InstructionsRole:
        return recipe.instructions;

    case AvailableRole:
        return recipe.isAvailable;
    }


    return {};
}


QHash<int, QByteArray> RecipeModel::roleNames() const
{
    return {
        {NameRole, "name"},
        {IngredientsRole, "ingredients"},
        {InstructionsRole, "instructions"},
        {AvailableRole, "isAvailable"}
    };
}


void RecipeModel::updateRecipes(QVector<recipeValue> recipes)
{
    beginResetModel();

    m_recipes = recipes;

    endResetModel();
}

void RecipeModel::search(QString query)
{
    QVector<recipeValue> results = m_data->search(query);

    beginResetModel();

    m_recipes = results;

    endResetModel();
}