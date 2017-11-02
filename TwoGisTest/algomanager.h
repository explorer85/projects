#ifndef ALGOMANAGER_H
#define ALGOMANAGER_H

#include <QObject>

#include "hashalgo.h"
#include "unorderedmapalgo.h"

#include <QVector>
#include <QScopedPointer>
#include <QSharedPointer>

class QQmlContext;

class AlgoManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSharedPointer<AbstractAlgo> algo MEMBER selectedAlgo NOTIFY algoChanged)
public:
    explicit AlgoManager(QQmlContext *cnt, QObject *parent = nullptr);

    Q_INVOKABLE QStringList getAlgoList();
    Q_INVOKABLE  void createAlgo(const QString &type);
signals:
    void algoChanged();

public slots:

private:
    QMap<QString /*algotype*/, AbstractAlgoCreator*> algolist;
    QSharedPointer<AbstractAlgo> selectedAlgo;
    QQmlContext *cnt_;
};

#endif // ALGOMANAGER_H
