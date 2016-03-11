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


Vec3 random_point_in_unit_sphere(){
    Vec3 p;
    do{
        p = Vec3(drand48(), drand48(), drand48()) * 2.0 - Vec3(1, 1, 1); // -1 < p < 1
    }while (p.dot(p) >= 1.0);
    
    return p;
}


Vec3 color(Ray &ray, Hitable *world, int depth){
    
    hit_record rec;
    
    if (world->hit(ray, 0.001, MAXFLOAT, rec)) {
        Ray scattered;
        Vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(ray, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1);
        }
        else{
            return Vec3(0, 0, 0);
        }
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
    
    Camera cam(90,nx/ny);
    
    float R = cos(M_PI/4);
    
    Hitable *list[2];
    
    list[0] = new Sphere(Vec3(-R, 0, -1), R, new Lambertian(Vec3(0, 0, 1)));
    list[1] = new Sphere(Vec3(R, 0, -1), R, new Lambertian(Vec3(1, 0, 0)));
                         
    
    
    Hitable *world = new HitableList(list,2);
    
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vec3 col(0,0,0);
            
            for (int s = 0; s < ns; s++) {
                // anti-aliasing: take ns samples in each pixel and average the color
                float u = float(i + drand48())/float(nx);
                float v = float(j + drand48())/float(ny);
                Ray ray = cam.get_ray(u, v);
                
                col = col + color(ray, world, 0);
            }
            
            col = col / float(ns);
            
            // gamma-2 correction
            col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    
}
