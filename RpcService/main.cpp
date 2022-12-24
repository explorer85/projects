#include <QCoreApplication>
#include <rpcservice.h>
#include "TargetMessages.h"
#include <QDebug>




class TargetMessagesHandler : public MessagesHandler {
 public:
  void handleMessage(Message* msg) override {

    AddTargetMessage* addTargetMsg = dynamic_cast<AddTargetMessage*>(msg);
    qDebug() << "handleMessage" <<  addTargetMsg->name << addTargetMsg->number;

  };



};








int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);


  //RemoveTargetMessage msgremove;
  TargetMessagesHandler targetMessagesHandler;
  RpcService<AddTargetMessage, RemoveTargetMessage> serv{&targetMessagesHandler};
  AddTargetMessage msg;
  msg.number = 5;
  msg.name = "Garfield";
  auto data = serv.sendMessage(msg);
  serv.onReceiveMessage(data);


  //serv.sendMessage(msgremove);

  return a.exec();
}
