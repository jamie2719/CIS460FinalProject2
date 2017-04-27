#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "intersection.h"
//#include "mat4.h"
#include "ray.h"
#include "math.h"
#include "la.h"
#include "material.h"

class Geometry {
public:
    Geometry();
    //Geometry(glm::mat4 transform_mat, Material material);
    ~Geometry();
    virtual Intersection getIntersection(ray inputRay) = 0;
    Material getMaterial();
    QString getType();
    void setMaterial(Material material);
    glm::mat4 * getTransformMat();
    void setMat(glm::mat4 transform_mat);
    void setName(QString name);
    void setType(QString type);

private:
    glm::mat4 transform_mat;
    Material material;
    QString name;
    QString type;
};



#endif // GEOMETRY_H
