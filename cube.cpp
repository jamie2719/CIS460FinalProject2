#include "cube.h"

Cube::Cube(QString name, glm::mat4 transform_mat, Material material, QString type) : Geometry() {
 //have to be able to  make cube of any size but get intersection should always test against unit sphere
    //this->transform_mat = transform_mat;
    this->setMat(transform_mat);
    //this->name = name;
    //this->material = material;
    this->setMaterial(material);
    this->setName(name);
    this->setType(type);
}


//glm::mat4 * Cube::getTransformMat() {
//    return this->getTransformMat();
//}

//Material Cube::getMaterial() {
//    return this->material;
//}

Intersection Cube::getIntersection(ray inputRay) {
    //The Cube should be 1x1x1 in dimensions and should be centered at the origin.
    //This means its vertices will be of the form <+-0.5, +-0.5, +-0.5>.


    float t_near = -INFINITY;
    float t_far = INFINITY;
    glm::vec4 p;
    glm::vec4 normal;

    glm::mat4 tmat = *this->getTransformMat();
    glm::mat4 invMat = glm::inverse(tmat);

    ray transformedRay = inputRay.getTransformedCopy(invMat);

    float x0 = transformedRay.getOrigin()[0];
    float y0 = transformedRay.getOrigin()[1];
    float z0 = transformedRay.getOrigin()[2];

    float xd = transformedRay.getDirection()[0];
    float yd = transformedRay.getDirection()[1];
    float zd = transformedRay.getDirection()[2];


    //x slab
    if (xd == 0) {
        if (x0 < -.5 || x0 > .5) {
            return Intersection(glm::vec4(0, 0, 0, 0), glm::vec4(0, 0, 0, 0), -1.0f,
                                (Geometry *) this);
        }
    }
    else {
        float t0x = (-.5 - x0)/xd;
        float t1x = (.5 - x0)/xd;

        if (t0x > t1x) {
            float tempx = t0x;
            t0x = t1x;
            t1x = tempx;
        }
        if (t0x > t_near) {
            t_near = t0x;
        }
        if (t1x < t_far) {
            t_far = t1x;
        }
    }

    //y slab
    if (yd == 0) {
        if (y0 < -.5 || y0 > .5) {
            return Intersection(glm::vec4(0, 0, 0, 0), glm::vec4(0, 0, 0, 0), -1, (Geometry *)this);
        }
    }
    else {
        float t0y = (-.5 - y0)/yd;
        float t1y = (.5 - y0)/yd;

        if (t0y > t1y) {
            float tempy = t0y;
            t0y = t1y;
            t1y = tempy;
        }
        if (t0y > t_near) {
            t_near = t0y;
        }
        if (t1y < t_far) {
            t_far = t1y;
        }
    }

    //z slab
    if (zd == 0) {
        if (z0 < -.5 || z0 > .5) {
            return Intersection(glm::vec4(0, 0, 0, 0), glm::vec4(0, 0, 0, 0), -1, (Geometry *)this);
        }
    }
    else {
        float t0z = (-.5 - z0)/zd;
        float t1z = (.5 - z0)/zd;

        if (t0z > t1z) {
            float tempz = t0z;
            t0z = t1z;
            t1z = tempz;
        }
        if (t0z > t_near) {
            t_near = t0z;
        }
        if (t1z < t_far) {
            t_far = t1z;
        }
    }

    if (t_near > t_far) {
        return Intersection(glm::vec4(0, 0, 0, 0), glm::vec4(0, 0, 0, 0), -1, (Geometry *) this);
    }

    p = transformedRay.getOrigin() + t_near * transformedRay.getDirection();

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
    if (max == pz) {
        normal = glm::vec4(0, 0, 1, 0);
    }


    //convert p and normal to world space
    glm::mat4 inverse = glm::inverse(tmat);
    glm::mat4 inverse_transpose = glm::transpose(inverse);

    p = inverse * p;
    normal = inverse_transpose * normal;


    return Intersection(p, glm::normalize(normal), t_near, (Geometry *)this);

}

glm::mat4 Cube::computeTextureToObjectMatrix() {

}
