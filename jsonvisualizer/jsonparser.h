#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QString>
#include <QJsonDocument>


class JsonParser
{
public:
    JsonParser();
    void read(const QString &fileName);
    QString readObject(QJsonObject jsonObj);
};

#endif // JSONPARSER_H
