#ifndef GEOTRANSFORM_H
#define GEOTRANSFORM_H
#include <iostream>
#include <tuple>
#include "updatable.h"
#include "visitor.h"

class GeoTransform : public Element {
 public:
  GeoTransform();
  void accept(AbstractPoint &v) override { v.visit(*this); }

  void setCoords(std::tuple<float, float> &coords) { coords_ = coords; }
  void update() override {
    //преобразование из геодезических координат в декартовы
    int x = bToX(std::get<0>(coords_));
    int y = lToY(std::get<1>(coords_));
    std::cout << "GeoTransform::update " << x << " " << y << std::endl;
  }

 private:
  std::tuple<int, int> coords_;

  int bToX(float B) { return B / 2.0; }
  int lToY(float L) { return L / 2.0; }
};

#endif  // GEOTRANSFORM_H
