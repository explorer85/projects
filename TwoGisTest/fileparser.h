#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QObject>

class FileParser : public QObject
{
    Q_OBJECT
public:
    explicit FileParser(QObject *parent = nullptr);
    Q_INVOKABLE void startParsing(const QString &path);

signals:
    void lineProcessed(long totalStringsCount, long totalWordsCount);

public slots:
};

#endif // FILEPARSER_H
