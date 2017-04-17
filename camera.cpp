#include "camera.h"
#include "la.h"

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

ray Camera::raycast(float px, float py) {
   // compute viewMatrix

   float sx = (2 * px/this->width) -1;
   float sy = 1 - (2 * py/this->height);
   glm::vec4 eye = glm::vec4(this->eye_x, this->eye_y, this->eye_z, 0);
   //glm::vec4 ref = eye + 3.0 *

}

glm::mat4 Camera::computeViewMatrix() {
   /* float l = 5.0;
    float r = 10.0;
    float t = 7.0;
    float b = 2.0;
    // ARBITRARY VALUES???
    float val1 = (2 * this->near) / (r - l);
        float val2 = (2 * this->near) / (t - b);
        float val3 = (r + l) / (r - l);
        float val4 = (t + b) / (t - b);
        float val5 = this->far / (this->far - this->near);
        float val6 = -(this->far * this->near) / (this->far - this->near);
        glm::vec4 v1 = vec4(val1, 0, 0, 0);
        glm::vec4 v2 = vec4(0, val2, 0, 0);
        glm::vec4 v3 = vec4(val3, val4, val5, 1);
        glm::vec4 v4 = vec4(0, 0, val6, 0);
        glm::mat4 projectionMatrix = mat4(v1, v2, v3, v4);*/

        // compute view matrix and store
        // compute F vector from doc (center - eye)
        glm::vec3 F = glm::vec3(this->center_x - this->eye_x, this->center_y - this->eye_y,
                           this->center_z - this->eye_z);
        glm::vec3 normF = F / (float)F.length();
        glm::vec3 UP = glm::vec3(this->up_x, this->up_y, this->up_z);
        glm::vec3 normUP = UP / (float)UP.length();
        // compute cross product
        glm::vec3 s = glm::cross(normF, normUP);
        glm::vec3 normS = s / (float)s.length();
        glm::vec3 u = glm::cross(normS, normF);

        // construct matrix now
        glm::vec4 v1 = glm::vec4(s[0], u[0], normF[0], 0);
        glm::vec4 v2 = glm::vec4(s[1], u[1], normF[1], 0);
        glm::vec4 v3 = glm::vec4(s[2], u[2], normF[2], 0);
        glm::vec4 v4 = glm::vec4(0, 0, 0, 1);
        glm::mat4 O = glm::mat4(v1, v2, v3, v4);

        glm::vec4 vec1 = glm::vec4(1, 0, 0, 0);
        glm::vec4 vec2 = glm::vec4(0, 1, 0, 0);
        glm::vec4 vec3 = glm::vec4(0, 0, 1, 0);
        glm::vec4 vecFour = glm::vec4(-this->eye_x, -this->eye_y, -this->eye_z, 1);
        glm::mat4 T = glm::mat4(vec1, vec2, vec3, vecFour);
        glm::mat4 viewMatrix = O * T;
        return viewMatrix;
}



