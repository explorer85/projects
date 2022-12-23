#include <iostream>

//#include <ext/typelist.h>
#include "typelist.h"
#include "visitor.h"





//реализация списка 3ех типов
using  TreeTypesList = TypeList<std::string, TypeList<float, TypeList<int, NullType>>>;






int main()
{
//////////////////////TYPEELISTS
  //получаем первый тип
  using TreeTypesListFirst = TreeTypesList::head;
  //получаем второй тип
  using TreeTypesListSecond = TreeTypesList::tail::head;
  //получаем третий тип
  using TreeTypesListTree = TreeTypesList::tail::tail;

  TreeTypesList tt;

   //количество элементов TypeList
  int val = Lenght<TreeTypesList>::value;

  //обращение по индексу к второиу типу
  using Two = TypeAt<TreeTypesList, 1>::Result;
 // Two two = "5";

  //поиск элемента
  int index = IndexOf<TreeTypesList, const float>::value;
  // Two two = "5";





  //////
  TreeTypesListFirst firsttype = "zzzz";
  TreeTypesListSecond secondtype = 5.0;



///////////VISITOR
//  Visitor<int> vv;

 // Visitor<std::tuple<AddTargetMessage, RemoveTargetMessage>>  v;

  AddTargetMessage msg;
  RemoveTargetMessage msgremove;
  //v.visit(msg);
  MessagesVisitor mv;
  mv.visit(msg);
  mv.visit(msgremove);

 //VisitorWithMsgs msgsv;
 //msgsv.visit(msgremove);



//  MessageSender<AddTargetMessage, RemoveTargetMessage> msgSender;
//  AddTargetMessage msgAdd;
//  RemoveTargetMessage msgRemove;
//  msgSender.sendMessage(&msgAdd);
//  msgSender.sendMessage(&msgRemove);


  return 0;
}
