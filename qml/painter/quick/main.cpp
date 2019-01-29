#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWidget>

#include "quick.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Quick>("Quick", 1, 0, "Quick");

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}
