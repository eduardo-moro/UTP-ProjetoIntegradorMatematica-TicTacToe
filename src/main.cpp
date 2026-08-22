#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QLoggingCategory>
#include <QQmlContext>
#include "GameEngine.hpp"

int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("qt.multimedia.*=false\nffmpeg*=false");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    GameEngine gameEngine;

    engine.rootContext()->setContextProperty("gameEngine", &gameEngine);

    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}