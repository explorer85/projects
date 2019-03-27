#include "phonebookmodel.h"

PhoneBookModel::PhoneBookModel() {}

void PhoneBookModel::loadModel(QString fileName) {
  beginResetModel();
  users.push_back(User{"1111", "2222", "3333"});
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
