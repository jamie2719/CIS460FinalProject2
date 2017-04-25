#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "geometry.h"

class Triangle : public Geometry
{
public:
    Triangle(QString name, glm::mat4 transform_mat, Material material, glm::vec4 a, glm::vec4 b, glm::vec4 c);

    virtual Intersection getIntersection(ray inputRay);

//    virtual Material getMaterial();
private:

   // glm::mat4 transform_mat;
  //  QString name;
  //  Material material;
    glm::vec4 a;
    glm::vec4 b;
    glm::vec4 c;
};

#endif // TRIANGLE_H
