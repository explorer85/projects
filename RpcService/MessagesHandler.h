#pragma once

#include <QDebug>
#include <tuple>
#include <boost/hana.hpp>

namespace hana = boost::hana;

template <typename T>
class MessagesHandler {

};

template <typename T1, typename... Ts>
class MessagesHandler<hana::tuple<T1, Ts...>> : public  MessagesHandler<hana::tuple<Ts...>>  {
 public:
  using MessagesHandler<hana::tuple<Ts...>>::handle;
  virtual void handle(typename T1::type* /*msg*/) {
  };

};

template <>
class MessagesHandler<hana::tuple<>> {
 public:
  virtual void handle(void*) {


  };
};

