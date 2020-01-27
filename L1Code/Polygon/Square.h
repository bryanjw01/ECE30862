#ifndef Square_H_
#define Square_H_
#include "Polygon.h"
#include <string>

class Square : public Polygon {
public:
   Square(float);
   virtual ~Square( );

   float getArea( );

};
#endif /*Square_H_*/
