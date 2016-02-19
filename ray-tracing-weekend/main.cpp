//
//  main.cpp
//  Ray-tracing-weekend
//
//  Created by Sun, Joy (Agoda) on 2/9/2559 BE.
//  Copyright © 2559 Sun, Joy (Agoda). All rights reserved.
//

#include <iostream>
#include "Camera.h"
#include "Sphere.h"
#include "HitableList.h"
#include "float.h"

Vec3 color(Ray &ray, Hitable *world){
    
    hit_record rec;
    
    if (world->hit(ray, 0, MAXFLOAT, rec)) { // hit: visualize normal
        return Vec3(rec.normal.x() +1, rec.normal.y()+1, rec.normal.z()+1) * 0.5;
    }
    else{ // not hit, blue to white blend
        Vec3 unit_direction = ray.direction().unit_vector();
        float t = 0.5 * (unit_direction.y() + 1.0); // -1 < y < 1 --> 0 < y+1 < 2 --> 0 < t < 1
        return Vec3(1, 1, 1) * (1.0-t) + Vec3(0.5, 0.7, 1.0) * t;
    }
    
}


int main(int argc, const char * argv[]) {
 
    int nx = 200;
    int ny = 100;
    int ns = 100;
    
    
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    
    Camera cam;
    
    Hitable *list[2];
    list[0] = new Sphere(Vec3(0,0,-1),0.5);
    list[1] = new Sphere(Vec3(0, -100.5, -1),100);
    Hitable *world = new HitableList(list,2);
    
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vec3 col(0,0,0);
            
            for (int s = 0; s < ns; s++) {
                // anti-aliasing: take ns samples in each pixel and average the color
                float u = float(i + drand48())/float(nx);
                float v = float(j + drand48())/float(ny);
                Ray ray = cam.get_ray(u, v);
                
                col = col + color(ray, world);
            }
            
            col = col / ns;

            
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    
}
