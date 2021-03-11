#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QString>
#include <QJsonDocument>
#include <vector>


class JsonParser
{
public:
    JsonParser();
    QString read(const QString &fileName);
    const std::vector<QString>& parameters() const {
        return parameters_;
    }
private:
    QString readObject(QJsonObject jsonObj);
    const int shiftSize{7};
    int shiftCount{-shiftSize};
    bool readParameters_{false};
    std::vector<QString> parameters_;
};

#endif // JSONPARSER_H
