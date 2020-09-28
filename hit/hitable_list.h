#if !defined(HITABLE_LISTH)
#define HITABLE_LISTH
#include "hitable.h"
class hitable_list:public hitable
{
private:
    /* data */
public:
    hitable_list(/* args */);
    hitable_list(hitable**l,int n);
    ~hitable_list();
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    hitable** list;
    int list_size;
};

hitable_list::hitable_list(/* args */)
{
}
hitable_list::hitable_list(hitable**l,int n):list(l),list_size(n)
{
}
hitable_list::~hitable_list()
{
}
bool hitable_list::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything=false;
    double closet_so_far=t_max;
    for (int i = 0; i < list_size; i++)
    {
        if(list[i]->hit(r,t_min,closet_so_far,temp_rec))
        {
            hit_anything=true;
            closet_so_far=temp_rec.t;
            rec=temp_rec;
        }
    }
    return hit_anything;
}

#endif // HITABLE_LISTH
