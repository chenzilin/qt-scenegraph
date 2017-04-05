#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "trapezium.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Trapezium>("Trapezium",1,0,"Trapezium");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
