#include "squareplane.h"

SquarePlane::SquarePlane(char *name, glm::mat4 transform_mat, Material *material) : Geometry()
{
    this->transform_mat = transform_mat;
    this->name = name;
    this->material = material;
}

Material *SquarePlane::getMaterial() {
    return this->material;
}

Intersection SquarePlane::getIntersection(ray inputRay) {
    float t;
    glm::vec4 p;
    glm::vec4 normal;

    glm::mat4 invMat = glm::inverse(this->transform_mat);
    ray transformedRay = inputRay.getTransformedCopy(invMat);

    glm::vec4 plane_normal = glm::vec4(0, 0, 1, 0);
    t = (glm::dot(((float)-1  * transformedRay.getOrigin()), plane_normal))/(glm::dot(transformedRay.getDirection(), plane_normal));
    p = transformedRay.getOrigin() + t * transformedRay.getDirection();
    normal = plane_normal;


    //if point is not within boundaries of our square plane, there is no intersection
    if (p.operator [](0) < -.5 || p.operator [](1) < -.5 || p.operator [](0) > .5 || p.operator [](1) > .5) {
        return Intersection(glm::vec4(0, 0, 0, 0), glm::vec4(0, 0, 0, 0), -1, this);
    }


    //convert p and normal to world space
    glm::mat4 inverse = glm::inverse(transform_mat);
    glm::mat4 inverse_transpose = glm::transpose(inverse);

    p = p * inverse;
    normal = normal * inverse_transpose;

    return Intersection(p, normal, t, this);
}
