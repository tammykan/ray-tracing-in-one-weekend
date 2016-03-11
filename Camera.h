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
    
    Camera(float vfov, float aspect){
        
        float theta = vfov*M_PI/180;
        float half_height = tanf(theta/2);
        float half_width = aspect*half_height;
        lower_left_corner = Vec3(-half_width, -half_height, -1);
        origin = Vec3(0, 0, 0);
        horizontal = Vec3(2*half_width, 0, 0);
        vertical = Vec3(0, 2*half_height, 0);
    }
    
    Ray get_ray(float u, float v) { return Ray(origin, lower_left_corner + horizontal*u + vertical*v - origin);}
    
    
    
    
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
};


#endif /* Camera_h */
