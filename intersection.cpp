#include "intersection.h"

Intersection::Intersection(glm::vec4 pointOfIntersection, glm::vec4 surfaceNormal, float t, Geometry *geometry)
// points: use 1 as w value, only direction: use 0 as w value
{
    this->pointOfIntersection = pointOfIntersection;
    this->surfaceNormal = surfaceNormal;
    this->t = t;
    this->geometry = geometry;
}

float Intersection::getT() {
    return this->t;
}


