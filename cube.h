#ifndef CUBE_H
#define CUBE_H

#include "geometry.h"
class Cube : public Geometry
{
public:
    Cube(char *name, glm::mat4 transform_mat);

    intersection getIntersection(ray *inputRay);

private:
    glm::mat4 transform_mat;
    const char* name;
};

#endif // CUBE_H
