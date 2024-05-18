#include "color.h"
#include "vec3.h"
#include <iostream>

int main() {

  // image dimensions
  int w = 256;
  int h = 256;

  // render image
  std::cout << "P3\n" << w << " " << h << "\n255\n";

  for (int j = 0; j < h; j++) {
    std::clog << "\rscanlines remaining: " << h - j << " " << std::flush;
    for (int i = 0; i < w; i++) {
      auto pixel_color = color(double(i) / (w - 1), double(j) / (h - 1), 0);
      write_color(std::cout, pixel_color);
    }
  }

  std::clog << "\rdone                                 \n";
}
