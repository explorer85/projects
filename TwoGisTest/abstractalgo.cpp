#include "abstractalgo.h"



AbstractAlgo::~AbstractAlgo()  {

    qDebug() << "~AbstractAlgo ";
    stopAlgo();
    wait(); //ждем пока завершиться поток олгоритма

    while (isRunning());

}


void AbstractAlgo::startAlgo(const QString &name) {

    if (isRunning())
        return;
    name_ = name;
    stopped = false;
    start();

}

void AbstractAlgo::stopAlgo() {

    stopped = true;
    emit algoFinished(false);
}

