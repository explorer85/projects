#ifndef VISITOR_H
#define VISITOR_H

#include "updatable.h"
class Transform;
class GeoTransform;

// Visitor
class AbstractPoint {
 public:
  virtual ~AbstractPoint() = default;
  virtual void visit(Transform & /*ref*/) {}
  virtual void visit(GeoTransform & /*ref*/) {}
};
// Element
class Element : public Updatable {
 public:
  virtual void accept(AbstractPoint &v) = 0;

 private:
};

#endif  // VISITOR_H
