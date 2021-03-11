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
            QString objstring = readObject(obj);
            QStringList stlist = objstring.split("\n");
            //qDebug() << stlist;
            parameters_.emplace_back(stlist);

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

    shiftCount += shiftSize;
    QString json;

    const QString slashn = "\n";
    for (auto it = jsonObj.begin(); it != jsonObj.end(); it++) {
        if (it.value().isObject()) {
            json += QString(shiftCount, ' ')  + "\"" + it.key() + "\"" + ": " + "{" + slashn;
            json += readObject(it->toObject());
            json += QString(shiftCount, ' ')  +"}";
        } else if (it.value().isArray()) {
            json += QString(shiftCount, ' ') + "\"" + it.key() + "\"" + ": " + "[" + slashn;
            QJsonArray jsonArray;
            jsonArray = it->toArray();
            for (auto arrIt = jsonArray.begin(); arrIt != jsonArray.end(); arrIt++) {
                if (arrIt->isObject()) {
                    shiftCount += shiftSize;
                    json += QString(shiftCount, ' ')  +  "{" + slashn;
                    json += readObject(arrIt->toObject());
                    json += QString(shiftCount, ' ')  +"}";
                    shiftCount -= shiftSize;
                    if ((arrIt + 1) != jsonArray.end())
                        json += ",";
                    json += slashn;
                }
            }
            json += QString(shiftCount, ' ')  +"]";

        } else {
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
        }



        if ((it + 1) != jsonObj.end())
            json += ",";
        json += slashn;


    }


    shiftCount -= shiftSize;
    return json;

}



