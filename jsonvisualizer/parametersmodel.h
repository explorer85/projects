#ifndef PARAMETERSMODEL_H
#define PARAMETERSMODEL_H

#include <QAbstractListModel>

struct Parameter {
    QStringList fields;
};


class ParametersModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ParametersModel();
    //int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int,QByteArray> roleNames() const override;
    void resetModel(std::vector<QStringList> parameters);
private:
   std::vector<QStringList> parameters_;
};

#endif // PARAMETERSMODEL_H
