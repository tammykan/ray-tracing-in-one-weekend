//
//  Hitable.h
//  ray-tracing-weekend
//
//  Created by Sun, Joy (Agoda) on 2/16/2559 BE.
//  Copyright © 2559 Sun, Joy (Agoda). All rights reserved.
//

#ifndef Hitable_h
#define Hitable_h

#include "Ray.h"

struct hit_record{
    float t;
    Vec3 p;
    Vec3 normal;
};

class Hitable{
public:
    virtual bool hit(Ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};


#endif /* Hitable_h */



