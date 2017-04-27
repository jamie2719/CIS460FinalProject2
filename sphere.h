#ifndef SPHERE_H
#define SPHERE_H
#include "geometry.h"

class Sphere : public Geometry
{
public:
    Sphere(QString name, glm::mat4 transform_mat, Material material, QString type);
    ~Sphere();

    Intersection getIntersection(ray inputRay);

//    Material getMaterial();
private:
   // glm::mat4 transform_mat;
   // QString name;
   // Material material;
};

#endif // SPHERE_H
