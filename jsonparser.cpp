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
//Scene sceneGlobal;
Material JsonParser::addMaterials(QJsonObject mat) {
    QString type = mat["type"].toString();
    QString name = mat["name"].toString();
    int r = 1;
    int g = 1;
    int b = 1;
    if (mat.contains("baseColor")) {
        QJsonArray baseColor = mat["baseColor"].toArray();
        r = baseColor.at(0).toInt();
        g = baseColor.at(1).toInt();
        b = baseColor.at(2).toInt();
    }
    bool emiss = false;
    Material newMat = Material(type, name, r, g, b, NULL, NULL, emiss);
    if(mat.contains("emissive")) {
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
            return newMat = Material(type, name, r, g, b, texture, normal, emiss);
        } else {
            return newMat = Material(type, name, r, g, b, texture, NULL, emiss);
        }
    } else {
        if(mat.contains("normalMap")) {
            QString normal = mat["normalMap"].toString();
            return newMat = Material(type, name, r, g, b, NULL, normal, emiss);
        } else {
            return newMat = Material(type, name, r, g, b, NULL, NULL, emiss);
        }
    }
}

Geometry* JsonParser::addGeometry(QJsonObject shape, QMap<QString, Material> *materialsMap) {
    //Geometry geometry;// = Geometry();
    Material shapeMaterial;
    if (materialsMap->contains(shape["material"].toString().toLatin1().data())) {
        shapeMaterial = materialsMap->value(shape["material"].toString().toLatin1().data());
    }
    QString name;
    if(shape.contains("name")){
        name = shape["name"].toString();
    }
    QJsonObject transform = shape["transform"].toObject();
    glm::mat4 tmat = glm::mat4();
    glm::mat4 trmat = glm::mat4();
    glm::mat4 smat = glm::mat4();
    glm::mat4 rmat = glm::mat4();
    glm::mat4 rmatx = glm::mat4();
    glm::mat4 rmaty = glm::mat4();
    glm::mat4 rmatz = glm::mat4();
    if(transform.contains("translate")) {
        QJsonArray translate = transform["translate"].toArray();


        trmat = glm::translate(trmat, glm::vec3((float)translate[0].toDouble(),
                               (float)translate[1].toDouble(),
                (float)translate[2].toDouble())); //check version of glm


        // tmat = tmat * trmat;
    }
    if (transform.contains("scale")) {
        QJsonArray scale = transform["scale"].toArray();
        smat = glm::scale(smat, glm::vec3((float)scale[0].toDouble(),
                          (float)scale[1].toDouble(),
                (float)scale[2].toDouble()));
        //tmat = tmat * smat;
    }
    if(transform.contains("rotate")) {
        QJsonArray rotate = transform["rotate"].toArray();
        rmatx = glm::rotate(rmat, (float)rotate[0].toDouble(),
                glm::vec3(0, 0, 0));
        rmaty = glm::rotate(rmat, (float)rotate[1].toDouble(),
                glm::vec3(0, 0, 0));
        rmatz = glm::rotate(rmat, (float)rotate[2].toDouble(),
                glm::vec3(0, 0, 0));
        rmat = rmatx*rmaty*rmatz;


        // tmat = tmat * rmat;
    }
    tmat = trmat * rmat * smat;

    if(QString::compare(shape["type"].toString(),("sphere")) == 0) {
        //           Geometry *geometry;
        Sphere *geometry = new Sphere(name, tmat, shapeMaterial);
        return geometry;
    } else if(QString::compare(shape["type"].toString(),("cube")) == 0) {
        Cube *geometry = new Cube(name, tmat, shapeMaterial);
        return geometry;
    } else if(QString::compare(shape["type"].toString(),("triangle")) == 0) {
        //geometry = Triangle(name, tmat, shapeMaterial);
        //add tinyobj stuff to load an obj file
    } else if(QString::compare(shape["type"].toString(),("square")) == 0) {
        SquarePlane *geometry = new SquarePlane(name, tmat, shapeMaterial);
        return geometry;
    } else if(QString::compare(shape["type"].toString(),("mesh")) == 0) {
        Mesh *geometry = new Mesh(name, tmat, shapeMaterial);
        return geometry;
        //add tinyobj stuff to load an obj file
    }


}

Scene* JsonParser::parse(const char* name) {
    QString fileString;
    QFile file;
    file.setFileName(name);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileString = file.readAll();
    file.close();
    QJsonDocument json = QJsonDocument::fromJson(fileString.toUtf8());
    QJsonObject jsonObject = json.object();
    QJsonObject scene = jsonObject.value(QString("scene")).toObject();
    QJsonObject cam = scene.value(QString("camera")).toObject();
    QJsonArray target = cam["target"].toArray();
    QJsonArray worldUp = cam["worldUp"].toArray();
    QJsonArray eye = cam["eye"].toArray();
    Camera *camera = new Camera(.01, 1000,
                                (float) eye.at(0).toDouble(), (float) eye.at(1).toDouble(), (float) eye.at(2).toDouble(),
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
    QMap<QString, Material> *materialsMap = new QMap<QString, Material>();
    for (int i = 0; i < materials.size(); i++) {
        Material mater = JsonParser::addMaterials(materials.at(i).toObject());
        materialsMap->insert(mater.getName(), mater);
    }

    QJsonArray geom = scene.value(QString("geometry")).toArray();
    std::vector<Geometry*> *geomets = new std::vector<Geometry*>();
    std::vector<Geometry*> *lights = new std::vector<Geometry*>();
    for (int i = 0; i < geom.size(); i++) {
        Geometry* geo = JsonParser::addGeometry(geom.at(i).toObject(), materialsMap);
        if (geo->getMaterial().isEmissive()) {
            lights->push_back(geo);
        }
        else {
            geomets->push_back(geo);
        }
    }
    return new Scene(materialsMap, geomets, lights, camera);
}


bool comparator(Intersection a, Intersection b) {
    return (a.getT() < b.getT());
}

//calculates the vector from point of intersection to light
glm::vec3 lightDirection(Intersection intersection, Geometry* light) {
    //how to get coordinates of light?
    glm::mat4 *mat = light->getTransformMat();
    glm::vec3 lightPosition = glm::vec3(mat->operator [](3));
    //glm::vec4((float)light->getTransformMat()[3][0], light->getTransformMat()[3][1], light->getTransformMat()[3][2], 1);
    glm::vec3 L = lightPosition - glm::vec3(intersection.getIntersection());
    return L;
}

//iterate through vector of lights in scene and calculate total light for a point with given normal using Lambert's law
float lambert(Intersection intersection, std::vector<Geometry*> *lights) {
    float E = 0.1;
    for (int i = 0; i < lights->size(); i++) {
        Geometry * currLight = lights->at(i);
//        glm::vec3 L = lightDirection(intersection, currLight);
        glm::vec3 L(0, 1, 0);
        E += CLAMPL(glm::dot(glm::normalize(glm::vec3(intersection.getNormal())), glm::normalize(L)));
    }
    return E;
}


void JsonParser::render(float width, float height, Scene* scene) {
    QImage output = QImage(width, height, QImage::Format_RGB888);
    output.fill(Qt::white);
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            ray currRay = scene->getCamera()->raycast(col, row, width, height);
//            int r = CLAMP(currRay.getDirection()[0] * 255);
//            int g = CLAMP(currRay.getDirection()[1] * 255);
//            int b = CLAMP(currRay.getDirection()[2] * 255);
//            QColor color = QColor(r, g, b);
//            output.setPixelColor(col, row, color);
//            continue;
            std::vector<Intersection> intersections = std::vector<Intersection>();
            std::vector<Geometry*> *lights = scene->getLights();
            std::vector<Geometry*> *geoms = scene->getGeometries();
            for (int a = 0; a < geoms->size(); a++){
                Geometry* geom = geoms->at(a);

                Intersection currIntersection = geom->getIntersection(currRay);

                if (currIntersection.getT() >= 0) {
                    if (!currIntersection.getGeometry()->getMaterial().isEmissive()) {
                        intersections.push_back(currIntersection);
                    }
                    else {

                    }
                }
            }
            if (!intersections.empty()) {
                std::sort(intersections.begin(), intersections.end(), comparator);
                //color pixel based on closest geometry
                //Geometry * closest = intersections[0].getGeometry();
                Intersection closest = intersections[0];
                //                QColor color = QColor(closest->getMaterial().getR() * 255,
                //                                  closest->getMaterial().getG() * 255,
                //                                  closest->getMaterial().getB() * 255);
                glm::vec4 normal = closest.getNormal();
                float E = lambert(closest, lights);
//                int r = CLAMP(closest.getGeometry()->getMaterial().getR() * 255 * E);
//                int g = CLAMP(closest.getGeometry()->getMaterial().getG() * 255 * E);
//                int b = CLAMP(closest.getGeometry()->getMaterial().getB() * 255 * E);

//                int r = CLAMP(normal[0] * 255);
//                int g = CLAMP(normal[1] * 255);
//                int b = CLAMP(normal[2] * 255 );

                if (E < 1) {

                }
                int r = CLAMPL(E);
                r = CLAMP(r*255);
                int g = CLAMPL(E);
                g = g*0;
                int b = CLAMPL(E);
                b = b*0;


                QColor color = QColor(r, g, b);
                output.setPixelColor(col, row, color);
            }

        }
    }
    // save image
    if (output.save("..//final project//test1.ppm")) {
        std::cout<<"save successful"<<endl;
    } else {
        std::cout<<"save unsuccessful"<<endl;
    }
}




