#ifndef HITABLEH
#define HITABLEH
#include "../ray/ray.h"
// using namespace glm;
struct hit_record
{
    float t;
    vec3 p;
    vec3 normal;
};
class hitable
{
private:
    /* data */
public:
    virtual bool hit(const ray& r,float t_min, float t_max, hit_record& rec) const = 0;
};

#endif HITABLEH