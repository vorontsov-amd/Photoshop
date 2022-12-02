#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "raytrace/vector.hpp"
#include "raytrace/ray.hpp"
#include "raytrace/hittable_list.hpp"
#include "raytrace/utility.hpp"
#include "raytrace/sphere.hpp"
#include "raytrace/camera.hpp"
#include "raytrace/material.hpp"
#include "button.hpp"


using Vector = vec3;
using Color = vec3;
using color = Color;


void write_color(std::ostream &out, color pixel_color, int samples_per_pixel, sf::Uint32& pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    int ir = static_cast<int>(256 * clamp(r, 0.0, 0.999));
    int ig = static_cast<int>(256 * clamp(g, 0.0, 0.999));
    int ib = static_cast<int>(256 * clamp(b, 0.0, 0.999));
    
    out << ir << ' ' << ig << ' ' << ib << '\n';
    
    pixel = ((0xff << 24) | (ib << 16) | (ig << 8) | ir);
}


color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;
    
    if (depth <= 0)
        return color(0,0,0);
    
    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}





//template <unsigned IMAGE_HEIGHT, unsigned IMAGE_WIDTH>
class RayTracer : public TextButton
{
private:
    #define IMAGE_HEIGHT  900
    #define IMAGE_WIDTH  1600
    
    int samples_per_pixel = 20;
    int max_depth = 20;
    double aspect_ratio = double(IMAGE_WIDTH) / IMAGE_HEIGHT;

    camera* cam;
    hittable_list* world = nullptr;
        
    sf::Uint32 img[IMAGE_HEIGHT][IMAGE_WIDTH] {};
    sf::Uint32* img_ptr = (sf::Uint32*)img;
public:
    RayTracer() : TextButton{Vector{400, 400}, 50, 50, "R", sf::Color::Blue}
    {
        point3 lookfrom(-2,2,1);
        point3 lookat(0,0,-1);
        vec3 vup(0,1,0);
        double dist_to_focus = (lookfrom - lookat).length();
        double aperture = 2.0;



        cam = new camera(lookfrom, lookat, vec3(0,1,0), 90, aspect_ratio, 0.2, dist_to_focus);
        world = new hittable_list;


        auto material_ground = make_shared<lambertian>(Color(0.8, 0.8, 0.0));
        auto material_center = make_shared<lambertian>(Color(0.1, 0.2, 0.5));
        auto material_left   = make_shared<dielectric>(1.5);
        auto material_right  = make_shared<metal>(Color(0.8, 0.6, 0.2), 0.0);

        world->add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
        world->add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
        world->add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
        world->add(make_shared<sphere>(point3(-1.0,    0.0, -1.0), -0.45, material_left));
        world->add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    }

    bool mousePressed(sf::Vector2i position) {
        if (contains(position.x, position.y)) {
            std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

            for (int j = IMAGE_HEIGHT-1; j >= 0; --j) {
                std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
                for (int i = 0; i < IMAGE_WIDTH; ++i) {
                    Color pixel_color(0, 0, 0);
                    for (int s = 0; s < samples_per_pixel; ++s) {
                        auto u = (i + random_double()) / (IMAGE_WIDTH-1);
                        auto v = (j + random_double()) / (IMAGE_HEIGHT-1);
                        ray r = cam->get_ray(u, v);
                        pixel_color += ray_color(r, *world, max_depth);
                    }
                    write_color(std::cout, pixel_color, samples_per_pixel, img[IMAGE_HEIGHT - j - 1][i]);
                }
            } 

            return true;
        }
        return false;
    }
};