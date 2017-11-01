#include "fileparser.h"
#include <QDebug>
#include <QFile>

FileParser::FileParser(QObject *parent) : QObject(parent)
{

}

void FileParser::startParsing(const QString &path) {
    qDebug() << "startParsing" << path;

    QFile file{path};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "filenotopen";
        return;
    }

    static long totalStringsCount_ = 0, totalWordsCount_ = 0;

    QTextStream in{&file};
    while (!in.atEnd()) {
        QString line = in.readLine();
        totalStringsCount_ ++;
        for (int i=0; i<10000; i++)
            int b = 0;

        emit lineProcessed(totalStringsCount_, totalWordsCount_);

    }

}
