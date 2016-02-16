//
//  Sphere.h
//  ray-tracing-weekend
//
//  Created by Sun, Joy (Agoda) on 2/16/2559 BE.
//  Copyright © 2559 Sun, Joy (Agoda). All rights reserved.
//

#ifndef Sphere_h
#define Sphere_h

#include "Hitable.h"

class Sphere:public Hitable{
public:
    Sphere(){}
    Sphere(Vec3 cent, float r):center(cent),radius(r) {};
    
    virtual bool hit(Ray &ray, float t_min, float t_max, hit_record &rec) const;
    
    Vec3 center;
    float radius;
    
};

bool Sphere::hit(Ray &ray, float t_min, float t_max, hit_record &rec) const{
    float a = ray.direction().dot(ray.direction());
    float b = 2 * ray.direction().dot(ray.origin() - center);
    float c = center.dot(center) - radius*radius;
    
    float discriminant = b*b - 4*a*c;
    
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant)) / (2*a);
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = ray.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / (2*a);
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = ray.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        
    }
    return false;
    
}


#endif /* Sphere_h */
