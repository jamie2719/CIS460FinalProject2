#include "mesh.h"

Mesh::Mesh(char *name, glm::mat4 transform_mat, Material material)
{
    this->transform_mat = transform_mat;
    this->name = name;
    this->material = material;
}

intersection Mesh::getIntersection(ray *ray) {

}
