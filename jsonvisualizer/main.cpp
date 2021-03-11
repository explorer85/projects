#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "jsonparser.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    JsonParser jp;
    QString jsonString = jp.read("data.json");


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("jsonString", jsonString);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
