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
    Scene(QMap<QString, Material> *materials, std::vector<Geometry*> *geos, Camera* cam);
    void setCamera(Camera* cam);
    QMap<QString, Material> *getMaterials();
    std::vector<Geometry*> *getGeometries();
    Camera *getCamera();

private:
    QMap<QString, Material> *materialsMap;
    std::vector<Geometry*> *geometries;
    Camera* camera;
};

#endif // SCENE_H
