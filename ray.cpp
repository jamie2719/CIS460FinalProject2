#include "ray.h"
//#include "vec4.h"
//#include "mat4.h"

ray::ray(glm::vec4 origin, glm::vec4 direction)
{
    this->origin = origin;
    this->direction = direction;
}

const ray ray::getTransformedCopy(glm::mat4 transformMatrix)
{
    //glm::vec4 newOrigin = transformMatrix * this->origin;
    glm::vec4 newDirection = transformMatrix * this->direction;
    ray newRay = ray(this->origin, newDirection);
    return newRay;
}

glm::vec4 ray::getOrigin() {
    return this->origin;
}

glm::vec4 ray::getDirection() {
    return this->direction;
}
