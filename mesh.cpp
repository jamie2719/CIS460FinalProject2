#include "mesh.h"

Mesh::Mesh(char *name, glm::mat4 transform_mat, Material *material)
{
    this->transform_mat = transform_mat;
    this->name = name;
    this->material = material;
}

Material *Mesh::getMaterial() {
    return this->material;
}

Intersection Mesh::getIntersection(ray *inputRay) {

}
