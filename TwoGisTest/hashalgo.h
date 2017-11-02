#ifndef HASHALGO_H
#define HASHALGO_H

#include "abstractalgo.h"
#include "abstractalgocreator.h"
#include <QDebug>


class HashAlgo : public AbstractAlgo
{
    Q_OBJECT
public:
    HashAlgo();
    ~HashAlgo() { qDebug() << "~HashAlgo1 ";


                }
private:
     void run();
};

class HashAlgoCreator : public AbstractAlgoCreator
{
public:
    AbstractAlgo* create();
    QString getType();
};



#endif // HASHALGO_H
