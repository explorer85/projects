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
  void saveParameters(const std::vector<QStringList> &params);
  //вернуть не форматированную строку
  QString source() const;
  //форматировать открытый файл
  QString format();

  //преобразовать json обьект в форматированную строку
  QString readObject(const QJsonObject &jsonObj, bool lastObject = true);
  //преоборазовать форматированную строку в не форматированную строку
  QJsonObject writeObject(const QString &formattedJsonObj);

 private:
  QString fileName_;
  QJsonObject jsonRootObject_;
  const int shiftSize_{7};
  int shiftCount_{0};
  bool doubleDotFlag_{false};

  QString valueToString(const QJsonValue &val) const;
};
using JsonParserPtr = std::shared_ptr<JsonParser>;

#endif  // JSONPARSER_H
