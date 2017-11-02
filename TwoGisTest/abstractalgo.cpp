#include "abstractalgo.h"



AbstractAlgo::~AbstractAlgo()  {

    qDebug() << "~AbstractAlgo ";
    quit();
#if QT_VERSION >= QT_VERSION_CHECK(5,2,0)
    requestInterruption();
#endif
    wait();

}


void AbstractAlgo::startAlgo(const QString &name) {
    name_ = name;
    stopped = false;
    start();


}

void AbstractAlgo::stopAlgo() {
    stopped = true;
    emit algoFinished(false);

}

