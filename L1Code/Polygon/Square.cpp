#include "Square.h"
#include <math.h>

Square::Square(float l) : Polygon(4, l) { }

Square::~Square( ) { };

float Square::getArea( ) {
   return lenSides * lenSides;
}
