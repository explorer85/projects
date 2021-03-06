#include "jsonparser.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

JsonParser::JsonParser() : QObject(nullptr) {}

std::vector<QStringList> JsonParser::readParameters() {
  std::vector<QStringList> parameters_;
  auto paramsIt = jsonRootObject_.find("parameters");
  QJsonArray jsonArray;
  jsonArray = paramsIt->toArray();
  for (auto arrIt = jsonArray.begin(); arrIt != jsonArray.end(); arrIt++) {
    if (arrIt->isObject()) {
      auto obj = arrIt->toObject();
      QStringList columns;
      for (auto it = obj.begin(); it != obj.end(); it++) {
        if (it.value().isObject()) {
          columns.append(QString(it.key() + ":") +
                         readObject(it.value().toObject()));
        } else {
          QString value = valueToString(it.value());
          columns.append(QString(it.key() + ":" + value));
        }
      }
      parameters_.emplace_back(columns);
    }
  }

  return parameters_;
}

void JsonParser::saveParameters(const std::vector<QStringList>& params) {
  qDebug() << "JsonParser::saveParameters" << params.size();
  QJsonArray jsonArray;

  for (unsigned long i = 0; i < params.size(); i++) {
    QJsonObject iObj = jsonArray.at(i).toObject();
    QStringList columns = params[i];
    for (const QString& col : columns) {
      QStringList sl = col.split(":");
      QString key = sl.takeFirst();
      QString value = sl.join(":");
      if (key == "value") {
        QJsonObject obj = writeObject(value);
        iObj.insert(key, obj);
      } else
        iObj.insert(key, value);
    }
    jsonArray.insert(i, iObj);
  }

  QFile saveFile("data.json");
  if (!saveFile.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open save file.");
  }
  jsonRootObject_["parameters"] = jsonArray;
  QJsonDocument saveDoc(jsonRootObject_);
  saveFile.write(saveDoc.toJson(QJsonDocument::Compact));
}

QString JsonParser::source() const {
  QJsonDocument d(jsonRootObject_);
  return d.toJson(QJsonDocument::Compact);
}

QString JsonParser::format() {
  //можно было воспользоваться стандартной форматирования
  //но я не ищу легких путей
  QString result = readObject(jsonRootObject_);
  return result;
}

bool JsonParser::openFile(const QString& fileName) {
  QFile file;
  file.setFileName(fileName);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Json filef couldn't be opened/found";
    return false;
  }
  QByteArray byteArray;
  byteArray = file.readAll();
  file.close();

  QJsonParseError parseError;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
  jsonRootObject_ = jsonDoc.object();
  if (parseError.error != QJsonParseError::NoError) {
    qWarning() << "Parse error at " << parseError.offset << ":"
               << parseError.errorString();
    return false;
  }
  return true;
}

QString JsonParser::readObject(const QJsonObject& jsonObj, bool lastObject) {
  const QString slashn = "\n";
  QString json;

  //если предыдущее значение которое была прочитано ":", то не добавляем сдвиг
  //пробелами
  QString shift;
  if (doubleDotFlag_)
    doubleDotFlag_ = false;
  else
    shift = QString(shiftCount_, ' ');

  json += shift + "{" + slashn;

  for (auto it = jsonObj.begin(); it != jsonObj.end(); it++) {
    //Обьект
    if (it.value().isObject()) {
      shiftCount_ += shiftSize_;
      json += QString(shiftCount_, ' ') + '"' + it.key() + '"' + ": ";
      doubleDotFlag_ = true;

      //добавляем флаг
      bool flag = false;
      if ((it + 1) == jsonObj.end()) flag = true;

      json += readObject(it->toObject(), flag);
      shiftCount_ -= shiftSize_;

    }
    //Массив
    else if (it.value().isArray()) {
      shiftCount_ += shiftSize_;
      json += QString(shiftCount_, ' ') + '"' + it.key() + '"' + ": " + "[" +
              slashn;
      QJsonArray jsonArray;
      jsonArray = it->toArray();
      for (auto arrIt = jsonArray.begin(); arrIt != jsonArray.end(); arrIt++) {
        if (arrIt->isObject()) {
          shiftCount_ += shiftSize_;

          //добавляем флаг
          bool flag = false;
          if ((arrIt + 1) == jsonArray.end()) flag = true;

          json += readObject(arrIt->toObject(), flag);
          shiftCount_ -= shiftSize_;
        } else {
          QString value = valueToString(*arrIt);
          json += QString(shiftCount_, ' ') + value;
          //добавляем запятую
          if ((arrIt + 1) != jsonArray.end()) json += ",";
          json += slashn;
        }
      }
      json += QString(shiftCount_, ' ') + "]";
      shiftCount_ -= shiftSize_;

      //добавляем запятую
      if ((it + 1) != jsonObj.end()) json += ",";
      json += slashn;

    }
    //остальные типы
    else {
      shiftCount_ += shiftSize_;
      QString value = valueToString(it.value());
      json += QString(shiftCount_, ' ') + '"' + it.key() + '"' + ": " + '"' +
              value + '"';

      shiftCount_ -= shiftSize_;

      //добавляем запятую
      if ((it + 1) != jsonObj.end()) json += ",";
      json += slashn;
    }
  }
  json += QString(shiftCount_, ' ') + "}";
  //не добавляем запятую для последнего объекта
  if (!lastObject) json += ",";

  json += slashn;

  return json;
}

QJsonObject JsonParser::writeObject(const QString& formattedJsonObj) {
  //немогу уже слишком муторно обратно парсить руками:)
  QJsonParseError pe;
  QJsonDocument dd = QJsonDocument::fromJson(formattedJsonObj.toUtf8(), &pe);
  return dd.object();
}

QString JsonParser::valueToString(const QJsonValue& val) const {
  QString value;
  switch (val.type()) {
    case QJsonValue::Null:
      value = "null";
      break;
    case QJsonValue::Bool:
      value = val.toBool() ? QString("true") : QString(false);
      break;
    case QJsonValue::Double:
      value = QString::number(val.toDouble());
      break;
    case QJsonValue::String:
      value = val.toString();
      break;
    case QJsonValue::Undefined:
      value = "undefined";
      break;
    default:
      value = "UNDEFINED JSON TYPE";
      break;
  }
  return value;
}
