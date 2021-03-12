#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <memory>
#include <vector>

class JsonParser : public QObject {
  Q_OBJECT
 public:
  JsonParser();
  virtual ~JsonParser() {}
  bool openFile(const QString &fileName);
  //прочитать массив parameters и вернуть его в виде вектора
  std::vector<QStringList> readParameters();
  //записать массив parameters в файл
  void saveParameters(std::vector<QStringList> params);
  //вернуть не форматированную строку
  QString source();
  //форматировать открытый файл
  QString format();

  //преобразовать json обьект в форматированную строку
  QString readObject(QJsonObject jsonObj, bool lastObject = true);
  //преоборазовать форматированную строку в не форматированную строку
  QJsonObject writeObject(QString formattedJsonObj);

 private:
  QString fileName_;
  QJsonObject jsonRootObject_;
  const int shiftSize{7};
  int shiftCount{0};
  bool doubleDotFlag{false};

  QString valueToString(QJsonValue val);
};
using JsonParserPtr = std::shared_ptr<JsonParser>;

#endif  // JSONPARSER_H
