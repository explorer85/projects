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





class RpcService : public QObject
{
  Q_OBJECT
 public:
  explicit RpcService(QObject *parent = nullptr) : QObject(parent)
  {

  }
template <class ...Ts>
  void registerTypes() {
  hana::tuple<Ts...> typesValues;
  auto tupes = hana::tuple_t<Ts...>;

  hana::for_each(typesValues, [&](auto member) {
    //qDebug() << member.number;
    qDebug() << member.staticMetaObject.className();
  });


  auto values = hana::transform(tupes, [](auto t) {
    return hana::just(t);
  });


  auto Ptrs = hana::transform(tupes, [](auto t) {
    return hana::traits::add_pointer(t);
  });

  qDebug() << "------------";




  hana::for_each(tupes, [&](auto t) {

    typename decltype(t)::type  vv;
    qDebug() << vv.staticMetaObject.className();
    qDebug() <<  (t == hana::type_c<RemoveTargetMessage>);



  hana::type<RemoveTargetMessage>{};

  //  hana::type_c<RemoveTargetMessage>::is_valid();

   // int a = t;
  // using T = t::type;

   // t == RemoveTargetMessage;
   // hana::type<T>
  //  qDebug() << t;
    //qDebug() << member.number;
   // qDebug() << member::staticMetaObject.className();
  });




  auto resRemove = hana::find(tupes, hana::type_c<RemoveTargetMessage>);
  auto resAdd = hana::find(tupes, hana::type_c<AddTargetMessage>);



  qDebug() <<  (resRemove == hana::just(hana::type_c<RemoveTargetMessage>));
   qDebug() <<  (resAdd == hana::just(hana::type_c<RemoveTargetMessage>));


  }




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
    int res = 0;

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


