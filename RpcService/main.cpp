#include <rpcservice.hpp>
#include <QCoreApplication>
#include <QDebug>
#include "Messages.h"

using MessagesTuple = hana::tuple<hana::type<AddMessage>, hana::type<RemoveMessage>>;


class ChatMessagesHandler : public MessagesHandler<MessagesTuple> {
 public:
  void handle(AddMessage* msg) override {
    qDebug() << "handle AddMessage" << msg->id << msg->text;
  };

  void handle(RemoveMessage* msg) override {
    qDebug() << "handle RemoveMessage" << msg->id;
  };
};

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  ChatMessagesHandler chatMessagesHandler;
  RpcService<MessagesTuple> serv{
      &chatMessagesHandler};

  // AddMessage
  {
    AddMessage msg;
    msg.id = 5;
    msg.text = "Hello";
    auto data = serv.sendMessage(msg);
    serv.onReceiveMessage(data);
  }

  // RemoveMessage
  {
    RemoveMessage msg;
    msg.id = 5;
    auto data = serv.sendMessage(msg);
    serv.onReceiveMessage(data);
  }

  return a.exec();
}
