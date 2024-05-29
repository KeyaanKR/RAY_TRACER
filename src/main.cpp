#include "hittable.h"
#include "hittable_list.h"
#include "rt.h"
#include "sphere.h"
#include <iostream>

color ray_color(const ray &r, const hittable &world) {
  hit_record rec;
  if (world.hit(r, interval(0, infinity), rec)) {
    return 0.5 * (rec.normal + color(1, 1, 1));
  }

  vector_3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {

  auto aspect_ratio = 16.0 / 9.0;

  // image dimensions
  int w = 400;

  // calculate image height based on aspect and ensure it is at least 1
  int h = int(w / aspect_ratio);
  h = (h < 1) ? 1 : h;

  // define the world
  hittable_list world;
  world.add(make_shared<sphere>(point_3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point_3(0, -100.5, -1), 100));

  // camera parameters
  auto focal_l = 1.0;
  auto viewport_h = 2.0;
  auto viewport_w = aspect_ratio * viewport_h;
  auto camera_center = point_3(0, 0, 0);

  // calculate basis vectors
  auto viewport_u = vector_3(viewport_w, 0, 0);
  auto viewport_v = vector_3(0, -viewport_h, 0);

  // calculate the horizontal and vertical delta vectors
  auto pixel_delta_u = viewport_u / double(w);
  auto pixel_delta_v = viewport_v / double(h);

  // calculate the upper left corner of the viewport
  auto viewport_upper_left =
      camera_center - viewport_u / 2 - viewport_v / 2 - vector_3(0, 0, focal_l);
  auto pixel00_loc =
      viewport_upper_left + pixel_delta_u / 2 + pixel_delta_v / 2;

  // render image
  std::cout << "P3\n" << w << " " << h << "\n255\n";

  for (int j = 0; j < h; j++) {
    std::clog << "\rscanlines remaining: " << h - j << " " << std::flush;
    for (int i = 0; i < w; i++) {
      auto pixel_center = pixel00_loc + i * pixel_delta_u + j * pixel_delta_v;
      auto ray_dir = pixel_center - camera_center;
      ray r(camera_center, ray_dir);
      color pixel_color = ray_color(r, world);
      write_color(std::cout, pixel_color);
    }
  }

  std::clog << "\rdone                                 \n";
}
