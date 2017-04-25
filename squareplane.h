#ifndef SQUAREPLANE_H
#define SQUAREPLANE_H
#include "geometry.h"

class SquarePlane : public Geometry
{
public:
    SquarePlane(QString name, glm::mat4 transform_mat, Material material);

    virtual Intersection getIntersection(ray inputRay);

//    virtual Material getMaterial();
private:
    //glm::mat4 transform_mat;
 //   QString name;
   // Material material;
};

#endif // SQUAREPLANE_H
