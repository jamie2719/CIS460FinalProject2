#ifndef MATERIAL_H
#define MATERIAL_H
#include <QString>

class Material
{
public:
    Material(char* type, char* name, int r, int g, int b, char* texture, QString normal, bool emissive);
    char* getType();
    char* getName();
    int getR();
    int getG();
    int getB();
    char* getTexture();
    char* getNormal();
    bool isEmissive();
private:
    char* type;
    char* name;
    int r;
    int g;
    int b;
    char* texture;
    char* normal;
    bool emissive;
};

#endif // MATERIAL_H
