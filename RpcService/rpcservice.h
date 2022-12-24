#pragma once

#include <QObject>
#include <QDebug>
#include <QDataStream>
#include <QMetaProperty>
#include <boost/hana.hpp>
namespace hana = boost::hana;








template <class ...Ts>
class RpcService
{
 public:
  explicit RpcService() {
    // qDebug() << sizeof...(types);

    //цикл п осписку типов
    hana::for_each(types_, [&](auto t) {
     // typename decltype(t)::type vv;
    //  qDebug() << vv.staticMetaObject.className();
     // qDebug() << (t == hana::type_c<RemoveTargetMessage>);
   //   qDebug() << genMessageId(decltype(t)::type::staticMetaObject.className());
    });

  }


  hana::tuple<hana::type<Ts>...> types_;
  hana::tuple<Ts...> typesValues_;




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

    hana::for_each(types_, [&](auto t) {
      int typeIntId =  genMessageId(decltype(t)::type::staticMetaObject.className());
      if (typeIntId == id) {
        typename decltype(t)::type vv;

        QMetaObject classMetaObject = decltype(t)::type::staticMetaObject;
        QStringList properties;
        for(int i = classMetaObject.propertyOffset(); i < classMetaObject.propertyCount(); ++i) {
          properties << QString::fromLatin1(classMetaObject.property(i).name());
          QVariant prop;
          dataStream >> prop;
          classMetaObject.property(i).writeOnGadget(&vv, prop);
        }
        qDebug() << vv.staticMetaObject.className() << vv.number;
      }
    });



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

 private:



};






//void registerTypes() {
//  auto tupes = hana::tuple_t<Ts...>;

//  hana::for_each(typesValues_, [&](auto member) {
//    //qDebug() << member.number;
//    qDebug() << member.staticMetaObject.className();
//  });


//  auto values = hana::transform(tupes, [](auto t) {
//    return hana::just(t);
//  });


//  auto Ptrs = hana::transform(tupes, [](auto t) {
//    return hana::traits::add_pointer(t);
//  });

//  qDebug() << "------------";




//  hana::for_each(tupes, [&](auto t) {

//    typename decltype(t)::type  vv;
//    qDebug() << vv.staticMetaObject.className();
//    qDebug() <<  (t == hana::type_c<RemoveTargetMessage>);



//    hana::type<RemoveTargetMessage>{};

//    //  hana::type_c<RemoveTargetMessage>::is_valid();

//    // int a = t;
//    // using T = t::type;

//    // t == RemoveTargetMessage;
//    // hana::type<T>
//    //  qDebug() << t;
//    //qDebug() << member.number;
//    // qDebug() << member::staticMetaObject.className();
//  }
//                 );




//  auto resRemove = hana::find(tupes, hana::type_c<RemoveTargetMessage>);
//  auto resAdd = hana::find(tupes, hana::type_c<AddTargetMessage>);



//  qDebug() <<  (resRemove == hana::just(hana::type_c<RemoveTargetMessage>));
//  qDebug() <<  (resAdd == hana::just(hana::type_c<RemoveTargetMessage>));


//}




//////////////////////////

////преобразованиеи в список типов
//auto to_types = [](auto vals) {
//  namespace hana = boost::hana;
//  return decltype(hana::transform(
//      hana::to_tuple(std::declval<decltype(vals)>()), hana::typeid_)){};
//};

//// types_ = to_types(typesValues_);





