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

