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
#include <material.h>
#include "camera.h"
#include "scene.h"


//typedef struct camera_struct {
//  float near, far;
//  float eye_x, eye_y, eye_z;
//  float up_x, up_y, up_z;
//  float fov;
//  float width, height;
//  float center_x, center_y, center_z;
//} camera_t;


class JsonParser
{
public:
    JsonParser();
    void addMaterials(QJsonObject mat, Scene *scene);
    void addGeometry(QJsonObject shape, Scene *scene);
//    scene_t parse(const char* name);
    Scene *parse(const char* name);
    ray rayCast(float x, float y);
    void render(float width, float height, Scene *scene);
};

#endif // JSONPARSER_H
