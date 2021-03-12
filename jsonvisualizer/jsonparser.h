#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QString>
#include <QJsonDocument>
#include <vector>


class JsonParser
{
public:
    JsonParser();
    //прочитать массив parameters и вернуть его в виде вектора
    std::vector<QStringList> readParameters(const QString &fileName);
    //прочитать json из файла
    QString formatFromFile(const QString &fileName);
    //прочитать json из строки
    QString formatFromString(const QString &jsonString);
private:
    QJsonObject openFile(const QString &fileName);
    QJsonObject readString(const QString &jsonString);
    QString readObject(QJsonObject jsonObj, bool lastObject = true);
    const int shiftSize{7};
    int shiftCount{0};
    bool doubleDotFlag{false};


};

#endif // JSONPARSER_H
