#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <iostream>
#include <tuple>
#include "visitor.h"

class Transform : public Element {
 public:
  Transform();
  void accept(AbstractPoint &v) override {
    //здесь в функции visit устанавливаем переменные класса  трансформации
    //тоесть посетителем устанавливаем переменные класса для трасформации
    //исходя из типа класса для трансформации
    v.visit(*this);
  }
  void setCoords(std::tuple<int, int> &coords) { coords_ = coords; }
  void update() override {
    std::cout << "Transform::update " << std::get<0>(coords_) << " "
              << std::get<1>(coords_) << std::endl;
  }

 private:
  std::tuple<int, int> coords_;
};

#endif  // TRANSFORM_H
