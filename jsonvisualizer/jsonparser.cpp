#include "jsonparser.h"
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

JsonParser::JsonParser(const QString &fileName) : QObject(nullptr), fileName_(fileName)
{

}

std::vector<QStringList> JsonParser::readParameters() {
    std::vector<QStringList> parameters_;
    QJsonObject jsonObj = openFile(fileName_);
    auto paramsIt = jsonObj.find("parameters");
    QJsonArray jsonArray;
    jsonArray = paramsIt->toArray();
    for (auto arrIt = jsonArray.begin(); arrIt != jsonArray.end(); arrIt++) {
        if (arrIt->isObject()) {
            auto obj = arrIt->toObject();
            QStringList columns;
            for (auto it = obj.begin(); it != obj.end(); it++) {
                if (it.value().isObject()) {
                    columns.append(QString(it.key() + ":") + readObject(it.value().toObject()));
                } else {
                    QString value = valueToString(it.value());
                    columns.append(QString(it.key() + ":" + value));
                }
             }
            //qDebug() << columns;
            parameters_.emplace_back(columns);

        }
    }


    return parameters_;

}

void JsonParser::saveParameters(std::vector<QStringList> params) {
    qDebug() << "JsonParser::saveParameters" << params.size();
    QJsonObject jsonObj = openFile(fileName_);
   // auto paramsIt = jsonObj.find("parameters");
    QJsonArray jsonArray;
    //jsonArray = paramsIt->toArray();

    for (auto i = 0; i < params.size(); i++) {
            QJsonObject iObj = jsonArray.at(i).toObject();
            QStringList columns = params[i];
            qDebug() << i << "-------------------";
            for (const QString& col : columns) {
                QStringList sl = col.split(":");
                QString key = sl.takeFirst();
                QString value = sl.join(":");
                qDebug() << key << "  " << value;
                iObj.insert(key, value);

             }
            jsonArray.insert(i, iObj);
    }

    QFile saveFile("save.json");
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
    }
    QJsonDocument saveDoc(jsonArray);
    saveFile.write(saveDoc.toJson(QJsonDocument::Compact));
}


QString JsonParser::formatFromFile() {

    QJsonObject jsonObj = openFile(fileName_);
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
    jsonDoc_ = QJsonDocument::fromJson(byteArray, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
        return {};
    }
    return  jsonDoc_.object();


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
            QString value = valueToString(it.value());
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

QString JsonParser::valueToString(QJsonValue val) {
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
