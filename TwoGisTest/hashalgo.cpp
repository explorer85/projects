#include "hashalgo.h"
#include <QDebug>
#include <QFile>

HashAlgo::HashAlgo()

{

}


void HashAlgo::parseFile(const QString &name) {
    name_ = name;

    start();


}

void HashAlgo::run() {

    qDebug() << "HashAlgo::run";


    QFile file{name_};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "filenotopen";
        return;
    }



    QTextStream in{&file};



   static long totalStringsCount_ = 0, totalWordsCount_ = 0;

   while (!in.atEnd()) {
        qDebug() << "HashAlgo::run";
       QString line = in.readLine();
       totalStringsCount_ ++;
       for (int i=0; i<100000; i++)
           int b = 0;

       emit lineProcessed(totalStringsCount_, totalWordsCount_, 0);
   }

}
