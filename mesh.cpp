#include "mesh.h"

Mesh::Mesh(QString name, glm::mat4 transform_mat, Material material, QString type) : Geometry()
{
    //this->transform_mat = transform_mat;
    this->setMat(transform_mat);
    //this->name = name;
    //this->material = material;
    this->setMaterial(material);
    this->setName(name);
    this->setType(type);
}

//Material Mesh::getMaterial() {
//    return this->material;
//}

Intersection Mesh::getIntersection(ray inputRay) {

}
