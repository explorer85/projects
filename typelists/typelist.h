#pragma once

#include <type_traits>


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


//метафункция поиска типа
template <class TList, class T> struct IndexOf;

template <class T>
struct IndexOf<NullType, T> {
  static const int value = -1;
};


template <class T, class Tail>
struct IndexOf<TypeList<T, Tail>, T> {
  static const int value = 0;
};


template <class Head, class Tail, class T>
struct IndexOf<TypeList<Head, Tail>, T> {
 private:
  static const int temp = IndexOf<Tail, T>::value;
 public:
  static const int value = temp == -1 ? -1 : 1 + temp;
};


