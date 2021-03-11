#include "parametersmodel.h"

ParametersModel::ParametersModel()
{

}

int ParametersModel::columnCount(const QModelIndex &parent) const {
    return 3;

}

int ParametersModel::rowCount(const QModelIndex &) const {
    return parameters_.size();
}

QVariant ParametersModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    auto it = parameters_.begin();
    std::advance(it, index.row());
    const QStringList p = *it;
    QString text = p[index.column()];
    switch (role) {
    case Qt::DisplayRole: {
        return text;
    }

    }

    return true;

}
bool ParametersModel::setData(const QModelIndex &/*index*/, const QVariant &/*value*/, int /*role*/) {

}
QHash<int,QByteArray> ParametersModel::roleNames() const {
    auto names = QAbstractItemModel::roleNames();
    return names;
}

void ParametersModel::resetModel(std::vector<QStringList> parameters) {
    beginResetModel();
    parameters_ = parameters;
    endResetModel();
}
