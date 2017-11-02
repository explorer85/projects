#ifndef UNORDEREDMAPALGO_H
#define UNORDEREDMAPALGO_H

#include "abstractalgo.h"
#include "abstractalgocreator.h"
#include <QDebug>


class UnorderedmapAlgo : public AbstractAlgo
{
     Q_OBJECT
public:
    UnorderedmapAlgo();
    ~UnorderedmapAlgo() { qDebug() << "~UnorderedmapAlgo "; }
private:
    void run();

};

class UnorderedmapAlgoCreator : public AbstractAlgoCreator
{
public:
    AbstractAlgo* create();
    QString getType() const;
};

#endif // UNORDEREDMAPALGO_H
