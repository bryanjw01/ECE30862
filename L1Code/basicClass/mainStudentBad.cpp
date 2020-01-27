#include "Student.h"
#include <iostream>

int main (int argc, char *argv[]) { 

   Student* s = new Student( );
   s->setName("Maria");
   s->id = -1; 

   std::cout << "s: " << s->getName( ) << ", " << s->getID( ) << std::endl;
}
