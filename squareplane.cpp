#include "squareplane.h"

SquarePlane::SquarePlane(char *name, glm::mat4 transform_mat)
{
    this->transform_mat = transform_mat;
    this->name = name;
}


intersection SquarePlane::getIntersection(ray *inputRay) {
    float t;
    glm::vec4 p;
    glm::vec4 normal;

    glm::mat4 invMat = glm::inverse(this->transform_mat);
    ray transformedRay = inputRay->getTransformedCopy(invMat);

    glm::vec4 plane_normal = glm::vec4(0, 0, 1, 0);
    t = (glm::dot(((float)-1  * transformedRay.getOrigin()), plane_normal))/(glm::dot(transformedRay.getDirection(), plane_normal));
    p = transformedRay.getOrigin() + t * transformedRay.getDirection();

    //calculate normal at intersection point p
    float px = p[0];
    float py = p[1];
    float pz = p[2];
    float max = -INFINITY;
    if (fabs(px) > max) {
        max = px;
    }
    if (fabs(py) > max) {
        max = py;
    }
    if (fabs(pz) > max) {
        max = pz;
    }

    if (max == px) {
        normal = glm::vec4(1, 0, 0, 0);
    }
    else if (max == py) {
        normal = glm::vec4(0, 1, 0, 0);
    }
    if (max == px) {
        normal = glm::vec4(1, 0, 0, 0);
    }

    //if point is not within boundaries of our square plane, there is no intersection
    if (p.operator [](0) < -.5 || p.operator [](1) < -.5 || p.operator [](0) > .5 || p.operator [](1) > .5) {
        return intersection(glm::vec4(0, 0, 0, 0), glm::vec4(0, 0, 0, 0), -1, this);
    }


    //how to convert p and normal to world space?
    // multiply by inverse tranpose of model matrix

    return intersection(p, normal, t, this);
}
