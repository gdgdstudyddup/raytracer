#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "ray/ray.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;
using namespace glm;
float hit_sphere(const vec3 &center, float radius, const ray &r)
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    return (-b - glm::sqrt(discriminant) )/ (2.0 * a);
}
vec3 color(const ray &r)
{
    float t=hit_sphere(vec3(0, 0, -1), 0.5, r);
    vec3 dir = normalize(r.direction());
    if (t>0.0)
    {
        return 0.5f*(vec3(1.0f)+normalize(r.point_at_parameter(t)-vec3(0.0,0.0,-1.0)));
    }
    t = 0.5 * (dir.y + 1.0);
    return (1.0f - t) * vec3(1.0) + t * vec3(0.5, 0.7, 1.0);
}
int main()
{
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    ofstream fout("result.ppm");
    if (!fout)
    {
        cout << "ppmfile open failed!" << endl;
        return 0;
    }
    int nx = 400;
    int ny = 200;
    fout << "P3\n"
         << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            float b = 0.2;
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);
            int ir = int(255.99 * col.r);
            int ig = int(255.99 * col.g);
            int ib = int(255.99 * col.b);
            fout << ir << " " << ig << " " << ib << "\n";
        }
    }
    getchar();
    return 0;
}