#include "data.h"
#include <QDebug>


void data_structure::processKeyTrigger(const QString &key)
{
    // Push the updated map configuration back up to the interface layer
    emit mapReady(m_orderedMap);
}

QVector<recipeValue> data_structure::search(QString key) {
    QVector<recipeValue> output;
    SplayTreeNode* result = s_tree.search(key.toStdString());
    if (result == nullptr) {
        return output;
    }
    else {
        for (Recipe& r : result->recipes) {
           output.push_back(recipeValue(r.recipeName, r.ingredientList, r.instructions));
        }
    }

    return output;
}

void data_structure::updateIngredientList(const QString &ingredientName) {
    std::string str = ingredientName.toStdString();
    qInfo() << str;
    //ingredientlist.push_back(str);
    qInfo() << "test test test";
}