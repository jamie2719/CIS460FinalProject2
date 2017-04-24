#include "mesh.h"

Mesh::Mesh(QString name, glm::mat4 transform_mat, Material material) : Geometry()
{
    this->transform_mat = transform_mat;
    this->name = name;
    this->material = material;
}

Material Mesh::getMaterial() {
    return this->material;
}

Intersection Mesh::getIntersection(ray inputRay) {

}
