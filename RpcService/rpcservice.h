#pragma once

#include <QObject>
#include <QDebug>
#include <QDataStream>
#include <QMetaProperty>
#include <boost/hana.hpp>
namespace hana = boost::hana;






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




//template <class ...Ts>
class RpcService : public QObject
{
  Q_OBJECT
 public:
  explicit RpcService(QObject *parent = nullptr);

//  void registerTypes() {

//  }

  //hana::tuple<...Ts> types;

//static constexpr auto message_types = hana::make_tuple(hana::type_c<AddTargetMessage>, hana::type_c<RemoveTargetMessage>);

  template <class T>
  QByteArray sendMessage(T& msg) {
    int id = genMessageId(T::staticMetaObject.className());
    qDebug() << T::staticMetaObject.className() << id;

    QByteArray result;
    QDataStream dataStream(&result, QIODevice::WriteOnly);
    dataStream << id;


    QMetaObject classMetaObject = T::staticMetaObject;
    QStringList properties;
    for(int i = classMetaObject.propertyOffset(); i < classMetaObject.propertyCount(); ++i) {
      properties << QString::fromLatin1(classMetaObject.property(i).name());
      QVariant prop = classMetaObject.property(i).readOnGadget(&msg);
      dataStream << prop;
    }
    qDebug() << "properties" << properties;




    qDebug() << result;
    return result;
  }
  void onReceiveMessage(QByteArray data) {
    QDataStream dataStream(&data, QIODevice::ReadOnly);
    int id = 0;
    dataStream >> id;
    qDebug() << id;
    //выбрать тип для id

  }
 private:
  int genMessageId(const char* name) {
    int res;

    int i=0;
    char c = '0';
    while (c !='\0') {
      c = name[i];
      res+=(int)c;
      i++;
    }
    return res;
  }

 signals:

};


