#ifndef HASHALGO_H
#define HASHALGO_H

#include "abstractalgo.h"


class HashAlgo : public AbstractAlgo
{
public:
    HashAlgo();
     void parseFile(const QString &name) override final;
private:
     void run();
     QString  name_;

};

#endif // HASHALGO_H
