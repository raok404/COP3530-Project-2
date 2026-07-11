#pragma once

#include <QObject>
#include <QString>
#include <map>
#include <vector>
#include <string>

// Struct configuration remains using Q_GADGET so QML can access fields directly
struct recipeValue {
    Q_GADGET
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QString ingredients MEMBER ingredients)
    Q_PROPERTY(QString instructions MEMBER instructions)
    Q_PROPERTY(bool isAvailable MEMBER isAvailable)

public:
    QString name;
    QString ingredients;
    QString instructions;
    bool isAvailable;
};
Q_DECLARE_METATYPE(recipeValue)

class data_structure : public QObject
{
    Q_OBJECT

public:
    explicit data_structure(QObject *parent = nullptr);

public slots:
    // Slot receives the key string from the QML button layer
    void processKeyTrigger(const QString &key);

signals:
    // Signal sends the updated std::map downstream to QML
    void mapReady(const std::map<QString, recipeValue> &orderedMap);

private:
    std::map<QString, recipeValue> m_orderedMap;
    std::vector<recipeValue> recipelist;
    std::vector<recipeValue> shownrecipelist;
    std::vector<std::string> ingredientlist;
};