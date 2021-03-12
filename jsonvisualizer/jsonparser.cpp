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
//                    auto o = it.value().toObject();
//                    qDebug() << o.keys();
                    columns.append(QString(it.key() + ":") + readObject(it.value().toObject()));
                } else {
                    columns.append(QString(it.key() + ":" + it.value().toString()));
                   // columns.append(readObject(it->toObject()));
                }
             }
            qDebug() << columns;
            parameters_.emplace_back(columns);

        }
    }


    return parameters_;

}


QString JsonParser::read(const QString &fileName) {

    QJsonObject jsonObj = openFile(fileName);
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

QString JsonParser::readObject(QJsonObject jsonObj) {


    const QString slashn = "\n";
    QString json;

    //если предыдущее чтение была прочитано :, то не добавляем сдвиг пробелами
    if (doubleDotFlag) {
        json += "{" + slashn;
        doubleDotFlag = false;
    } else
    {
        json += QString(shiftCount, ' ')  + "{" + slashn;
    }

    for (auto it = jsonObj.begin(); it != jsonObj.end(); it++) {
        if (it.value().isObject()) {
            shiftCount += shiftSize;
            json += QString(shiftCount, ' ')  + "\"" + it.key() + "\"" + ": ";
            doubleDotFlag = true;

            json += readObject(it->toObject());
            shiftCount -= shiftSize;
        } else if (it.value().isArray()) {
            shiftCount += shiftSize;
            json += QString(shiftCount, ' ') + "\"" + it.key() + "\"" + ": " + "[" + slashn;
            QJsonArray jsonArray;
            jsonArray = it->toArray();
            for (auto arrIt = jsonArray.begin(); arrIt != jsonArray.end(); arrIt++) {
                if (arrIt->isObject()) {
                    shiftCount += shiftSize;
                    //json += QString(shiftCount, ' ')  +  "{" + slashn;
                    json += readObject(arrIt->toObject());
                    shiftCount -= shiftSize;
//                    if ((arrIt + 1) != jsonArray.end())
//                        json += ",";
//                    json += slashn;
                }
            }
            json += QString(shiftCount, ' ')  +"]" + slashn;
            shiftCount -= shiftSize;

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


            json += QString(shiftCount, ' ') + "\"" + it.key() + "\"" + ": "+ "\"" + value + "\"" + slashn;
            shiftCount -= shiftSize;
        }



//        if ((it + 1) != jsonObj.end())
//            json += ",";
//        json += slashn;


    }


    json += QString(shiftCount, ' ')  + "}" + slashn;

    return json;

}



