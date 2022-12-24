#pragma once

#include <QObject>
#include <QDebug>
#include <QMetaProperty>

class Message  {
  Q_GADGET
 public:
  virtual void printName() {}
  virtual ~Message() {}

};


class AddTargetMessage : public Message {
  Q_GADGET
  Q_PROPERTY(int number MEMBER number)
  Q_PROPERTY(QString name MEMBER name)
 public:
  int number{0};
  QString name;
  virtual void printName() override {
    // qDebug() << "AddTargetMessage";
  }
};

class RemoveTargetMessage : public Message {
  Q_GADGET
  Q_PROPERTY(int number MEMBER number)
 public:
  int number{0};
};
