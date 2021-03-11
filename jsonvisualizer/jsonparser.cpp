#include "jsonparser.h"
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

JsonParser::JsonParser()
{

}
QString JsonParser::read(const QString &fileName) {

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

    QJsonObject jsonObj;
    jsonObj = jsonDoc.object();
    QString result = readObject(jsonObj);
    return result;
}

QString JsonParser::readObject(QJsonObject jsonObj) {

    shiftCount += shiftSize;
    QString json;

    const QString slashn = "\n";
    for (auto it = jsonObj.begin(); it != jsonObj.end(); it++) {
        if (it.value().isObject()) {
            json += QString(shiftCount, ' ')  + "\"" + it.key() + "\"" + ": " + "{" + slashn;
            json += readObject(it->toObject());
            json += QString(shiftCount, ' ')  +"}" + "," + slashn;
        } else if (it.value().isArray()) {
            json += QString(shiftCount, ' ') + "\"" + it.key() + "\"" + ": " + "[" + slashn;
            QJsonArray jsonArray;
            jsonArray = it->toArray();
            for (auto arrIt = jsonArray.begin(); arrIt != jsonArray.end(); arrIt++) {
                if (arrIt->isObject()) {

                    json += QString(shiftCount, ' ')  +  "{" + slashn;
                    json += readObject(arrIt->toObject());
                    json += QString(shiftCount, ' ')  +"}" + "," + slashn;
                }
            }
            json += QString(shiftCount, ' ')  +"]" + "," + slashn;

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

            json += QString(shiftCount, ' ') + "\"" + it.key() + "\"" + ": "+ "\"" + value + "\"" + "," + slashn;
        }
    }

    shiftCount -= shiftSize;
    return json;

}



