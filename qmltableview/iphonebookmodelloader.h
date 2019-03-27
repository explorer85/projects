#ifndef IPHONEBOOKMODELLOADER_H
#define IPHONEBOOKMODELLOADER_H

#include "phonebookmodel.h"

class IPhoneBookModelLoader {
 public:
  virtual PhoneBookModel::UsersList load(const QString &fileName) = 0;
};

#endif  // IPHONEBOOKMODELLOADER_H
