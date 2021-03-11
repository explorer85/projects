#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QString>
#include <QJsonDocument>
#include <vector>


class JsonParser
{
public:
    JsonParser();
    std::vector<QStringList> readParameters(const QString &fileName);
    QString read(const QString &fileName);
private:
    QJsonObject openFile(const QString &fileName);
    QString readObject(QJsonObject jsonObj);
    const int shiftSize{7};
    int shiftCount{-shiftSize};
    bool readParameters_{false};

};

#endif // JSONPARSER_H
