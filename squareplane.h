#ifndef SQUAREPLANE_H
#define SQUAREPLANE_H
#include "geometry.h"

class SquarePlane : public Geometry
{
public:
    SquarePlane(QString name, glm::mat4 transform_mat, Material material, QString type);

    virtual Intersection getIntersection(ray inputRay);

    glm::mat4 computeTextureToObjectMatrix();

//    virtual Material getMaterial();
private:
    //glm::mat4 transform_mat;
 //   QString name;
   // Material material;
};

#endif // SQUAREPLANE_H
