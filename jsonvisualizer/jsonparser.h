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
};

#endif // JSONPARSER_H
