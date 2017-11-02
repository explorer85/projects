#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <hashalgo.h>
#include <unorderedmapalgo.h>

#include "algomanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    AlgoManager *amanager = new AlgoManager(engine.rootContext());
    engine.rootContext()->setContextProperty("amanager", amanager);


    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
