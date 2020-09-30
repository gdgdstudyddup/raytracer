#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "ray/ray.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "hit/hitable_list.h"
#include "hit/sphere.h"
#include "camera/camera.h"
#include "material/lambertian.h"
#include "rand48.h"

using namespace std;
using namespace glm;
vec3 color(const ray &r, hitable *world, int depth)
{
    hit_record rec;
    if (world->hit(r, 0.0001, 1000.0, rec))
    {
        // return 0.5f * (rec.normal + 1.0f);
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
            return vec3(0);
    }
    else
    {
        vec3 dir = normalize(r.direction());
        float t = 0.5 * (dir.y + 1.0);
        return (1.0f - t) * vec3(1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}
int main()
{
    int nx = 200;
    int ny = 100;
    int ns = 100;
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    camera cam(vec3(-2, 1, 1), vec3(0, 0, -1), vec3(0, 1, 0), 90, float(nx) / float(ny));
    hitable *list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(1, 0, 0)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0, 0, 1)));
    hitable *world = new hitable_list(list, 2);
    ofstream fout("result.ppm");
    if (!fout)
    {
        cout << "ppmfile open failed!" << endl;
        return 0;
    }
    fout << "P3\n"
         << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world,0);
            }
            col /= float(ns);
            // float u = float(i) / float(nx);
            // float v = float(j) / float(ny);
            // float b = 0.2;
            // ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            // // vec3 col = color(r);
            // vec3 p=r.point_at_parameter(2.0);
            // vec3 col=color(r,world);
            int ir = int(255.99 * col.r);
            int ig = int(255.99 * col.g);
            int ib = int(255.99 * col.b);
            fout << ir << " " << ig << " " << ib << "\n";
        }
    }
    getchar();
    return 0;
}