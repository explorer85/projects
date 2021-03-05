#include "geopoint.h"
#include "geotransform.h"

GeoPoint::GeoPoint(float B, float L) : coords_(std::make_tuple(B, L)) {}

void GeoPoint::visit(GeoTransform &ref) { ref.setCoords(coords_); }
