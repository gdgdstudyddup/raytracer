#if !defined(SPHEREH)
#define SPHEREH
#include "hitable.h"
#include "../glm/glm.hpp"
#include "../material/material.h"
using namespace glm;
class sphere : public hitable
{
private:
    /* data */
public:
    sphere(/* args */);
    sphere(vec3 cen, float r, material*mat);
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    ~sphere();
    vec3 center;
    float radius;
    material *mat;
};

sphere::sphere(/* args */)
{
}

sphere::~sphere()
{
}
sphere::sphere(vec3 cen, float r, material*mat) : center(cen), radius(r), mat(mat)
{
}
bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        float temp = (-b - glm::sqrt(b * b - a * c)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr=mat;
            return true;
        }
        temp = (-b + glm::sqrt(b * b - a * c)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr=mat;
            return true;
        }
    }
    return false;
}

#endif // SPHEREH
