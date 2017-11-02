#include "unorderedmapalgo.h"
#include <QDebug>
#include <QFile>

UnorderedmapAlgo::UnorderedmapAlgo()
{
    qDebug() << "UnorderedmapAlgo";
}



void UnorderedmapAlgo::run() {

    qDebug() << "UnorderedmapAlgo::run";

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
       qDebug() << "UnorderedmapAlgo::run" << line;
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





AbstractAlgo *UnorderedmapAlgoCreator::create()  {
    return new UnorderedmapAlgo();
}
QString UnorderedmapAlgoCreator::getType() {
    return "UnorderedmapAlgo";
}
