#ifndef CUBE_H
#define CUBE_H

#include "geometry.h"
class Cube : public Geometry
{
public:
    Cube(QString name, glm::mat4 transform_mat, Material material, QString type);

    virtual Intersection getIntersection(ray inputRay);

//    Material getMaterial();

//    glm::mat4 * getTransformMat();
private:
 //   glm::mat4 transform_mat;
    //QString name;
   // Material material;
};

#endif // CUBE_H
