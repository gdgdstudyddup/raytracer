#if !defined(METALH)
#define METALH
#include "../ray/ray.h"
#include "./material.h"
#include "../rand48.h"
vec3 random_in_unit_spherem()
{
    vec3 p;
    do
    {
        p = 2.0f * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.x * p.x + p.y * p.y + p.z * p.z >= 1.0);
    return p;
};
class metal:public material
{
private:
    /* data */
public:
    metal(const vec3& albedo,float f);
    ~metal();
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const;
    vec3 albedo;
    float fuzz;
};

metal::metal(const vec3& a,float f):albedo(a),fuzz(f)
{
}

metal::~metal()
{
}
bool metal::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
{
    refract(r_in.direction(),rec.normal,0.4f);
    vec3 reflected=reflect(normalize(r_in.direction()),rec.normal);
    scattered=ray(rec.p,reflected+fuzz* random_in_unit_spherem());
    attenuation=albedo;
    return (dot(normalize(scattered.direction()),rec.normal)>0);
}


#endif // METALH
