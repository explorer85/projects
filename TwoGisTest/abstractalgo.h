#ifndef ABSTRACTALGO_H
#define ABSTRACTALGO_H

#include <QObject>
#include <QTextStream>
#include <QThread>
#include <QDebug>

class AbstractAlgo : public QThread {
    Q_OBJECT
public:
    Q_INVOKABLE virtual void startAlgo(const QString &fileName);
    Q_INVOKABLE virtual void stopAlgo();
    ~AbstractAlgo();
    virtual void run() = 0; //переопределить и создать реализацию алгоритма здесь
signals:
    void lineProcessed(long totalStringsCount, long totalWordsCount, long uniqueWordsCount); //должен генерироваться после обработки строки
    void algoFinished(bool result); //должен генерироваться при завершении работы алгоритма

protected:
    QString  name_;
    bool stopped{false};

};

#endif // ABSTRACTALGO_H
