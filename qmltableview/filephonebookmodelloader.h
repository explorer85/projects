#ifndef FILEPHONEBOOKMODELLOADER_H
#define FILEPHONEBOOKMODELLOADER_H

#include "iphonebookmodelloader.h"

class FilePhoneBookModelLoader : public IPhoneBookModelLoader {
 public:
  FilePhoneBookModelLoader();
  PhoneBookModel::UsersList load(const QString &fileName) override;
};

#endif  // FILEPHONEBOOKMODELLOADER_H
