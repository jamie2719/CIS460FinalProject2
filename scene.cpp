#include "scene.h"

Scene::Scene()
{
     //this->camera = Camera(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

    this->materialsMap = new QMap<QString, Material*>;
    this->geometries = new std::vector<Geometry*>;
}

void Scene::addMaterial(QString name, Material* newMat) {
    this->materialsMap->insert(name, newMat);
}

void Scene::addGeometries(Geometry shape) {
    this->geometries->push_back(&shape);
}

void Scene::setCamera(Camera cam) {
    this->camera = cam;
}

QMap<QString, Material*> *Scene::getMaterials() {
    return this->materialsMap;
}

std::vector<Geometry*> *Scene::getGeometries() {
    return this->geometries;
}

Camera Scene::getCamera() {
    return this->camera;
}
