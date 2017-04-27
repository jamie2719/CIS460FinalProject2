#ifndef MESH_H
#define MESH_H
#include "geometry.h"
#include "tiny_obj_loader.h"

class Mesh : public Geometry
{
public:
    Mesh(QString name, glm::mat4 transform_mat, Material material, QString type);

    virtual Intersection getIntersection(ray inputRay);

    glm::mat4 computeTextureToObjectMatrix();

    const char* getObjFilename();

    void setObjFilename(const char* filename);

    void loadObject();

//    virtual Material getMaterial();
private:
   // glm::mat4 transform_mat;
   // QString name;
   // Material material;
    const char* objfilename;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;


};

#endif // MESH_H
