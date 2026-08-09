#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("qt.multimedia.*=false\nffmpeg*=false");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}