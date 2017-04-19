#include "material.h"

Material::Material(char* type, char* name, int r, int g, int b, char* texture, QString normal, bool emissive)
{
    this->type = type;
    this->name = name;
    this->r = r;
    this->g = g;
    this->b = b;
    this->texture = texture;
    this->normal = normal.toLatin1().data();
    this->emissive = emissive;
}

char *Material::getType() {
    return this->type;
}
char *Material::getName() {
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
char *Material::getTexture(){
    return this->texture;
}
char *Material::getNormal() {
    return this->normal;
}
bool Material::isEmissive() {
    return this->emissive;
}
