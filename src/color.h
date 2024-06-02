#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"
#include <cmath>
#include <iostream>

using color = vector_3;

inline double linear_to_gamma(double linear_value) {
  if (linear_value > 0) {
    return sqrt(linear_value);
  }
  return 0;
}

void write_color(std::ostream &out, const color &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);

  // Scales [0, 1] value of each color component to [0, 255]
  static const interval intensity(0.000, 0.999);
  int r_byte = int(256 * intensity.clamp(r));
  int g_byte = int(256 * intensity.clamp(g));
  int b_byte = int(256 * intensity.clamp(b));

  // Write the translated [0, 255] value of each color component
  out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}

#endif
