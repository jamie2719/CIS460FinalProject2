#include "jsonparser.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QFile>
#include "ray.h"
#include "QImage"
#include <iostream>

JsonParser::JsonParser()
{
}
scene_t *sceneGlobal;
void JsonParser::addMaterials(QJsonObject mat, scene_t *scene) {
    char* type = mat["type"].toString().toLatin1().data();
    QString key = mat["name"].toString();
    char* name = key.toLatin1().data();
    int r = 1;
    int g = 1;
    int b = 1;
    if (mat.contains("baseColor")) {
        QJsonArray baseColor = mat["baseColor"].toArray();
        r = baseColor.at(0).toInt();
        g = baseColor.at(1).toInt();
        b = baseColor.at(2).toInt();
    }
    Material *newMat;
    QString nu = "";
    char* null = nu.toLatin1().data();
    bool emiss = false;
    if(mat.contains("emssive")) {
        QString emis = mat["emissive"].toString();
        QString tr = "true";
        if (emis == tr) {
            emiss = true;
        }
    }
    if(mat.contains("texture")) {
        char* texture = mat["texture"].toString().toLatin1().data();
        if(mat.contains("normalMap")) {
            QString normal = mat["normalMap"].toString();
            newMat = new Material(type, name, r, g, b, texture, normal, emiss);
        } else {
            newMat = new Material(type, name, r, g, b, texture, nu, emiss);
        }
    } else {
        if(mat.contains("normalMap")) {
            QString normal = mat["normalMap"].toString();
            newMat = new Material(type, name, r, g, b, null, normal, emiss);
        } else {
            newMat = new Material(type, name, r, g, b, null, nu, emiss);
        }
    }
    scene->materialsMap->insert(key, newMat);
}

void JsonParser::addGeometry(QJsonObject shape, scene_t *scene) {
    Geometry geometry = Geometry();
    Material *shapeMaterial;
    if (scene->materialsMap->contains(shape["material"].toString())) {
        shapeMaterial = scene->materialsMap->value(shape["material"].toString());
    }
    char *name;
    if(shape.contains("name")){
        name = shape["name"].toString().toLatin1().data();
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
            geometry = Sphere(name, tmat, shapeMaterial);
        } else if(QString::compare(shape["type"].toString(),("cube")) == 0) {
            geometry = Cube(name, tmat, shapeMaterial);
        } else if(QString::compare(shape["type"].toString(),("triangle")) == 0) {
            //geometry = Triangle(name, tmat, shapeMaterial);
            //add tinyobj stuff to load an obj file
        } else if(QString::compare(shape["type"].toString(),("square")) == 0) {
            geometry = SquarePlane(name, tmat, shapeMaterial);
        } else if(QString::compare(shape["type"].toString(),("mesh")) == 0) {
<<<<<<< HEAD
            //*geometry = Mesh(name, tmat, shapeMaterial);
        } else if(QString::compare(shape["type"].toString(),("squarePlane"))) {
            //*geometry = SquarePlane(name, tmat, shapeMaterial);
}
        // scene->geometries->push_back(geometry);
=======
            geometry = Mesh(name, tmat, shapeMaterial);
            //add tinyobj stuff to load an obj file
        } else if(QString::compare(shape["type"].toString(),("squarePlane"))) {
            geometry = SquarePlane(name, tmat, shapeMaterial);
        }
         scene->geometries->push_back(geometry);

>>>>>>> 69c970bfea81a80897923260e41afdcd472dd6b5
}

scene_t JsonParser::parse(const char* name) {
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
    QJsonArray worldUp = cam["worldUp"].toArray();
    QJsonArray eye = cam["eye"].toArray();
    sceneTemp->camera = Camera(.01, 1000, (float) eye.at(0).toDouble(), (float) eye.at(1).toDouble(), (float) eye.at(2).toDouble(),
                               (float) worldUp.at(0).toDouble(), (float) worldUp.at(1).toDouble(), (float) worldUp.at(2).toDouble(),
                               (float) target.at(0).toDouble(), (float) target.at(1).toDouble(), (float) target.at(2).toDouble(),
                               (float) cam["fov"].toDouble(), (float) cam["width"].toDouble(), (float) cam["height"].toDouble());
            //(float near, float far, float eye_x, float eye_y, float eye_z, float up_x, float up_y, float up_z,
           // float center_x, float center_y, float center_z, float fov, float width, float height)
//    sceneTemp->camera->center_x = (float) target.at(0).toDouble();
//    sceneTemp->camera->center_y = (float) target.at(1).toDouble();
//    sceneTemp->camera->center_z = (float) target.at(2).toDouble();

//    sceneTemp->camera->eye_x = (float) eye.at(0).toDouble();
//    sceneTemp->camera->eye_y = (float) eye.at(1).toDouble();
//    sceneTemp->camera->eye_z = (float) eye.at(2).toDouble();

//    sceneTemp->camera->up_x = (float) worldUp.at(0).toDouble();
//    sceneTemp->camera->up_y = (float) worldUp.at(1).toDouble();
//    sceneTemp->camera->up_z = (float) worldUp.at(2).toDouble();
//    sceneTemp->camera->fov = (float) cam["fov"].toDouble();
//    sceneTemp->camera->width = (float) cam["width"].toDouble();
//    sceneTemp->camera->height = (float) cam["height"].toDouble();
//    sceneTemp->camera->near = 0.01;
//    sceneTemp->camera->far = 1000;
    QJsonArray materials = scene.value(QString("material")).toArray();
    for (int i = 0; i < materials.size(); i++) {
        JsonParser::addMaterials(materials.at(i).toObject(), sceneTemp);
    }

    QJsonArray geom = scene.value(QString("geometry")).toArray();
    for (int i = 0; i < geom.size(); i++) {
        JsonParser::addGeometry(geom.at(i).toObject(), sceneTemp);
    }
    sceneGlobal = sceneTemp;
    return *sceneTemp;
}


bool comparator(Intersection a, Intersection b) {
    return (a.getT() < b.getT());
}


void JsonParser::render(float width, float height, scene_t scene) {
    QImage output = QImage(width, height, QImage::Format_RGB888);
    output.fill(Qt::black);
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            ray *currRay = scene.camera.raycast(col, row);
            std::vector<Intersection> intersections;
            for (int a = 0; a < scene.geometries->size(); a++) {
                Geometry currGeometry = scene.geometries->at(a);
                Intersection currIntersection = currGeometry.getIntersection(currRay);
                if (currIntersection.getT() >= 0) {
                    intersections.push_back(currIntersection);
                }
            }
            if (!intersections.empty()) {
                std::sort(intersections.begin(), intersections.end(), comparator);
                //color pixel based on closest geometry
                QRgb color = qRgb(255, 0, 0);
                output.setPixel(col, row, color);
            }

        }
    }
    // save image
    if (output.save("/Users/Jamie/Desktop/CIS 460/final_project/test.jpg")) {
        std::cout<<"save successful"<<endl;
    } else {
        std::cout<<"save unsuccessful"<<endl;
    }
}




