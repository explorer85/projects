#pragma once

#include <QObject>
#include <QDebug>
#include <QMetaProperty>

#include "Message.h"


class AddTargetMessage {
  Q_GADGET
  Q_PROPERTY(int number MEMBER number)
  Q_PROPERTY(QString name MEMBER name)
 public:
  int number{0};
  QString name;
};

class RemoveTargetMessage  {
  Q_GADGET
  Q_PROPERTY(int number MEMBER number)
 public:
  int number{0};
};


class UpdateTargetMessage  {
  Q_GADGET
  Q_PROPERTY(int number MEMBER number)
 public:
  int number{0};

};
