#ifndef VECTOR3_H
#define VECTOR3_H

#include "random.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

class vector_3 {
public:
  double e[3];
  vector_3() : e{0, 0, 0} {}
  vector_3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  vector_3 operator-() const { return vector_3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  vector_3 &operator+=(const vector_3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  vector_3 &operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  vector_3 &operator/=(const double t) { return *this *= 1 / t; }

  double length() const { return sqrt(length_squared()); }

  double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  bool near_zero() const {
    auto s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
  }

  static vector_3 random() {
    return vector_3(random_double(), random_double(), random_double());
  }

  static vector_3 random(double min, double max) {
    return vector_3(random_double(min, max), random_double(min, max),
                    random_double(min, max));
  }
};

using point_3 = vector_3;

// utility functions

inline std::ostream &operator<<(std::ostream &out, const vector_3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vector_3 operator+(const vector_3 &u, const vector_3 &v) {
  return vector_3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vector_3 operator-(const vector_3 &u, const vector_3 &v) {
  return vector_3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vector_3 operator*(const vector_3 &u, const vector_3 &v) {
  return vector_3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vector_3 operator*(double t, const vector_3 &v) {
  return vector_3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vector_3 operator*(const vector_3 &v, double t) { return t * v; }

inline vector_3 operator/(vector_3 v, double t) { return (1 / t) * v; }

inline double dot(const vector_3 &u, const vector_3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vector_3 cross(const vector_3 &u, const vector_3 &v) {
  return vector_3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                  u.e[2] * v.e[0] - u.e[0] * v.e[2],
                  u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vector_3 unit_vector(vector_3 v) { return v / v.length(); }

inline vector_3 random_unit_vector() {
  while (true) {
    auto p = vector_3::random(-1, 1);
    auto length_sq = p.length_squared();
    if (1e-160 < length_sq && length_sq <= 1)
      return p / sqrt(length_sq);
  }
}

inline vector_3 random_on_hemisphere(const vector_3 &normal) {
  vector_3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0)
    return on_unit_sphere;
  else
    return -on_unit_sphere;
}

inline vector_3 reflect(const vector_3 &v, const vector_3 &n) {
  return v - 2 * dot(v, n) * n;
}

#endif
