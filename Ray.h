//
//  Ray.h
//  Ray-tracing-weekend
//
//  Created by Sun, Joy (Agoda) on 2/9/2559 BE.
//  Copyright © 2559 Sun, Joy (Agoda). All rights reserved.
//
#pragma once

#include "Vec3.h"

class Ray{
public:
    
    Ray(){}
    Ray(const Vec3& a, const Vec3& b){A = a; B = b;}
    
    Vec3 origin() const {return A;}
    Vec3 direction() const {return B;}
    
    Vec3 point_at_parameter(float t) {
        return A + B*t;
    }
    
    Vec3 random_point_in_unit_sphere(){
        Vec3 p;
        do{
            p = Vec3(drand48(), drand48(), drand48()) * 2.0 - Vec3(1, 1, 1); // -1 < p < 1
        }while (p.dot(p) >= 1.0);
        
        return p;
    }
    
    Vec3 A;
    Vec3 B;
    
};
