#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <hashalgo.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    AbstractAlgo *algo = new HashAlgo();
    engine.rootContext()->setContextProperty("algo", algo);


    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;



    return app.exec();
}
