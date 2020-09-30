#if !defined(MATERIALH)
#define MATERIALH
#include "../hit/hitable.h"
#include "../glm/glm.hpp"
using namespace glm;
class material
{
private:
    /* data */
public:
    material(/* args */);
    ~material();
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

material::material(/* args */)
{
}

material::~material()
{
}

#endif // MATERIALH
