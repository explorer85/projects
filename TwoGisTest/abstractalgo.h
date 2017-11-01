#ifndef ABSTRACTALGO_H
#define ABSTRACTALGO_H

#include <QObject>
#include <QTextStream>
#include <QThread>

class AbstractAlgo : public QThread {
    Q_OBJECT
public:
    virtual void parseFile(const QString &name) = 0;
signals:
    void lineProcessed(long totalStringsCount, long totalWordsCount, long uniqueWordsCoint);

};

#endif // ABSTRACTALGO_H
