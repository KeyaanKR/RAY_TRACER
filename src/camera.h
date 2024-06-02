#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "rt.h"

class camera {
public:
  double aspect_ratio = 1.0;
  int image_width = 100;
  int samples_per_pixel = 10;
  int max_depth = 10;

  void render(const hittable &world) {
    initialize();
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++) {
      std::clog << "\rscanlines remaining: " << image_height - j << " "
                << std::flush;
      for (int i = 0; i < image_width; i++) {
        color pixel_color(0, 0, 0);
        for (int s = 0; s < samples_per_pixel; s++) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, world, 50);
        }
        write_color(std::cout, pixel_samples_scale * pixel_color);
      }
    }
    std::clog << "\rdone                                 \n";
  }

private:
  int image_height;
  double pixel_samples_scale;
  point_3 camera_center;
  point_3 pixel00_loc;
  vector_3 pixel_delta_u;
  vector_3 pixel_delta_v;

  void initialize() {
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    camera_center = point_3(0, 0, 0);

    auto focal_l = 1.0;
    auto viewport_h = 2.0;
    auto viewport_w = viewport_h * (double(image_width) / double(image_height));

    auto viewport_u = vector_3(viewport_w, 0, 0);
    auto viewport_v = vector_3(0, -viewport_h, 0);

    pixel_delta_u = viewport_u / double(image_width);
    pixel_delta_v = viewport_v / double(image_height);

    auto viewport_upper_left = camera_center - viewport_u / 2 - viewport_v / 2 -
                               vector_3(0, 0, focal_l);
    pixel00_loc = viewport_upper_left + pixel_delta_u / 2 + pixel_delta_v / 2;
  }

  ray get_ray(int i, int j) const {
    auto offset = sample_square();
    auto pixel_sample = pixel00_loc + (pixel_delta_u * (i + offset.x())) +
                        (pixel_delta_v * (j + offset.y()));

    auto ray_origin = camera_center;
    auto ray_direction = pixel_sample - camera_center;
    return ray(ray_origin, ray_direction);
  }

  vector_3 sample_square() const {
    return vector_3(random_double() - 0.5, random_double() - 0.5, 0);
  }

  color ray_color(const ray &r, const hittable &world, int depth) const {
    hit_record rec;

    if (depth <= 0) {
      return color(0, 0, 0);
    }

    if (world.hit(r, interval(0.001, infinity), rec)) {
      // return 0.5 * (rec.normal + color(1, 1, 1));
      vector_3 direction = rec.normal + random_unit_vector();
      return 0.5 * ray_color(ray(rec.p, direction), world, depth - 1);
    }

    vector_3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }
};

#endif
