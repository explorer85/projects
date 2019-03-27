#include "phonebookmodel.h"
#include <QFile>
#include <QTextStream>

const QString DELIMITER = ";";

PhoneBookModel::PhoneBookModel() {}

void PhoneBookModel::loadModel(const QString &fileName) {
  beginResetModel();
  users = loadFromFile(fileName);
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

PhoneBookModel::UsersList PhoneBookModel::loadFromFile(
    const QString &fileName) {
  QFile file{fileName};
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return {};
  QTextStream in(&file);

  UsersList users;
  while (!in.atEnd()) {
    QString line = in.readLine();
    QStringList list = line.split(DELIMITER);
    if (list.size() >= 3)
      users.push_back(User{list.at(0), list.at(1), list.at(2)});
  }

  return users;
}
