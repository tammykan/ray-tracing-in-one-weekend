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
#include <fstream>
#include <ctime>

tm *get_current_time(){

    time_t currentTime;
    struct tm *localTime;
    
    time( &currentTime );
    localTime = localtime( &currentTime );
    
    return localTime;
}


Hitable *hitable_scene(){
    
    int n = 500;
    
    Hitable **list = new Hitable*[n+1];
    
    list[0] = new Sphere(Vec3(0, -1000, 0),1000,new Lambertian(Vec3(0.5, 0.5, 0.5)));
    
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = drand48();
            Vec3 center(a+0.9*drand48(), 0.2, b+0.9*drand48());
            if ((center-Vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.0) {//diffuse
                    list[i++] = new Sphere(center,0.2, new Lambertian(Vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
                }
                else if (choose_mat < 0.95){//metal
                    list[i++] = new Sphere(center,0.2,
                                           new Metal(Vec3(0.5*(1+drand48()), 0.5*(1+drand48()), 0.5*(1+drand48())), 0.5*drand48()));
                }
                else{//glass
                    list[i++] = new Sphere(center,0.2, new Dielectric(1.5));
                }
            }
        }
    }
    
    list[i++] = new Sphere(Vec3(0, 1, 0),1.0,new Dielectric(1.5));
    list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0, new Lambertian(Vec3(0.4, 0.2, 0.1)));
    list[i++] = new Sphere(Vec3(4, 1, 0), 1.0, new Metal(Vec3(0.7, 0.6, 0.5),0.0));
    
    
    return new HitableList(list,i);
}


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
    
    std::cout << "started...\n";
    
    std::ofstream myfile;
    
    myfile.open("output.ppm");
 
    int nx = 400;
    int ny = 300;
    int ns = 100;
    
    
    myfile << "P3\n" << nx << " " << ny << "\n255\n";
    
    Vec3 lookFrom = Vec3(20, 20, 2);
    Vec3 lookAt = Vec3(0, 0, -1);
    float dist_to_focus = (lookFrom - lookAt).length();
    float aperture = 2.0;
    
    Camera cam(lookFrom, lookAt, Vec3(0, 1, 0), 20,float(nx)/float(ny), aperture, dist_to_focus);
    
    float R = cos(M_PI/4);
    
    Hitable *list[5];
    
    //list[0] = new Sphere(Vec3(-R, 0, -1), R, new Lambertian(Vec3(0, 0, 1)));
    //list[1] = new Sphere(Vec3(R, 0, -1), R, new Lambertian(Vec3(1, 0, 0)));
                         
    
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.1,0.2,0.5)));
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100, new Lambertian(Vec3(0.8, 0.8, 0.0)));
    list[2] = new Sphere(Vec3(1,0,-1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0));
    list[3] = new Sphere(Vec3(-1, 0, -1), 0.5, new Dielectric(1.5));
    list[4] =new Sphere(Vec3(-1, 0, -1), -0.45, new Dielectric(1.5));
    
    
    //Hitable *world = new HitableList(list,5);
    Hitable *world = hitable_scene();
    
    tm *now = get_current_time();
    std::cout << "world generated   " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\n";
    
    for (int j = ny - 1; j >= 0; j--) {
        
        now = get_current_time();
        
        std::cout << j << "   " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\n";
        
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
            
            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    myfile.close();
    
    std::cout << "done!\n";
    
}
