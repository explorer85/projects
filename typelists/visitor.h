#pragma once
#include <ext/typelist.h>
#include <tuple>
#include <iostream>
#include <type_traits>



//__gnu_cxx::typelist::chain
//_GLIBCXX_TYPELIST_CHAIN3

class Message;
class AddTargetMessage;
class RemoveTargetMessage;



template <typename T>
class Visitor {

};


template <typename T1, typename... Ts>
class Visitor<std::tuple<T1, Ts...>> : public  Visitor<std::tuple<Ts...>>  {
 public:
  virtual void visit(T1 &msg) {
    this->visit(static_cast<Message&>(msg));

    //получаем число для каждого имени типа
   // const int messageId = sizeof... (Ts);
    //msg.serialize();


  };

};

template <>
class Visitor<std::tuple<>> {
  virtual void visit(Message&) {


  };
};


class MessagesVisitor;

class Message {
 public:
  virtual void serialize() {}
  virtual void accept(MessagesVisitor &v) = 0;

};

class AddTargetMessage : public Message {
 public:
  int number;
  void accept(MessagesVisitor &v);
};

class RemoveTargetMessage : public Message {
 public:
  int number;
  //void accept(Visitor &v) {
  //  v.visit(this);
  //}
};



using VisitorWithMsgs = Visitor<std::tuple<AddTargetMessage, RemoveTargetMessage>>;

class MessagesVisitor : public VisitorWithMsgs {

};




//class MessageSerializeVisitor : public  Visitor {
// public:
//  void visit(AddTargetMessage* msg) override {
//    std::cout << "serialize AddTargetMessage" << std::endl;
//  }
//  void visit(RemoveTargetMessage* msg) override {
//    std::cout << "serialize RemoveTargetMessage" << std::endl;
//  }
//};




//template <typename ...T>
class MessageSender {
 public:
//  void sendMessage(Message *msg) {
//    msg->accept(serializeVisitor_);
//  }
 private:
  //MessageSerializeVisitor serializeVisitor_;
};
