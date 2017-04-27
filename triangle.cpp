#include "triangle.h"

Triangle::Triangle(QString name, glm::mat4 transform_mat, Material material, glm::vec4 a, glm::vec4 b, glm::vec4 c, QString type) : Geometry()
{
    this->a = a;
    this->b = b;
    this->c = c;
    //this->transform_mat = transform_mat;
    this->setMat(transform_mat);
    //this->name = name;
    //this->material = material;
    this->setMaterial(material);
    this->setName(name);
    this->setType(type);
}

//Material Triangle::getMaterial() {
//    return this->material;
//}

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

Intersection Triangle::getIntersection(ray inputRay) {
    //find intersection point using ray-plane intersection
    float t;
    glm::vec4 p;
    glm::vec4 normal;

    glm::mat4 tmat = *this->getTransformMat();
    glm::mat4 invMat = glm::inverse(tmat);
    ray transformedRay = inputRay.getTransformedCopy(invMat);

    glm::vec4 plane_normal = glm::vec4(0, 0, 1, 0);
    t = (glm::dot(((float)-1  * transformedRay.getOrigin()), plane_normal))/(glm::dot(transformedRay.getDirection(), plane_normal));
    p = transformedRay.getOrigin() + t * transformedRay.getDirection();
    normal = plane_normal;

    //check if point p is within bounds of triangle
    float s = area(this->a, this->b, this->c);
    float s1 = area(p, this->b, this->c)/s;
    float s2 = area(p, this->c, this->a)/s;
    float s3 = area(p, this->a, this->b)/s;

    //if this doesnt work, use real calculation instead of hard coded plane normal
    //    //calculate normal of intersection point
    //    normal = cross(p1-p2, p3-p2);


    if (s1 > 1 || s1 < 0 || s2 > 1 || s2 > 0 || s3 > 1 || s3 < 0 || s1+s2+s3 != 1.0) {
        return Intersection(glm::vec4(0, 0, 0, 0), glm::vec4(0, 0, 0, 0), -1, this);
    }
    else {
        //convert p and normal to world space
        glm::mat4 inverse = glm::inverse(*this->getTransformMat());
        glm::mat4 inverse_transpose = glm::transpose(inverse);

        p = p * inverse;
        normal = normal * inverse_transpose;
        return Intersection(p, normal, t, this);
    }



}
