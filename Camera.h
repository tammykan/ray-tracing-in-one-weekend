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
    
    Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 vup, float vfov, float aspect){
        
        Vec3 u,v,w;
        
        float theta = vfov*M_PI/180;
        float half_height = tanf(theta/2);
        float half_width = aspect*half_height;
        
        origin = lookFrom;
        // orthogonal basis for camera
        w = (lookFrom - lookAt).unit_vector();
        u = vup.cross(vup, w).unit_vector();
        v = w.cross(w, u);
        
        lower_left_corner = origin - u*half_width - v*half_height-w; // why -w?
        
        horizontal = u * (2*half_width);
        vertical = v * (2*half_height);
    }
    
    Ray get_ray(float u, float v) { return Ray(origin, lower_left_corner + horizontal*u + vertical*v - origin);}
    
    
    
    
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
};


#endif /* Camera_h */
