#ifndef PHONEBOOKMODEL_H
#define PHONEBOOKMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class PhoneBookModel : public QAbstractTableModel {
  struct User {
    QString id;
    QString name;
    QString phone;
  };
  QList<User> users;

  enum UserRole { IdRole = Qt::UserRole + 1, NameRole, PhoneRole };

 public:
  PhoneBookModel();
  void loadModel(QString fileName);
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;
};

#endif  // PHONEBOOKMODEL_H
