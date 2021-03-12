#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "jsonparser.h"
#include "parametersmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    JsonParserPtr jp = std::make_shared<JsonParser>();
    if (!jp->openFile("data.json")) {
        qDebug() << "file not found!";
        return 0;
    }
    ParametersModel pm{jp};

    QString jsonString = jp->format();
    std::vector<QStringList> parameters = jp->readParameters();
    pm.resetModel(parameters);


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("jsonString", jsonString);
    engine.rootContext()->setContextProperty("paramsModel", &pm);
    engine.rootContext()->setContextProperty("jsonParser", jp.get());
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
