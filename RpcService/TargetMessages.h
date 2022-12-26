#pragma once

#include <QObject>
#include <QDebug>
#include <QMetaProperty>

#include "Message.h"


class AddTargetMessage : public Message {
  Q_GADGET
  Q_PROPERTY(int number MEMBER number)
  Q_PROPERTY(QString name MEMBER name)
 public:
  int number{0};
  QString name;
  void accept(MessagesHandler &/*v*/) override {

  }
  virtual void printName() override {
    // qDebug() << "AddTargetMessage";
  }
};

class RemoveTargetMessage : public Message {
  Q_GADGET
  Q_PROPERTY(int number MEMBER number)
 public:
  int number{0};

  void accept(MessagesHandler &/*v*/) override {

  }
};


class UpdateTargetMessage : public Message {
  Q_GADGET
  Q_PROPERTY(int number MEMBER number)
 public:
  int number{0};

  void accept(MessagesHandler &/*v*/) override {

  }
};
