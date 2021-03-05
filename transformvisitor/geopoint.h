#ifndef GEOPOINT_H
#define GEOPOINT_H
#include <tuple>
#include "visitor.h"

class GeoPoint : public AbstractPoint {
 public:
  GeoPoint() {}
  GeoPoint(float B, float L);
  void visit(GeoTransform &ref);

 private:
  std::tuple<float, float> coords_;
};

#endif // GEOPOINT_H
