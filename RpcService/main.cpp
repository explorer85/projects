#include <rpcservice.h>
#include <QCoreApplication>
#include <QDebug>
#include "TargetMessages.h"

using MessagesHandlerWithMsgs =
    MessagesHandler<std::tuple<AddTargetMessage, RemoveTargetMessage>>;

class TargetMessagesHandler : public MessagesHandlerWithMsgs {
 public:
  void visit(AddTargetMessage* msg) override {
    // AddTargetMessage* addTargetMsg = dynamic_cast<AddTargetMessage*>(msg);
    qDebug() << "handle AddTargetMessage" << msg->name << msg->number;
  };

  void visit(RemoveTargetMessage* msg) override {
    // AddTargetMessage* addTargetMsg = dynamic_cast<AddTargetMessage*>(msg);
    qDebug() << "handle RemoveTargetMessage" << msg->number;
  };
};

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  TargetMessagesHandler targetMessagesHandler;
  RpcService<AddTargetMessage, RemoveTargetMessage> serv{
      &targetMessagesHandler};

  // AddTargetMessage
  {
    AddTargetMessage msg;
    msg.number = 5;
    msg.name = "Garfield";
    auto data = serv.sendMessage(msg);
    serv.onReceiveMessage(data);
  }

  // AddTargetMessage
  {
    RemoveTargetMessage msg;
    msg.number = 10;
    auto data = serv.sendMessage(msg);
    serv.onReceiveMessage(data);
  }

  return a.exec();
}
