#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "geometry.h"

class Triangle : public Geometry
{
public:
    Triangle(char *name, glm::mat4 transform_mat, Material *material, glm::vec4 a, glm::vec4 b, glm::vec4 c);

    virtual Intersection getIntersection(ray *inputRay);

    virtual Material *getMaterial();
private:

    glm::mat4 transform_mat;
    const char *name;
    Material *material;
    glm::vec4 a;
    glm::vec4 b;
    glm::vec4 c;
};

#endif // TRIANGLE_H
