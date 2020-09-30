#if !defined(LAMBERTIANH)
#define LAMBERTIANH
// #include "../hit/hitable.h"
// #include "../glm/glm.hpp"
#include "../ray/ray.h"
#include "./material.h"
#include "../rand48.h"
vec3 random_in_unit_sphere()
{
    vec3 p;
    do
    {
        p = 2.0f * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.x * p.x + p.y * p.y + p.z * p.z >= 1.0);
    return p;
};
class lambertian : public material
{
private:
    /* data */
public:
    lambertian(const vec3&albedo);
    ~lambertian();
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;
    vec3 albedo;
};

lambertian::lambertian(const vec3&albedo):albedo(albedo)
{
}

lambertian::~lambertian()
{
}
bool lambertian::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
{
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    scattered=ray(rec.p,target-rec.p);
    attenuation=albedo;
    return true;
}

#endif // LAMBERTIANH
