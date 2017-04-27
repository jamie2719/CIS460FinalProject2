#include "material.h"

Material::Material(){

}

Material::Material(QString type, QString name, float r, float g, float b, QString texture, QString normal, bool emissive)
{
    this->type = type;
    this->name = name;
    this->r = r;
    this->g = g;
    this->b = b;
    this->texture = texture;
    this->normal = normal;
    this->emissive = emissive;
}

QString Material::getType() {
    return this->type;
}
QString Material::getName() {
    return this->name;
}
int Material::getR() {
    return this->r;
}
int Material::getG() {
    return this->g;
}
int Material::getB() {
    return this->b;
}
QString Material::getTexture(){
    return this->texture;
}
QString Material::getNormal() {
    return this->normal;
}
bool Material::isEmissive() {
    return this->emissive;
}
