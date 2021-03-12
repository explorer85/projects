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
    //прочитать json целиком
    QString read(const QString &fileName);
private:
    QJsonObject openFile(const QString &fileName);
    QString readObject(QJsonObject jsonObj, bool lastObject = true);
    const int shiftSize{7};
    int shiftCount{0};
    bool doubleDotFlag{false};


};

#endif // JSONPARSER_H
