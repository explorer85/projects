#ifndef PHONEBOOKMODEL_H
#define PHONEBOOKMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class IPhoneBookModelLoader;

class PhoneBookModel : public QAbstractTableModel {
 public:
  struct User {
    QString id;
    QString name;
    QString phone;
  };
  using UsersList = QList<User>;
  PhoneBookModel(IPhoneBookModelLoader &loader) : loader_(loader) {}
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;
  void loadModel(const QString &fileName);

 private:
  UsersList users;
  IPhoneBookModelLoader &loader_;

  enum UserRole { IdRole = Qt::UserRole + 1, NameRole, PhoneRole };
};

#endif  // PHONEBOOKMODEL_H
