#pragma once

#include "Message.h"


template <typename T>
class MessagesHandler {

};

template <typename T1, typename... Ts>
class MessagesHandler<std::tuple<T1, Ts...>> : public  MessagesHandler<std::tuple<Ts...>>  {
 public:
  using MessagesHandler<std::tuple<Ts...>>::visit;
  virtual void visit(T1 */*msg*/) {

  };

};

template <>
class MessagesHandler<std::tuple<>> {
 public:
  virtual void visit(void*) {


  };
};

