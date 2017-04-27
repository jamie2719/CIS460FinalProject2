#include "camera.h"
#include "la.h"
#include "math.h"

Camera::Camera() {

}

Camera::Camera(float near, float far, float eye_x, float eye_y, float eye_z, float up_x, float up_y, float up_z,
               float center_x, float center_y, float center_z, float fov, float width, float height) {
    this->near = near;
    this->far = far;
    this->eye_x = eye_x;
    this->eye_y = eye_y;
    this->eye_z = eye_z;
    this->up_x = up_x;
    this->up_y = up_y;
    this->up_z = up_z;
    this->center_x = center_x;
    this->center_y = center_y;
    this->center_z = center_z;
    this->fov = fov;
    this->width = width;
    this->height = height;
}

ray Camera::raycast(float px, float py, float width, float height) {
//    px = 256;
//    py = 256;
   // compute viewMatrix
    glm::mat4 viewMat = glm::transpose(computeViewMatrix());

   float sx = (2.f * px/width) - 1.0f;
   float sy = 1.0f - (2.f * py/height);

   glm::vec4 eye = glm::vec4(this->eye_x, this->eye_y, this->eye_z, 1);
   float t = 5.f; // can be any float apparently???

  // glm::mat4 transposeViewMatrix = glm::transpose(viewMat);

   glm::vec4 ref = eye + t * viewMat[2];
   float len =  (float)((ref - eye).length());
   float alpha = this->fov / 2.0;
   float radians = tanf(alpha * M_PI / 180.0);
   glm::vec4 V = viewMat[1] * len * radians;
   glm::vec4 H = viewMat[0] * len * (width/height) * radians;
   glm::vec4 p = ref + (sx * H) + (sy * V);

   glm::vec4 rayOrigin = eye;
   glm::vec4 rayDirection = glm::vec4(glm::normalize(glm::vec3(p) - glm::vec3(eye)), 0);

   ray returnedRay = ray(rayOrigin, rayDirection);
   return returnedRay;
}

glm::mat4 Camera::computeViewMatrix() {
    glm::vec3 F = glm::vec3(this->center_x - this->eye_x,
                            this->center_y - this->eye_y,
                            this->center_z - this->eye_z);
    glm::vec3 normF = glm::normalize(F);
    glm::vec3 UP = glm::vec3(this->up_x, this->up_y, this->up_z);
    glm::vec3 normUP = glm::normalize(UP);

    // compute cross product
    glm::vec3 s = glm::normalize(glm::cross(normF, normUP));
    glm::vec3 u = glm::normalize(glm::cross(s, normF));

    // construct matrix now
    glm::vec4 v1 = glm::vec4(s[0], u[0], normF[0], 0);
    glm::vec4 v2 = glm::vec4(s[1], u[1], normF[1], 0);
    glm::vec4 v3 = glm::vec4(s[2], u[2], normF[2], 0);
    glm::vec4 v4 = glm::vec4(0, 0, 0, 1);
    glm::mat4 Ori = glm::mat4(v1, v2, v3, v4);

    glm::vec4 vec1 = glm::vec4(1, 0, 0, 0);
    glm::vec4 vec2 = glm::vec4(0, 1, 0, 0);
    glm::vec4 vec3 = glm::vec4(0, 0, 1, 0);
    glm::vec4 vecFour = glm::vec4(-this->eye_x, -this->eye_y, -this->eye_z, 1.f);
    glm::mat4 T = glm::mat4(vec1, vec2, vec3, vecFour);
    glm::mat4 viewMatrix = T * Ori;
    return viewMatrix;
}





