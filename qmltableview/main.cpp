#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "filephonebookmodelloader.h"
#include "phonebookmodel.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  FilePhoneBookModelLoader floader;
  // SqlPhoneBookModelLoader sloader;
  PhoneBookModel m{floader};
  m.loadModel(QCoreApplication::arguments().at(1));

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("phonebookmodel", &m);
  engine.load(QUrl(QLatin1String("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty()) return -1;

  return app.exec();
}
