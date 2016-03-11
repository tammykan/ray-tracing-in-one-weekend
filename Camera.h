//
//  Camera.h
//  ray-tracing-weekend
//
//  Created by Sun, Joy (Agoda) on 2/19/2559 BE.
//  Copyright © 2559 Sun, Joy (Agoda). All rights reserved.
//
#pragma once

#ifndef Camera_h
#define Camera_h

#include "Ray.h"

class Camera{
public:
    
    Vec3 random_in_unit_disk(){
        Vec3 p;
        do{
            p = Vec3(drand48(), drand48(), 0)*2 - Vec3(1, 1, 0);
        }while (p.dot(p) >= 1.0);
        return p;
    }
    
    Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 vup, float vfov, float aspect, float aperture, float focus_disk){
        
        lens_radius = aperture/2;
        
        float theta = vfov*M_PI/180;
        float half_height = tanf(theta/2);
        float half_width = aspect*half_height;
        
        origin = lookFrom;
        // orthogonal basis for camera
        w = (lookFrom - lookAt).unit_vector();
        u = vup.cross(vup, w).unit_vector();
        v = w.cross(w, u);
        
        lower_left_corner = origin - u*(half_width*focus_disk) - v*(half_height*focus_disk)-w*focus_disk; // why -w?
        
        horizontal = u * (2*half_width) * focus_disk;
        vertical = v * (2*half_height) * focus_disk;
    }
    
    Ray get_ray(float s, float t) {
        
        Vec3 rd = random_in_unit_disk()*lens_radius;
        Vec3 offset = u*rd.x() + v*rd.y();
        
        return Ray(origin+offset, lower_left_corner + horizontal*s + vertical*t - origin - offset);
    }
    
    
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    
    Vec3 u,v,w;
    float lens_radius;
};


#endif /* Camera_h */
