#pragma once

#include <QObject>
#include <QDebug>
#include <QMetaProperty>


class AddMessage {
  Q_GADGET
  Q_PROPERTY(int id MEMBER id)
  Q_PROPERTY(QString text MEMBER text)
 public:
  int id{0};
  QString text;
};

class RemoveMessage  {
  Q_GADGET
  Q_PROPERTY(int id MEMBER id)
 public:
  int id{0};
};


class UpdateMessage  {
  Q_GADGET
  Q_PROPERTY(int id MEMBER id)
  Q_PROPERTY(QString text MEMBER text)
 public:
  int id{0};
  QString text;

};
