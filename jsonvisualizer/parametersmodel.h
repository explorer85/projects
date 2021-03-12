#ifndef PARAMETERSMODEL_H
#define PARAMETERSMODEL_H

#include <QAbstractTableModel>




class ParametersModel : public QAbstractTableModel
{
    Q_OBJECT
    enum Roles {
        setParamRole = Qt::UserRole + 1
    };
public:
    ParametersModel();
    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int,QByteArray> roleNames() const override;
    void resetModel(std::vector<QStringList> parameters);
    Q_INVOKABLE std::vector<QStringList> modelData() const {
        return parameters_;
    }
private:
    std::vector<QStringList> parameters_;
};


using VectorOfParams = std::vector<QStringList>;
Q_DECLARE_INTERFACE(VectorOfParams, "org.foo.List")

#endif // PARAMETERSMODEL_H
