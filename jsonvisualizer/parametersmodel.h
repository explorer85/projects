#ifndef PARAMETERSMODEL_H
#define PARAMETERSMODEL_H

#include <QAbstractTableModel>
#include <memory>

class JsonParser;
using JsonParserPtr = std::shared_ptr<JsonParser>;



class ParametersModel : public QAbstractTableModel
{
    Q_OBJECT
    enum Roles {
        setParamRole = Qt::UserRole + 1,
        NsgbrHighLightRole
    };
public:
    ParametersModel(JsonParserPtr jp);
    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int,QByteArray> roleNames() const override;
    void resetModel(std::vector<QStringList> parameters);
    Q_INVOKABLE void saveModelData();
private:
    std::vector<QStringList> parameters_;
    JsonParserPtr jp_;
};


using VectorOfParams = std::vector<QStringList>;

#endif // PARAMETERSMODEL_H
