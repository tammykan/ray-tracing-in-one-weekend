#include <gtest/gtest.h>
#include "Ray.h"

TEST(RayTest, PointAtParameter){
    Ray r(Vec3(1,2,3),Vec3(4,5,6));
    
    Vec3 res = r.point_at_parameter(2);
    
    // 1 + 2*4 = 9
    EXPECT_EQ(res.e[0], 9);
}