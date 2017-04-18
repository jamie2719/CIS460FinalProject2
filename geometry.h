#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "intersection.h"
//#include "mat4.h"
#include "ray.h"
#include "math.h"
#include "la.h"

class Geometry {
public:
    Geometry();
    virtual intersection getIntersection(ray *inputRay); //jess's class intersection

private:
    glm::mat4 transform_mat;
    //Material material;
};


//need to store transformation matrix

#endif // GEOMETRY_H
