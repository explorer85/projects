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

    qmlRegisterInterface<VectorOfParams>("VectorOfParameters");

    ParametersModel pm;
    JsonParser jp;
    QString jsonString = jp.formatFromFile("data.json");
    std::vector<QStringList> parameters_ = jp.readParameters("data.json");
    pm.resetModel(parameters_);


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("jsonString", jsonString);
    engine.rootContext()->setContextProperty("paramsModel", &pm);
    engine.rootContext()->setContextProperty("jsonParser", &jp);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
