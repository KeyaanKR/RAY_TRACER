#include <iostream>

int main() {

  // image dimensions
  int w = 256;
  int h = 256;

  // render image
  std::cout << "P3\n" << w << " " << h << "\n255\n";

  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      float r = float(i) / float(w - 1);
      float g = float(j) / float(h - 1);
      float b = 0.0;

      int ir = int(255.99 * r);
      int ig = int(255.99 * g);
      int ib = int(255.99 * b);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
