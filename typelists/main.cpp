#include <iostream>



//структура для хранения списка типов
struct NullType {
};


template <class T, class U>
struct TypeList
{
  typedef T head;
  typedef U tail;
};


//рекурсивная метафункция для вычисления длины TypeList
template <class TList> struct Lenght;

template <class T, class U>
struct Lenght< TypeList<T, U> >
{
  static const int value = 1 + Lenght<U>::value;
};


template <> struct Lenght<NullType> {
  static const int value = 0;
};


//метафункция для индексированного доступа
template <class TList, unsigned int index> struct TypeAt;



template <class Head, class Tail>
struct TypeAt<TypeList<Head, Tail>, 0> {
  using Result = Head;
};

template <class Head, class Tail, unsigned int i>
struct TypeAt<TypeList<Head, Tail>, i> {
  using Result = typename TypeAt<Tail, i-1>::Result;
};






//реализация списка 3ех типов
using  TreeTypesList = TypeList<std::string, TypeList<float, TypeList<int, NullType>>>;


int main()
{

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





  //////
  TreeTypesListFirst firsttype = "zzzz";
  TreeTypesListSecond secondtype = 5.0;

 // using MyType = TypeList<float, int>::head;
// MyType t = "5";


  return 0;
}
