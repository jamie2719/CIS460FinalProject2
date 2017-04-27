#ifndef MATERIAL_H
#define MATERIAL_H
#include <QString>

class Material
{
public:
    Material();
    Material(QString type, QString name, int r, int g, int b, QString texture, QString normal, bool emissive);
    QString getType();
    QString getName();
    int getR();
    int getG();
    int getB();
    QString getTexture();
    QString getNormal();
    bool isEmissive();
private:
    QString type;
    QString name;
    int r;
    int g;
    int b;
    QString texture;
    QString normal;
    bool emissive;
};

#endif // MATERIAL_H
