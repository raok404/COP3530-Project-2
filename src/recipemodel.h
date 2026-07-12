#pragma once

#include <QAbstractListModel>
#include <QVector>
#include "data.h"

class RecipeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    RecipeModel(data_structure* data, QObject *parent = nullptr);

    enum Roles {
        NameRole = Qt::UserRole + 1,
        IngredientsRole,
        InstructionsRole,
        AvailableRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(
        const QModelIndex &index,
        int role = Qt::DisplayRole
        ) const override;

    QHash<int, QByteArray> roleNames() const override;

    void updateRecipes(QVector<recipeValue> recipes);

    Q_INVOKABLE void search(QString query);



private:
    QVector<recipeValue> m_recipes;
    data_structure* m_data;
};