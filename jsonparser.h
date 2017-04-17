#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <geometry.h>
#include <sphere.h>
#include <cube.h>
#include <squareplane.h>
#include <triangle.h>
#include <mesh.h>
//#include <mat4.h>
//#include <vec4.h>

typedef struct camera_struct {
  float near, far;
  float eye_x, eye_y, eye_z;
  float up_x, up_y, up_z;
  float fov;
  float width, height;
  float center_x, center_y, center_z;
} camera_t;

typedef struct material_struct {
  QString name;
  QJsonArray baseColor;
  QString texture;
  QString normalMap;
} material_t;

typedef struct scene_struct {
    QMap<QString, material_t> *materialsMap;
    std::vector<Geometry> *geometries;
    camera_t *camera = (camera_t *) malloc(sizeof(camera_t));
} scene_t;

class JsonParser
{
public:
    JsonParser();
    void addMaterials(QJsonObject mat, scene_t *scene);
    void addGeometry(QJsonObject shape, scene_t *scene);
    scene_t parse(const char* name);
    ray rayCast(float x, float y);
};

#endif // JSONPARSER_H
