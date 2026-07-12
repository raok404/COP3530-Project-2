#include "data.h"
#include <QDebug>


void data_structure::updateIngredientList(const QString &ingredientName) {
    std::string str = ingredientName.toStdString();
    qInfo() << str << " added";
    ingredientlist.push_back(str);

    signalIngredientChange();
}

void data_structure::signalIngredientChange() {
    for (const std::string &name: ingredientlist) {
        qInfo() << "adding to ing" << name;
        QString QSname = QString::fromStdString(name);
        emit addIngredientToModel(QSname);
    }
}

void data_structure::updateRecipeList(){
    for (const std::string &name: ingredientlist) {
        SplayTreeNode* test = s_tree.search(name);
        vector<Recipe> temp = test->recipes;
        for (const Recipe &recip : temp) {

        }
    }
}

void data_structure::initDatas() {
    signalIngredientChange();
}

void data_structure::processKeyTrigger(const QString &key)
{
    // Push the updated map configuration back up to the interface layer
    emit mapReady(m_orderedMap);
}

QVector<recipeValue> data_structure::search(QString key) {
    QVector<recipeValue> output;
    if (use_splay) {
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

    RedBlackTreeNode* result = rb_tree.search(key.toStdString());
    if (result == nullptr) {
        return output;
    }
    else {
        for (Recipe& r : result->recipe) {
            output.push_back(recipeValue(r.recipeName, r.ingredientList, r.instructions));
        }
    }

    return output;

}

void data_structure::switchTree() {
    use_splay = !use_splay;
    qInfo() << use_splay;
    if (use_splay) {
        m_text = "Using Splay Tree";
    }
    else {
        m_text = "Using RB Tree";
    }
    emit textChanged();
}

