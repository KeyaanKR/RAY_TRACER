#ifndef HITTABLE_H
#define HITTABLE_H

#include "interval.h"
#include "ray.h"
#include <memory>

class material;

class hit_record {
public:
  point_3 p;
  vector_3 normal;
  std::shared_ptr<material> mat;
  double t;

  bool front_face;
  void set_face_normal(const ray &r, const vector_3 &outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;
};

#endif
