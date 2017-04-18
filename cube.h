#ifndef CUBE_H
#define CUBE_H

#include "geometry.h"
class Cube : public Geometry
{
public:
    Cube(char *name, glm::mat4 transform_mat, Material material);

    virtual intersection getIntersection(ray *inputRay);

private:
    glm::mat4 transform_mat;
    const char* name;
    Material material;
};

#endif // CUBE_H
