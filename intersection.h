/*Create an Intersection class which will be returned as the result of functions
 * that determine the point of intersection between a ray and some geometry in
 * your scene. Your Intersection class should contain:
 *
 * A vec3 representing the world-space point of intersection with a geometry
 * A vec3 representing the world-space surface normal at the point of intersection
 * A float which represents the t value obtained from the intersection test that
 * produced this Intersection
 * A pointer to the Geometry that produced this intersection
*/

#ifndef INTERSECTION_H
#define INTERSECTION_H
//#include "vec4.h"
#include "la.h"

class Geometry;

class Intersection
{
public:
    Intersection(glm::vec4 pointOfIntersection, glm::vec4 surfaceNormal, float t, Geometry *geometry);

    float getT();
    Geometry *getGeometry();

private:
    glm::vec4 pointOfIntersection; // should take the form of (x, y, z, 1)
    glm::vec4 surfaceNormal; // should take the form of (x, y, z, 0)
    float t;
    // pointer to Geometry
    Geometry *geometry;
};

#endif // INTERSECTION_H
