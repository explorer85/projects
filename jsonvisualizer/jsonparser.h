#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <vector>


class JsonParser : public QObject
{
    Q_OBJECT
public:
    JsonParser(const QString &fileName);
    virtual ~JsonParser() {}
    //прочитать массив parameters и вернуть его в виде вектора
    std::vector<QStringList> readParameters();
    //записать массив parameters в файл
    void saveParameters(std::vector<QStringList> params);
    //прочитать json из файла
    QString formatFromFile();
private:
    QString fileName_;
    QJsonDocument jsonDoc_;
    QJsonObject openFile(const QString &fileName);
    QString readObject(QJsonObject jsonObj, bool lastObject = true);

    QString valueToString(QJsonValue val);
    const int shiftSize{7};
    int shiftCount{0};
    bool doubleDotFlag{false};


};

#endif // JSONPARSER_H
