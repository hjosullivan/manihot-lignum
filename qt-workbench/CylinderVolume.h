#ifndef CYLINDER_H
#define CYLINDER_H

#include <Point.h>
#include <PositionVector.h>
//#include <Volume.h>

using namespace cxxadt;

class CylinderVolume /*: public Volume*/ {
 public :
  CylinderVolume(double radius, double height, Point point, PositionVector direction, int detail);
  ~CylinderVolume();
  int isPointInside(Point point);

 private:
  double radius;
  double real_radius;
  double height;
  Point point;
  Point origo;
  PositionVector direction;
  PositionVector plane;
  double c;
  double a;
};

#endif
