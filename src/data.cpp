#include "data.h"
#include <QDebug>

data_structure::data_structure(QObject *parent)
    : QObject(parent)
{
}

void data_structure::processKeyTrigger(const QString &key)
{


    // Push the updated map configuration back up to the interface layer
    emit mapReady(m_orderedMap);
}