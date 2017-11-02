#include "abstractalgo.h"


void AbstractAlgo::startAlgo(const QString &name) {
    name_ = name;
    stopped = false;
    start();


}

void AbstractAlgo::stopAlgo() {
    stopped = true;
    emit algoFinished(false);

}

