#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include <iostream>

class ray {
public:
  ray() {}
  ray(const point_3 &origin, const vector_3 &direction)
      : orig(origin), dir(direction) {}

  const point_3 &origin() const { return orig; }
  const vector_3 &direction() const { return dir; }

  point_3 at(double t) const { return orig + t * dir; }

private:
  point_3 orig;
  vector_3 dir;
};

#endif
