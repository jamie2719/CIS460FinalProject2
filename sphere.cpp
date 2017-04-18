#include "sphere.h"


Sphere::Sphere(char *name, glm::mat4 transform_mat)
{
    this->transform_mat = transform_mat;
}


intersection Sphere::getIntersection(ray *inputRay) {
    //The Sphere should have a radius of 0.5 and should be centered at the origin.
    //center = (0, 0, 0)
    //radius = .5
    float t;
    glm::vec4 p;
    glm::vec4 normal;

    glm::mat4 invMat = glm::inverse(this->transform_mat);

    ray transformedRay = inputRay->getTransformedCopy(invMat);

    float x0 = transformedRay.getOrigin().operator [](0);
    float y0 = transformedRay.getOrigin().operator [](1);
    float z0 = transformedRay.getOrigin().operator [](2);

    float xd = transformedRay.getDirection().operator [](0);
    float yd = transformedRay.getDirection().operator [](1);
    float zd = transformedRay.getDirection().operator [](2);


    float a = pow(xd, 2) + pow(yd, 2) + pow(zd, 2);
    float b = 2 * (xd*x0 + yd*y0 + zd*z0);
    float c = pow(x0, 2) + pow(y0, 2) + pow(z0, 2) - .25;

    float disc = pow(b, 2) - 4 * a * c;
    if (disc < 0) {
        return intersection(glm::vec4(0, 0, 0, 0), glm::vec4(0, 0, 0, 0), -1, this);
    }
    else {
        float t0 = b * -1 - (sqrtf(disc))/(2 * a);
        float t1 = b * -1 + (sqrtf(disc))/(2 * a);

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

        glm::mat4 inverse = glm::inverse(transform_mat);
        glm::mat4 inverse_transpose = glm::transpose(inverse);

        p = p * inverse_transpose;
        normal = normal * inverse_transpose;
    }

    return intersection(p, normal, t, this);

}
