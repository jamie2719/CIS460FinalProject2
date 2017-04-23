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
    void addMaterial(QString name, Material* newMat);
    void addGeometries(Geometry shape);
    void setCamera(Camera cam);
    QMap<QString, Material*> *getMaterials();
    std::vector<Geometry*> *getGeometries();
    Camera getCamera();

private:
    QMap<QString, Material*> *materialsMap;
    std::vector<Geometry*> *geometries;
    Camera camera;
};

#endif // SCENE_H
