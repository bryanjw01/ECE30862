#include "Polygon.h"
#include "Square.h"
#include "Triangle.h"
#include "Pentagon.h"
#include <iostream>

int main (int argc, char *argv[]) { 

   Polygon* p[4];
   float area = 0;

   p[0] = new Square(4.0);
   p[1] = new Triangle(4.0);
   p[2] = new Polygon(8, 4.0);
   p[3] = new Pentagon(4.0);

   for (int i=0; i <4; i++) {
      area += p[i]->getArea( );
      std::cout << "area of poly " << i << " = " << p[i]->getArea( ) << std::endl;
   }
   
   std::cout << "total area = " << area << std::endl; 
}
