#include "mesh.h"

Mesh::Mesh(char *name, glm::mat4 transform_mat)
{
    this->transform_mat = transform_mat;
    this->name = name;
}

intersection Mesh::getIntersection(ray *ray) {

}
