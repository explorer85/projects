#include "point.h"
#include "transform.h"

Point::Point()
{

}

Point::Point(int x, int y) : coords_(std::make_tuple(x, y)) {}

void Point::visit(Transform &ref) { ref.setCoords(coords_); }
