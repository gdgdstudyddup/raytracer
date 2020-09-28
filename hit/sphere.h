#if !defined(SPHEREH)
#define SPHEREH
#include "hitable.h"
#include "../glm/glm.hpp"
class sphere : public hitable
{
private:
    /* data */
public:
    sphere(/* args */);
    sphere(vec3 cen, float r);
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    ~sphere();
    vec3 center;
    float radius;
};

sphere::sphere(/* args */)
{
}

sphere::~sphere()
{
}
sphere::sphere(vec3 cen, float r) : center(cen), radius(r)
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
        float temp = (-b - sqrt(b * b - a * c)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(b * b - a * c)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(temp);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}

#endif // SPHEREH
