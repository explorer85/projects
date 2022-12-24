#include <QCoreApplication>
#include <rpcservice.h>
#include <QDebug>







class AddTargetMessage : public Message {
  Q_GADGET
  Q_PROPERTY(int number MEMBER number)
  Q_PROPERTY(QString name MEMBER name)
 public:
  int number{0};
  QString name;
  virtual void printName() override {
    // qDebug() << "AddTargetMessage";
  }
};

class RemoveTargetMessage : public Message {
  Q_GADGET
  Q_PROPERTY(int number MEMBER number)
 public:
  int number{0};
};




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
