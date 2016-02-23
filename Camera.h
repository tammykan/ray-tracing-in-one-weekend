//
//  Camera.h
//  ray-tracing-weekend
//
//  Created by Sun, Joy (Agoda) on 2/19/2559 BE.
//  Copyright © 2559 Sun, Joy (Agoda). All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "Ray.h"

class Camera{
public:
    
    Camera(){
        origin = Vec3(0,0,0);
        lower_left_corner = Vec3(-2,-1,-1);
        horizontal = Vec3(4,0,0);
        vertical = Vec3(0,2,0);
        
    }
    
    Ray get_ray(float u, float v) { return Ray(origin, lower_left_corner + horizontal*u + vertical*v - origin);}
    
    
    
    
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
};


#endif /* Camera_h */
