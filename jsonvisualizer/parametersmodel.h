#ifndef PARAMETERSMODEL_H
#define PARAMETERSMODEL_H

#include <QAbstractTableModel>

class JsonParser;



class ParametersModel : public QAbstractTableModel
{
    Q_OBJECT
    enum Roles {
        setParamRole = Qt::UserRole + 1,
        NsgbrHighLightRole
    };
public:
    ParametersModel(JsonParser *jp);
    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int,QByteArray> roleNames() const override;
    void resetModel(std::vector<QStringList> parameters);
    Q_INVOKABLE void saveModelData();
private:
    std::vector<QStringList> parameters_;
    JsonParser *jp_;
};


using VectorOfParams = std::vector<QStringList>;
Q_DECLARE_INTERFACE(VectorOfParams, "org.foo.List")

#endif // PARAMETERSMODEL_H
