#include "jsonparser.h"
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

JsonParser::JsonParser()
{

}
void JsonParser::read(const QString &fileName) {


    //1. Open the QFile and write it to a byteArray and close the file
    QFile file;
    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Json filef couldn't be opened/found";
        return;
    }
    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    //2. Format the content of the byteArray as QJsonDocument
    //and check on parse Errors
    QJsonParseError parseError;
    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
        return;
    }

    //3. Create a jsonObject and fill it with the byteArray content, formatted
    //and holding by the jsonDocument Class
    QJsonObject jsonObj;
    jsonObj = jsonDoc.object();
    //QString result;
    readObject(jsonObj);




    //4. Now picking the jsonValues and printing them out or do what ever you need
//    QJsonValue jsonVal;
//    QTextStream textStream(stdout);

//    jsonVal = jsonObj.value("name");
    //    textStream << jsonVal.toString() << endl;

    //5. Now we need to fill the object of the object. To do that, we need
    //the Item Object and a jsonSubVal object for json without a loop
    //    QJsonObject jsonItemObj;
    //    QJsonValue jsonSubVal;

    //    jsonVal = jsonObj.value(QString("links"));
    //    jsonItemObj = jsonVal.toObject();
    //    qDebug() << jsonItemObj;
    // jsonSubVal = jsonItemObj["Street"];
    //    textStream << jsonSubVal.toString() << endl;




}

QString JsonParser::readObject(QJsonObject jsonObj) {
    // qDebug() << jsonObj.keys();

    for (auto it = jsonObj.begin(); it != jsonObj.end(); it++) {
        if (it.value().isObject()) {
            qDebug() << "{} " << it.key();
            readObject(it->toObject());
        } else if (it.value().isArray()) {
            qDebug() << "[] " << it.key();
            QJsonArray jsonArray;
            jsonArray = it->toArray();
            for (auto arrIt = jsonArray.begin(); arrIt != jsonArray.end(); arrIt++) {
                if (arrIt->isObject()) {
                    qDebug() << " readarr";
                    readObject(arrIt->toObject());
                }

            }

        } else {
            //qDebug() << "PARSEVALUE" << it.key();
            qDebug() << it.key() << ":" << it.value().toVariant();
        }
    }
    return "";

}


//void readJsonFile()
//{
//    qDebug() << "Read Json File:";



//    QByteArray byteArray;
//    byteArray = file.readAll();
//    file.close();

//    //2. Format the content of the byteArray as QJsonDocument
//    //and check on parse Errors
//    QJsonParseError parseError;
//    QJsonDocument jsonDoc;
//    jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
//    if(parseError.error != QJsonParseError::NoError){
//        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
//        return;
//    }

//    //3. Create a jsonObject and fill it with the byteArray content, formatted
//    //and holding by the jsonDocument Class
//    QJsonObject jsonObj;
//    jsonObj = jsonDoc.object();

//    //4. Now picking the jsonValues and printing them out or do what ever you need
//    QJsonValue jsonVal;
//    QTextStream textStream(stdout);

//    jsonVal = jsonObj.value("FirstName");
//    textStream << jsonVal.toString() << endl;

//    jsonVal = jsonObj.value("MiddleName");
//    //null gets back to an empty fild - added the sting "null/empty" to make it visible
//    textStream << jsonVal.toVariant().toString() << "null/empty" << endl;

//    jsonVal = jsonObj.value("LastName");
//    textStream << jsonVal.toString() << endl;

//    //The number has to be converted to an int and than to a string to print it
//    jsonVal = jsonObj.value("Age");
//    textStream << QString::number(jsonVal.toInt()) << endl;

//    //5. Now we need to fill the object of the object. To do that, we need
//    //the Item Object and a jsonSubVal object for json without a loop
//    QJsonObject jsonItemObj;
//    QJsonValue jsonSubVal;

//    jsonVal = jsonObj.value(QString("Address"));
//    jsonItemObj = jsonVal.toObject();

//       jsonSubVal = jsonItemObj["Street"];
//       textStream << jsonSubVal.toString() << endl;

//       jsonSubVal = jsonItemObj["City"];
//       textStream << jsonSubVal.toString() << endl;

//       jsonSubVal = jsonItemObj["Country"];
//       textStream << jsonSubVal.toString() << endl;

//    //6. now the Phone Numbers array with a loop
//    QJsonArray jsonArray;
//    jsonArray = jsonObj["Phone numbers"].toArray();

//    for(int i = 0; i < jsonArray.size(); i++)
//        textStream << jsonArray[i].toString() << endl;

//    textStream << "or with foreach" << endl;

//    foreach(QJsonValue v, jsonArray)
//        textStream << v.toString() << endl;

//    //7. And finally the bool value:
//    jsonVal = jsonObj.value(QString("Valid"));
//    textStream << jsonVal.toVariant().toString() << endl;

//    textStream << "or as number, not a string: ";

//    textStream << (QString::number(jsonVal.toInt())) << endl;

//    textStream << "\nThe whole file as printed in the file \n" <<
//                  jsonDoc.toJson(QJsonDocument::Indented);

