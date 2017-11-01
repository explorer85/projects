#ifndef ABSTRACTALGO_H
#define ABSTRACTALGO_H

#include <QObject>
#include <QTextStream>
#include <QThread>

class AbstractAlgo : public QThread {
    Q_OBJECT
public:
    virtual void startAlgo(const QString &fileName) = 0;
    virtual void stopAlgo() = 0;
signals:
    void lineProcessed(long totalStringsCount, long totalWordsCount, long uniqueWordsCount); //должен генерироваться после обработки строки
    void algoFinished(bool result); //должен генерироваться при завершении работы алгоритма

};

#endif // ABSTRACTALGO_H
