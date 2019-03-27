#include "filephonebookmodelloader.h"
#include <QFile>
#include <QTextStream>

const QString DELIMITER = ";";

FilePhoneBookModelLoader::FilePhoneBookModelLoader() {}

PhoneBookModel::UsersList FilePhoneBookModelLoader::load(
    const QString &fileName) {
  QFile file{fileName};
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return {};
  QTextStream in(&file);

  PhoneBookModel::UsersList users;
  while (!in.atEnd()) {
    QString line = in.readLine();
    QStringList list = line.split(DELIMITER);
    if (list.size() >= 3)
      users.push_back(PhoneBookModel::User{list.at(0), list.at(1), list.at(2)});
  }

  return users;
}
