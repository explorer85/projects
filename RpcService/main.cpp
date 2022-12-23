#include <QCoreApplication>
#include <rpcservice.h>
#include <QDebug>







int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  AddTargetMessage msg;
  msg.name = "Garfield";
 // msg->printName();
  RemoveTargetMessage msgremove;
 // qDebug() << msg->staticMetaObject.de->className();
 // qDebug() << AddTargetMessage::staticMetaObject.className();
//  qDebug() << RemoveTargetMessage::staticMetaObject.className();



  RpcService serv;
  auto data = serv.sendMessage(msg);
  serv.onReceiveMessage(data);


  //serv.sendMessage(msgremove);

  return a.exec();
}
