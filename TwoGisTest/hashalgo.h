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
    ~HashAlgo() { qDebug() << "~HashAlgo";


                }
private:
     void run();
};

class HashAlgoCreator : public AbstractAlgoCreator
{
public:
    AbstractAlgo* create();
    QString getType() const;
};



#endif // HASHALGO_H
