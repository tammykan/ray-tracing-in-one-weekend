//
//  HitableList.h
//  ray-tracing-weekend
//
//  Created by Sun, Joy (Agoda) on 2/16/2559 BE.
//  Copyright © 2559 Sun, Joy (Agoda). All rights reserved.
//

#ifndef HitableList_h
#define HitableList_h

#include "Hitable.h"

class HitableList:public Hitable{
public:
    HitableList(){}
    
    HitableList(Hitable **l, int n){list = l; list_size = n;}
    
    virtual bool hit(Ray &ray, float t_min, float t_max, hit_record &rec) const;
    
    Hitable **list;
    int list_size;
};

bool HitableList::hit(Ray &ray, float t_min, float t_max, hit_record &rec) const{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_hit_so_far = t_max;
    
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(ray, t_min, closest_hit_so_far, temp_rec)) { // clever: set t_max to closest_hit_so_far
            hit_anything = true;
            closest_hit_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}


#endif /* HitableList_h */
