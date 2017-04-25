#ifndef MESH_H
#define MESH_H
#include "geometry.h"

class Mesh : public Geometry
{
public:
    Mesh(QString name, glm::mat4 transform_mat, Material material);

    virtual Intersection getIntersection(ray inputRay);

//    virtual Material getMaterial();
private:
   // glm::mat4 transform_mat;
   // QString name;
   // Material material;


};

#endif // MESH_H
