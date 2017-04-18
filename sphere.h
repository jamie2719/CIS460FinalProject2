#ifndef SPHERE_H
#define SPHERE_H
#include "geometry.h"

class Sphere : public Geometry
{
public:
    Sphere(char *name, glm::mat4 transform_mat, Material material);

    virtual intersection getIntersection(ray *inputRay);

private:
    glm::mat4 transform_mat;
    const char* name;
    Material material;
};

#endif // SPHERE_H
