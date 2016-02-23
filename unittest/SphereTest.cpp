//
//  SphereTest.cpp
//  ray-tracing-weekend
//
//  Created by Sun, Joy (Agoda) on 2/16/2559 BE.
//  Copyright © 2559 Sun, Joy (Agoda). All rights reserved.
//

#include <stdio.h>
#include <gtest/gtest.h>
#include "Sphere.h"
#include "float.h"

TEST(SphereTest, HitTest){
    
    Sphere s = Sphere(Vec3(1, 1, 0), 1);
    Ray r = Ray(Vec3(-1, 1, 0), Vec3(1, 0, 0));
    
    hit_record rec;
    
    EXPECT_EQ(s.hit(r, 0, MAXFLOAT, rec), true);
}

