#include "triangle.h"

Triangle::Triangle(char *name, glm::mat4 transform_mat, glm::vec4 a, glm::vec4 b, glm::vec4 c)
{
    this->transform_mat = transform_mat;
    this->name = name;
    this->a = a;
    this->b = b;
    this->c = c;
}

//cross product of 2 vec4s
glm::vec4 cross(const glm::vec4 &v1, const glm::vec4 &v2) {
    return glm::vec4(v1[1] * v2[2] - v2[1] * v1[2],
            v1[2] * v2[0] - v2[2] * v1[0],
            v1[0] * v2[1] - v2[0] * v1[1], 0);
}


//computes area of a triangle given 3 coordinates (vec4s)
float area(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3) {
    return (cross(p1-p2, p3-p2).length())/2.0;
}

intersection Triangle::getIntersection(ray *inputRay) {
    //find intersection point using ray-plane intersection
    float t;
    glm::vec4 p;
    glm::vec4 normal;

    glm::mat4 invMat = glm::inverse(this->transform_mat);
    ray transformedRay = inputRay->getTransformedCopy(invMat);

    glm::vec4 plane_normal = glm::vec4(0, 0, 1, 0);
    t = (glm::dot(((float)-1  * transformedRay.getOrigin()), plane_normal))/(glm::dot(transformedRay.getDirection(), plane_normal));
    p = transformedRay.getOrigin() + t * transformedRay.getDirection();


    //check if point p is within bounds of triangle
    float s = area(this->a, this->b, this->c);
    float s1 = area(p, this->b, this->c)/s;
    float s2 = area(p, this->c, this->a)/s;
    float s3 = area(p, this->a, this->b)/s;


    //calculate normal of intersection point
    //triangle in xy plane, looking down z axis (positive behind us) => (0, 0, 0) (1, 0, 0) (0, 1, 0)
    //normal for this should be (0, 0, 1)
    //b - a X c - a

    if (s1 > 1 || s1 < 0 || s2 > 1 || s2 > 0 || s3 > 1 || s3 < 0 || s1+s2+s3 != 1.0) {
        return intersection(glm::vec4(0, 0, 0, 0), glm::vec4(0, 0, 0, 0), -1, this);
    }
    else {
        //convert back to world space
        return intersection(p, normal, t, this);
    }



}
