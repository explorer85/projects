#include "hashalgo.h"
#include <QDebug>
#include <QFile>

HashAlgo::HashAlgo()

{
   qDebug() << "HashAlgo";
}


void HashAlgo::run() {

    qDebug() << "HashAlgo::run";

    QHash<QString /*word*/, long /*count*/> hashWords;

    QFile file{name_};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "filenotopen";
        return;
    }

    QTextStream in{&file};
   long totalStringsCount_ = 0, totalWordsCount_ = 0;

   while (!in.atEnd()) {

       if (stopped)
           return;

       QString line = in.readLine();
       line.remove(QChar(','));
       //qDebug() << "HashAlgo::run" << line;
       QStringList sline = line.split(" ");
       totalStringsCount_ ++;
       totalWordsCount_+=sline.size();

       for (const QString &st: sline)
        hashWords.insert(st, 0);


       for (int i=0; i<100000; i++)
           int b = 0;

       emit lineProcessed(totalStringsCount_, totalWordsCount_, hashWords.size());
   }

   emit algoFinished(true);

}




AbstractAlgo *HashAlgoCreator::create()  {
    return new HashAlgo();
}
QString HashAlgoCreator::getType() {
    return "HashAlgo";
}
