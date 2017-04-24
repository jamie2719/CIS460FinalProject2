#ifndef CUBE_H
#define CUBE_H

#include "geometry.h"
class Cube : public Geometry
{
public:
    Cube(QString name, glm::mat4 transform_mat, Material material);

    virtual Intersection getIntersection(ray inputRay);

    virtual Material getMaterial();
private:
    glm::mat4 transform_mat;
    QString name;
    Material material;
};

#endif // CUBE_H
