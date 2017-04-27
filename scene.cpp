#include "scene.h"

Scene::Scene()
{

}

Scene::Scene(QMap<QString, Material>* materials, std::vector<Geometry*> *geos, std::vector<Geometry *> *lights, Camera* cam)
{
    this->camera = cam;
    this->materialsMap = materials;
    this->geometries = geos;
    this->lights = lights;
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

std::vector<Geometry *> *Scene::getLights() {
    return this->lights;
}

Camera *Scene::getCamera() {
    return this->camera;
}
