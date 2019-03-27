#include "phonebookmodel.h"
#include <QFile>
#include <QTextStream>
#include "iphonebookmodelloader.h"

void PhoneBookModel::loadModel(const QString &fileName) {
  beginResetModel();
  users = loader_.load(fileName);
  endResetModel();
}

int PhoneBookModel::rowCount(const QModelIndex & /*parent*/) const {
  return users.size();
}
int PhoneBookModel::columnCount(const QModelIndex & /*parent*/) const {
  return 3;
}

QVariant PhoneBookModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  switch (role) {
    case UserRole::IdRole: {
      return users.at(index.row()).id;
      break;
    }
    case UserRole::NameRole: {
      return users.at(index.row()).name;
      break;
    }
    case UserRole::PhoneRole: {
      return users.at(index.row()).phone;
      break;
    }
    default:
      break;
  }

  return QVariant();
}

QHash<int, QByteArray> PhoneBookModel::roleNames() const {
  QHash<int, QByteArray> roleNames;
  roleNames[IdRole] = "id";
  roleNames[NameRole] = "name";
  roleNames[PhoneRole] = "phone";
  return roleNames;
}
