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
    
    bool refract(Vec3 &v, Vec3 &n, float ni_over_nt, Vec3 &refracted) const{
        Vec3 uv = v.unit_vector();
        Vec3 un = n.unit_vector();
        float dt = uv.dot(un);
        
        float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt*dt);
        if (discriminant > 0) {
            refracted = (uv - n*dt)*ni_over_nt - n*sqrt(discriminant);
            return true;
        }
        else
            return false;
    }
    
    float schlick(float cosine, float ref_idx) const{
        float r0 = (1 - ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0+ (1-r0)*pow((1-cosine), 5);
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

class Dielectric:public Material{
public:
    
    Dielectric(float ri): ref_idx(ri){}
    
    virtual bool scatter(Ray &r_in, hit_record &rec, Vec3 &attenuation, Ray& scattered) const{
     
        Vec3 outward_normal;
        Vec3 r_in_direction = r_in.direction();
        Vec3 reflected = reflect(r_in_direction, rec.normal);
        
        float ni_over_nt;
        attenuation = Vec3(1.0, 1.0, 1.0);
        Vec3 refracted;
        float reflect_prob;;
        float cosine;
        
        if (r_in_direction.dot(rec.normal) > 0) {
            outward_normal = rec.normal * -1;
            ni_over_nt = ref_idx;
            
            float a = r_in_direction.dot(rec.normal) * ref_idx;
            float b = r_in_direction.length();
            cosine = a/b;
            
        }else{
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            float a = r_in_direction.dot(rec.normal) * ref_idx;
            float b = r_in_direction.length();
            cosine = -a/b;
        }
        
        if (refract(r_in_direction, outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        }else{
            reflect_prob = 1.0;
        }
        
        if (drand48() < reflect_prob) {
            scattered = Ray(rec.p, reflected);
        }
        else{
            scattered = Ray(rec.p, refracted);
        }
        
        return true;
        
    }
    
    
    
    float ref_idx;
};

#endif /* Hitable_h */



