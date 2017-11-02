#include "algomanager.h"
#include <QQmlContext>

AlgoManager::AlgoManager(QQmlContext *cnt, QObject *parent)
    : QObject(parent), cnt_(cnt)
{
   AbstractAlgoCreator *ptr = new HashAlgoCreator();
   AbstractAlgoCreator *ptr1 = new UnorderedmapAlgoCreator();
   algolist = {{ptr->getType(), ptr}, {ptr1->getType(), ptr1}};

}

QStringList AlgoManager::getAlgoList() {
    return algolist.keys();
}

void  AlgoManager::createAlgo(const QString &type) {
    selectedAlgo.reset(algolist.value(type)->create());
    cnt_->setContextProperty("algo", selectedAlgo.data());
}
