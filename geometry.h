#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "intersection.h"
//#include "mat4.h"
#include "ray.h"
#include "math.h"
#include "la.h"
#include "material.h"

class Geometry {
public:
    Geometry();
    ~Geometry();
    virtual Intersection getIntersection(ray inputRay) = 0; //jess's class intersection
    virtual Material *getMaterial() = 0;

private:
//    glm::mat4 transform_mat;
//    Material *material;
};


//need to store transformation matrix

#endif // GEOMETRY_H
