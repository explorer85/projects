#include "jsonparser.h"
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

JsonParser::JsonParser()
{

}

std::vector<QStringList> JsonParser::readParameters(const QString &fileName) {
    std::vector<QStringList> parameters_;
    QJsonObject jsonObj = openFile(fileName);
    auto paramsIt = jsonObj.find("parameters");
    QJsonArray jsonArray;
    jsonArray = paramsIt->toArray();
    for (auto arrIt = jsonArray.begin(); arrIt != jsonArray.end(); arrIt++) {
        if (arrIt->isObject()) {
            auto obj = arrIt->toObject();
            QStringList columns;
            for (auto it = obj.begin(); it != obj.end(); it++) {
                //qDebug() << it.key() << it.value();
                if (it.value().isObject()) {
                    columns.append(QString(it.key() + ":") + readObject(it.value().toObject()));
                } else {
                    columns.append(QString(it.key() + ":" + it.value().toString()));
                }
             }
            qDebug() << columns;
            parameters_.emplace_back(columns);

        }
    }


    return parameters_;

}


QString JsonParser::formatFromFile(const QString &jsonString) {

    QJsonObject jsonObj = openFile(jsonString);
    QString result = readObject(jsonObj);
    return result;
}

QString JsonParser::formatFromString(const QString &jsonString){
    QJsonObject jsonObj = readString(jsonString);
    QString result = readObject(jsonObj);
    return result;
}

QJsonObject JsonParser::openFile(const QString &fileName) {
    QFile file;
    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Json filef couldn't be opened/found";
        return {};
    }
    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
        return {};
    }

    return  jsonDoc.object();


}

QJsonObject JsonParser::readString(const QString &jsonString) {
    QJsonParseError parseError;
    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);
    return  jsonDoc.object();
}

QString JsonParser::readObject(QJsonObject jsonObj, bool lastObject) {


    const QString slashn = "\n";
    QString json;

    //если предыдущее значение которое была прочитано ":", то не добавляем сдвиг пробелами
    QString shift;
    if (doubleDotFlag)
        doubleDotFlag = false;
    else
        shift = QString(shiftCount, ' ');

    json += shift  + "{" + slashn;

    for (auto it = jsonObj.begin(); it != jsonObj.end(); it++) {
        if (it.value().isObject()) {
            shiftCount += shiftSize;
            json += QString(shiftCount, ' ')  + "\"" + it.key() + "\"" + ": ";
            doubleDotFlag = true;

            //добавляем флаг
            bool flag = false;
            if ((it + 1) == jsonObj.end())
                flag = true;

            json += readObject(it->toObject(), flag);
            shiftCount -= shiftSize;

        } else if (it.value().isArray()) {
            shiftCount += shiftSize;
            json += QString(shiftCount, ' ') + "\"" + it.key() + "\"" + ": " + "[" + slashn;
            QJsonArray jsonArray;
            jsonArray = it->toArray();
            for (auto arrIt = jsonArray.begin(); arrIt != jsonArray.end(); arrIt++) {
                if (arrIt->isObject()) {
                    shiftCount += shiftSize;

                    //добавляем флаг
                    bool flag = false;
                    if ((arrIt + 1) == jsonArray.end())
                        flag = true;

                    json += readObject(arrIt->toObject(), flag);
                    shiftCount -= shiftSize;
                }
            }
            json += QString(shiftCount, ' ')  +"]";
            shiftCount -= shiftSize;

            //добавляем запятую
            if ((it + 1) != jsonObj.end())
                json += ",";
            json += slashn;

        } else {
            shiftCount += shiftSize;
            QString value;
            switch (it.value().type()) {
            case QJsonValue::Null:
                value = "null";
                break;
            case QJsonValue::Bool:
                value = it.value().toBool() ? QString("true") : QString(false);
                break;
            case QJsonValue::Double:
                value = QString::number(it.value().toDouble());
                break;
            case QJsonValue::String:
                value = it.value().toString();
                break;
            case QJsonValue::Undefined:
                value = "undefined";
                break;
            default:
                value = "UNDEFINED JSON TYPE";
                break;

            }
            json += QString(shiftCount, ' ') + "\"" + it.key() + "\"" + ": "+ "\"" + value + "\"";

            shiftCount -= shiftSize;

            //добавляем запятую
            if ((it + 1) != jsonObj.end())
                json += ",";
            json += slashn;
        }
    }
    json += QString(shiftCount, ' ')  + "}";
    //не добавляем запятую для последнего объекта
    if (!lastObject)
        json += ",";
   // else
        //lastObjectFlag = false;


    json += slashn;

    return json;

}
