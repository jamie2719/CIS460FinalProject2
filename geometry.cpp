#include "geometry.h"

Geometry::Geometry() {

}

//Geometry::Geometry(glm::mat4 transform_mat, Material material) {
//    this->transform_mat = transform_mat;
//    this->material = material;
//}

Geometry::~Geometry() {
//    delete material;
}

glm::mat4 * Geometry::getTransformMat() {
    return &this->transform_mat;
}

Material Geometry::getMaterial() {
    return this->material;
}

QString Geometry::getType() {
    return this->type;
}


void Geometry::setMaterial(Material material) {
    this->material = material;
}

void Geometry::setMat(glm::mat4 transform_mat) {
    this->transform_mat = transform_mat;
}

void Geometry::setName(QString name) {
    this->name = name;
}

void Geometry::setType(QString type) {
    this->type = type;
}
