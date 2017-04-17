#include "jsonparser.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QFile>
#include "ray.h"

JsonParser::JsonParser()
{
}

void addGeometry(QJsonObject shape, scene_t *scene) {
    Geometry *geometry;
    char *name;
    if(shape.contains("name")){
        name = shape["name"].toString().toLatin1().data();
    } else {
        name = "";
    }
        QJsonObject transform = shape["transform"].toObject();
        glm::mat4 tmat = glm::mat4();
        glm::mat4 trmat = glm::mat4();
        glm::mat4 smat = glm::mat4();
        glm::mat4 rmat = glm::mat4();
        if(transform.contains("translate")) {
            QJsonArray translate = transform["translate"].toArray();


            trmat = glm::translate(trmat, glm::vec3((float)translate[0].toDouble(),
                    (float)translate[1].toDouble(),
                    (float)translate[2].toDouble())); //check version of glm


            tmat = tmat * trmat;
        }
        if (transform.contains("scale")) {
            QJsonArray scale = transform["scale"].toArray();
            smat = glm::scale(smat, glm::vec3((float)scale[0].toDouble(),
                    (float)scale[1].toDouble(),
                    (float)scale[2].toDouble()));
            tmat = tmat * smat;
        }
        if(transform.contains("rotate")) {
            QJsonArray rotate = transform["rotate"].toArray();
            rmat = glm::rotate(rmat, (float)rotate[0].toDouble(),
                    glm::vec3(0, 0, 0));

            tmat = tmat * rmat;
        }
        if(QString::compare(shape["type"].toString(),("sphere")) == 0) {
            *geometry = Sphere(name, tmat);
        } else if(QString::compare(shape["type"].toString(),("cube")) == 0) {
            *geometry = Cube(name, tmat);
        } else if(QString::compare(shape["type"].toString(),("triangle")) == 0) {
            //*geometry = Triangle(name, tmat);
        } else if(QString::compare(shape["type"].toString(),("square")) == 0) {
            *geometry = SquarePlane(name, tmat);
        } else if(QString::compare(shape["type"].toString(),("mesh")) == 0) {
            *geometry = Mesh(name, tmat);
        }
    scene->geometries->push_back(*geometry);
}

void JsonParser::parse(const char* name) {
    QString fileString;
    QFile file;
    file.setFileName(name);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileString = file.readAll();
    file.close();
    scene_t *sceneTemp = (scene_t *) malloc(sizeof(scene_t));
    QJsonDocument json = QJsonDocument::fromJson(fileString.toUtf8());
    QJsonObject jsonObject = json.object();
    QJsonObject scene = jsonObject.value(QString("scene")).toObject();
    QJsonObject cam = scene.value(QString("camera")).toObject();
    QJsonArray target = cam["target"].toArray();
    sceneTemp->camera->center_x = (float) target.at(0).toDouble();
    sceneTemp->camera->center_y = (float) target.at(1).toDouble();
    sceneTemp->camera->center_z = (float) target.at(2).toDouble();
    QJsonArray eye = cam["eye"].toArray();
    sceneTemp->camera->eye_x = (float) eye.at(0).toDouble();
    sceneTemp->camera->eye_y = (float) eye.at(1).toDouble();
    sceneTemp->camera->eye_z = (float) eye.at(2).toDouble();
    QJsonArray worldUp = cam["worldUp"].toArray();
    sceneTemp->camera->up_x = (float) worldUp.at(0).toDouble();
    sceneTemp->camera->up_y = (float) worldUp.at(1).toDouble();
    sceneTemp->camera->up_z = (float) worldUp.at(2).toDouble();
    sceneTemp->camera->fov = (float) cam["fov"].toDouble();
    sceneTemp->camera->width = (float) cam["width"].toDouble();
    sceneTemp->camera->height = (float) cam["height"].toDouble();
    sceneTemp->camera->near = 0.01;
    sceneTemp->camera->far = 1000;

    QJsonArray geom = scene.value(QString("geometry")).toArray();
    for (int i = 0; i < geom.size(); i++) {
        addGeometry(geom.at(0).toObject(), sceneTemp);
    }
    scenes->push_back(*sceneTemp);
}


