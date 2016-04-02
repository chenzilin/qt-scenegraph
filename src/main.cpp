#include <QGuiApplication>
#include <QQmlApplicationEngine>


#include <radarline.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<RadarLine>("RadarLine", 1, 0, "RadarLine");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
