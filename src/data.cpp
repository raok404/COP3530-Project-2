#include "data.h"
#include <QDebug>


void data_structure::processKeyTrigger(const QString &key)
{

    // Push the updated map configuration back up to the interface layer
    emit mapReady(m_orderedMap);
}

void data_structure::updateIngredientList(const QString &ingredientName) {
    std::string str = ingredientName.toStdString();
    qInfo() << str;
    //ingredientlist.push_back(str);
    qInfo() << "test test test";
}