#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
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

#endif
