#pragma once

#include <QObject>
#include <QMetaProperty>

class Message  {
  Q_GADGET
 public:
  virtual void printName() {}
  virtual ~Message() {}

};
