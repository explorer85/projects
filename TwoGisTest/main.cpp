#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <fileparser.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    FileParser fparser;
    engine.rootContext()->setContextProperty("fparser", &fparser);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;



    return app.exec();
}
