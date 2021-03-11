#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QString>
#include <QJsonDocument>


class JsonParser
{
public:
    JsonParser();
    QString read(const QString &fileName);
private:
    QString readObject(QJsonObject jsonObj);
    const int shiftSize{7};
    int shiftCount{-shiftSize};
};

#endif // JSONPARSER_H
