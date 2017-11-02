#include "unorderedmapalgo.h"
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <unordered_map>

UnorderedmapAlgo::UnorderedmapAlgo()
{
    qDebug() << "UnorderedmapAlgo";
}



void UnorderedmapAlgo::run() {

    qDebug() << "UnorderedmapAlgo::run";
    int startTime = QDateTime::currentDateTime().toMSecsSinceEpoch();


   // QHash<QString /*word*/, long /*count*/> hashWords;
    std::unordered_map<std::string /*word*/, long /*count*/> hashWords;

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
        hashWords.insert(std::make_pair(st.toStdString(), 0));


       for (int i=0; i<100000; i++)
           int b = 0;

       emit lineProcessed(totalStringsCount_, totalWordsCount_, hashWords.size());
   }


   int endTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - startTime;

   emit algoFinished(endTime);

}





AbstractAlgo *UnorderedmapAlgoCreator::create()  {
    return new UnorderedmapAlgo();
}
QString UnorderedmapAlgoCreator::getType() const {
    return "UnorderedmapAlgo";
}
