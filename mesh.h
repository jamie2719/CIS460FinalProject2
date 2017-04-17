#ifndef MESH_H
#define MESH_H
#include "geometry.h"

class Mesh : public Geometry
{
public:
    Mesh(char *name, glm::mat4 transform_mat);

    intersection getIntersection(ray *ray);

private:
    glm::mat4 transform_mat;
    const char *name;


};

#endif // MESH_H
