#include "scene.h"

Scene::Scene()
{

}

Scene::Scene(QMap<QString, Material>* materials, std::vector<Geometry*> *geos, Camera* cam)
{
    this->camera = cam;
    this->materialsMap = materials;
    this->geometries = geos;
}

void Scene::setCamera(Camera *cam) {
    this->camera = cam;
}

QMap<QString, Material> *Scene::getMaterials() {
    return this->materialsMap;
}

std::vector<Geometry *> *Scene::getGeometries() {
    return this->geometries;
}

Camera *Scene::getCamera() {
    return this->camera;
}
