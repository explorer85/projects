#ifndef POINT_H
#define POINT_H
#include <tuple>
#include "visitor.h"

class Point : public AbstractPoint {
 public:
  Point();
  Point(int x, int y);
  void visit(Transform &ref) override;

 private:
  std::tuple<int, int> coords_;
};

#endif // POINT_H
