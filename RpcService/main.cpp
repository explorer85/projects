#include <QCoreApplication>
#include <rpcservice.h>
#include "target_messages.h"
#include <QDebug>











int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);


  //RemoveTargetMessage msgremove;

  RpcService<AddTargetMessage, RemoveTargetMessage> serv;
  AddTargetMessage msg;
  msg.number = 5;
  msg.name = "Garfield";
  auto data = serv.sendMessage(msg);
  serv.onReceiveMessage(data);


  //serv.sendMessage(msgremove);

  return a.exec();
}
