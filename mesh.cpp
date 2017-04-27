#include "mesh.h"


Mesh::Mesh(QString name, glm::mat4 transform_mat, Material material, QString type) : Geometry()
{
    //this->transform_mat = transform_mat;
    this->setMat(transform_mat);
    //this->name = name;
    //this->material = material;
    this->setMaterial(material);
    this->setName(name);

    this->shapes = std::vector<tinyobj::shape_t>();
    this->materials = std::vector<tinyobj::material_t>();


    this->setType(type);
}

//Material Mesh::getMaterial() {
//    return this->material;
//}

Intersection Mesh::getIntersection(ray inputRay) {

}

glm::mat4 Mesh::computeTextureToObjectMatrix() {

}

const char *Mesh::getObjFilename() {
    return this->objfilename;
}

void Mesh::setObjFilename(const char *filename) {
    this->objfilename = filename;
}

void Mesh::loadObject() {
    const char *mtl_basepath = NULL;
    tinyobj::LoadObj(this->shapes, this->materials, this->getObjFilename(), mtl_basepath);
}
