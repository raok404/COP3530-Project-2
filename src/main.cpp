#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <data.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    data_structure *datas = new data_structure();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataStructureManager", datas);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("ratatouile", "Main");

    return QGuiApplication::exec();
}
