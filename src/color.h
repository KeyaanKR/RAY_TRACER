#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vector_3;

void write_color(std::ostream &out, const color &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // Scales [0, 1] value of each color component to [0, 255]
  int r_byte = int(255.999 * r);
  int g_byte = int(255.999 * g);
  int b_byte = int(255.999 * b);

  // Write the translated [0, 255] value of each color component
  out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}

#endif
