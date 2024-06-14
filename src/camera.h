#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable.h"
#include "material.h"
#include "rt.h"
#include <omp.h>
#include <vector>

class camera {
public:
  double aspect_ratio = 1.0;
  int image_width = 100;
  int samples_per_pixel = 10;
  int max_depth = 10;

  double vfov = 90.0;
  point_3 lookfrom = point_3(0, 0, 0); // Point camera is looking from
  point_3 lookat = point_3(0, 0, -1);  // Point camera is looking at
  vector_3 vup = vector_3(0, 1, 0);    // Camera-relative "up" direction

  double defocus_angle = 0;
  double focus_dist = 10;

  void render(const hittable &world) {
    initialize();
    std::vector<color> image(image_width * image_height);
    int scanlines_completed = 0;

#pragma omp parallel for schedule(dynamic)
    for (int j = 0; j < image_height; j++) {
      for (int i = 0; i < image_width; i++) {
        color pixel_color(0, 0, 0);
        for (int s = 0; s < samples_per_pixel; s++) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, world, max_depth);
        }
        image[j * image_width + i] = pixel_color;
      }

      // Use atomic operation to safely increment scanlines completed
#pragma omp atomic
      scanlines_completed++;

      // Update the progress bar (only one thread at a time)
#pragma omp critical
      {
        std::clog << "\rscanlines remaining: "
                  << image_height - scanlines_completed << " " << std::flush;
      }
    }
    std::clog << "\rdone                                 \n";

    // Output the image after rendering is complete
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++) {
      for (int i = 0; i < image_width; i++) {
        write_color(std::cout,
                    pixel_samples_scale * image[j * image_width + i]);
      }
    }
  }

private:
  int image_height;
  double pixel_samples_scale;
  point_3 camera_center;
  point_3 pixel00_loc;
  vector_3 pixel_delta_u;
  vector_3 pixel_delta_v;
  vector_3 u, v, w;
  vector_3 defocus_disk_u;
  vector_3 defocus_disk_v;

  void initialize() {
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    camera_center = lookfrom;

    auto theta = degrees_to_radians(vfov);
    auto h = tan(theta / 2);
    auto viewport_h = 2.0 * h * focus_dist;
    auto viewport_w = viewport_h * (double(image_width) / double(image_height));

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    auto viewport_u = viewport_w * u;
    auto viewport_v = viewport_h * -v;

    pixel_delta_u = viewport_u / double(image_width);
    pixel_delta_v = viewport_v / double(image_height);

    auto viewport_upper_left =
        camera_center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + pixel_delta_u / 2 + pixel_delta_v / 2;

    auto defocus_radius =
        focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
  }

  ray get_ray(int i, int j) const {
    auto offset = sample_square();
    auto pixel_sample = pixel00_loc + (pixel_delta_u * (i + offset.x())) +
                        (pixel_delta_v * (j + offset.y()));

    auto ray_origin =
        (defocus_angle <= 0) ? camera_center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;
    return ray(ray_origin, ray_direction);
  }

  vector_3 sample_square() const {
    return vector_3(random_double() - 0.5, random_double() - 0.5, 0);
  }

  point_3 defocus_disk_sample() const {
    auto p = random_in_unit_disk();
    return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
  }

  color ray_color(const ray &r, const hittable &world, int depth) const {
    hit_record rec;

    if (depth <= 0) {
      return color(0, 0, 0);
    }

    if (world.hit(r, interval(0.001, infinity), rec)) {
      ray scattered;
      color attenuation;
      if (rec.mat->scatter(r, rec, attenuation, scattered)) {
        return attenuation * ray_color(scattered, world, depth - 1);
      }
      return color(0, 0, 0);
    }

    vector_3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }
};

#endif
