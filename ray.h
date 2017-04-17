#ifndef RAY_H
#define RAY_H
//#include "vec4.h"
//#include "mat4.h"
#include "la.h"

class ray
{
public:
    ray(glm::vec4 origin, glm::vec4 direction);
    const ray getTransformedCopy(glm::mat4 transformMatrix);
    glm::vec4 getOrigin();
    glm::vec4 getDirection();

private:
    glm::vec4 origin;
    glm::vec4 direction;
};


#endif // RAY_H
