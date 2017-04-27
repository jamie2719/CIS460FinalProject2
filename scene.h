#ifndef SCENE_H
#define SCENE_H
#include <QMap>
#include <QString>
#include "material.h"
#include "geometry.h"
#include "camera.h"

class Scene
{
public:
    Scene();
    Scene(QMap<QString, Material> *materials, std::vector<Geometry*> *geos, std::vector<Geometry*> *lights, Camera* cam);
    void setCamera(Camera* cam);
    QMap<QString, Material> *getMaterials();
    std::vector<Geometry*> *getGeometries();
    std::vector<Geometry*> *getLights();
    Camera *getCamera();

private:
    QMap<QString, Material> *materialsMap;
    std::vector<Geometry*> *geometries;
    std::vector<Geometry*> *lights;
    Camera* camera;
};

#endif // SCENE_H
