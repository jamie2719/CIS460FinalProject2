#ifndef CAMERA_H
#define CAMERA_H
#include "ray.h"
#include "la.h"
//#include "jsonparser.h"





class Camera
{
public:
    Camera(float near, float far, float eye_x, float eye_y, float eye_z, float up_x, float up_y, float up_z,
           float center_x, float center_y, float center_z, float fov, float width, float height);

    ray *raycast(float px, float py);

    glm::mat4 computeViewMatrix();




private:
    float near, far;
    float eye_x, eye_y, eye_z;
    float up_x, up_y, up_z;
    float fov;
    float width, height;
    float center_x, center_y, center_z;


};

#endif // CAMERA_H
