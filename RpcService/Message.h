#pragma once

#include <QObject>
#include <QMetaProperty>



class Message  {

  Q_GADGET
 public:
  class MessagesHandler;
  virtual void printName() {}
  virtual ~Message() {}
  virtual void accept(MessagesHandler &v) = 0;

};
