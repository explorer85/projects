#ifndef HASHALGO_H
#define HASHALGO_H

#include "abstractalgo.h"


class HashAlgo : public AbstractAlgo
{
    Q_OBJECT
public:
    HashAlgo();
     Q_INVOKABLE void startAlgo(const QString &name) override final;
     Q_INVOKABLE void stopAlgo() override final;
private:
     void run();
     QString  name_;
     bool stopped{false};

};

#endif // HASHALGO_H
