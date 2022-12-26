#include <rpcservice.hpp>
#include <QCoreApplication>
#include <QDebug>
#include "TargetMessages.h"

using MessagesTuple = hana::tuple<hana::type<AddTargetMessage>, hana::type<RemoveTargetMessage>>;


class TargetMessagesHandler : public MessagesHandler<MessagesTuple> {
 public:
  void handle(AddTargetMessage* msg) override {
    qDebug() << "handle AddTargetMessage" << msg->name << msg->number;
  };

  void handle(RemoveTargetMessage* msg) override {
    qDebug() << "handle RemoveTargetMessage" << msg->number;
  };
};

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  TargetMessagesHandler targetMessagesHandler;
  RpcService<MessagesTuple> serv{
      &targetMessagesHandler};

  // AddTargetMessage
  {
    AddTargetMessage msg;
    msg.number = 5;
    msg.name = "Airplane";
    auto data = serv.sendMessage(msg);
    serv.onReceiveMessage(data);
  }

  // RemoveTargetMessage
  {
    RemoveTargetMessage msg;
    msg.number = 10;
    auto data = serv.sendMessage(msg);
    serv.onReceiveMessage(data);
  }

  return a.exec();
}
