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

class Material; // forward declaration

struct hit_record{
    float t;
    Vec3 p;
    Vec3 normal;
    Material *mat_ptr;
};

class Hitable{
public:
    virtual bool hit(Ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};

class Material
{
public:
    virtual bool scatter(Ray &r_in, hit_record &rec, Vec3 &attenuation, Ray& scattered) const = 0;
    
    Vec3 reflect(Vec3 &v, Vec3 &n) const{
        return v - n * (v.dot(n) * 2);
    }
};

class Lambertian:public Material{
public:
    
    Lambertian(const Vec3& e): albedo(e){}
    virtual bool scatter(Ray &r_in, hit_record &rec, Vec3 &attenuation, Ray& scattered) const{
        Vec3 target = rec.p + rec.normal + r_in.random_point_in_unit_sphere();
        scattered = Ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
    
    Vec3 albedo;
};

class Metal:public Material{
public:
    
    Metal(const Vec3& e, float f):albedo(e){if (f < 1) fuzz = f; else fuzz = 1;}
    
    virtual bool scatter(Ray &r_in, hit_record &rec, Vec3 &attenuation, Ray& scattered) const{
     
        Vec3 v = r_in.direction().unit_vector();
        Vec3 reflected = reflect(v, rec.normal);
        
        scattered = Ray(rec.p, reflected + r_in.random_point_in_unit_sphere()*fuzz);
        attenuation = albedo;
        return (scattered.direction().dot(rec.normal) > 0);
        
    }
    
    
    Vec3 albedo;
    float fuzz;
};

#endif /* Hitable_h */



