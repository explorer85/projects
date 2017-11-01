#include "fileparser.h"
#include <QDebug>


#include "hashalgo.h"

FileParser::FileParser(QObject *parent) : QObject(parent)
{

}

void FileParser::startParsing(const QString &path) {
    qDebug() << "startParsing" << path;



    AbstractAlgo *algo = new HashAlgo;
    connect(algo, &HashAlgo::lineProcessed, [=]
            (long totalStringsCount, long totalWordsCount, long uniqueWordsCoint) {
        emit lineProcessed(totalStringsCount, totalWordsCount);
    });
    algo->parseFile(path);


   // static long totalStringsCount_ = 0, totalWordsCount_ = 0;
//    while (!in.atEnd()) {
//        QString line = in.readLine();
//        totalStringsCount_ ++;
//        for (int i=0; i<10000; i++)
//            int b = 0;

    //    emit lineProcessed(totalStringsCount_, totalWordsCount_);

  //  }

}
