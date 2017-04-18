#ifndef SQUAREPLANE_H
#define SQUAREPLANE_H
#include "geometry.h"

class SquarePlane : public Geometry
{
public:
    SquarePlane(char *name, glm::mat4 transform_mat, Material material);

    virtual intersection getIntersection(ray *inputRay);

private:
    glm::mat4 transform_mat;
    const char *name;
    Material material;
};

#endif // SQUAREPLANE_H
