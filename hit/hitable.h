#ifndef HITABLEH
#define HITABLEH
#include "../ray/ray.h"
// #include "../material/material.h"
// using namespace glm;
class material;
struct hit_record
{
    float t;
    vec3 p;
    vec3 normal;
    material* mat_ptr;
};
class hitable
{
private:
    /* data */
public:
    virtual bool hit(const ray& r,float t_min, float t_max, hit_record& rec) const = 0;
};

#endif //HITABLEH