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

template <unsigned IMAGE_HEIGHT, unsigned IMAGE_WIDTH>
class RayTracer : public TextButton
{
private:
    int samples_per_pixel = 20;
    int max_depth = 5;
    double aspect_ratio = IMAGE_WIDTH / IMAGE_HEIGHT;
        
    sf::Uint32 img[IMAGE_HEIGHT][IMAGE_WIDTH] {};
    sf::Uint32* img_ptr = (sf::Uint32*)img;
public:
    RayTracer() : TextButton{Vector{400, 400}, 50, 50, "R", sf::Color::Blue}
    {
        point3 lookfrom(13,2,3);
        point3 lookat(0,0,0);
        vec3 vup(0,1,0);
        double dist_to_focus = 10.0;
        double aperture = 0.1;

        camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
    }
};