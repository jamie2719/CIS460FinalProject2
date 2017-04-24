#include "sphere.h"


Sphere::Sphere(QString name, glm::mat4 transform_mat, Material material) : Geometry()
{
    this->transform_mat = transform_mat;
    this->name = name;
    this->material = material;
}
Sphere::~Sphere() {
//    delete material;
}

Material Sphere::getMaterial() {
    return this->material;
}

Intersection Sphere::getIntersection(ray inputRay) {
    //The Sphere should have a radius of 0.5 and should be centered at the origin.
    //center = (0, 0, 0)
    //radius = .5
    float t;
    glm::vec4 p;
    glm::vec4 normal;

    glm::mat4 invMat = glm::inverse(this->transform_mat);

    ray transformedRay = inputRay.getTransformedCopy(invMat);

    float x0 = transformedRay.getOrigin()[0];
    float y0 = transformedRay.getOrigin()[1];
    float z0 = transformedRay.getOrigin()[2];

    float xd = transformedRay.getDirection()[0];
    float yd = transformedRay.getDirection()[1];
    float zd = transformedRay.getDirection()[2];


    float a = pow(xd, 2.0) + pow(yd, 2.0) + pow(zd, 2.0);
    float b = 2 * (xd*x0 + yd*y0 + zd*z0);
    float c = pow(x0, 2.0) + pow(y0, 2.0) + pow(z0, 2.0) - .25;

    float disc = pow(b, 2.0) - 4.0 * a * c;
    if (disc < 0) {
        return Intersection(glm::vec4(0, 0, 0, 0), glm::vec4(0, 0, 0, 0), -1, this);
    }
    else {
        float t0 = b * -1.0 - (sqrtf(disc))/(2 * a);
        float t1 = b * -1.0 + (sqrtf(disc))/(2 * a);

        if (t0 > 0) {
            //check which is smaller
            if (t0 < t1) {
                t = t0;
            }
            else {
                t = t1;
            }
        }
        else {
            //use t1
            t = t1;
        }
        p = transformedRay.getOrigin() + t * transformedRay.getDirection();
        normal = glm::normalize(p);

        glm::mat4 inverse = glm::inverse(this->transform_mat);
        glm::mat4 inverse_transpose = glm::transpose(inverse);

        p = inverse * p; //NOT TRANSPOSE
        normal = inverse_transpose * normal;
    }

    return Intersection(p, normal, t, this);

}
