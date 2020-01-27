#ifndef Polygon_H_
#define Polygon_H_
#include <string>

class Polygon {
public:
   Polygon( );
   Polygon(int,float);
   virtual ~Polygon( );

   virtual float getArea( );

protected:
   int numSides;
   float lenSides;

};
#endif /*Polygon_H_*/
