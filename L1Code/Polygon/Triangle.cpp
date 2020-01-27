#include "Triangle.h"
#include <math.h>

Triangle::Triangle(float l) : Polygon(3, l) { }

Triangle::~Triangle( ) { };

float Triangle::getArea( ) {
   return 0.433 * lenSides * lenSides;
}
