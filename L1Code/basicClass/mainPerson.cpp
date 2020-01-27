#include "Person.h"
#include <iostream>

int main (int argc, char *argv[]) { 

   Person* p1 = new Person( );
   Person* p2 = new Person( );
   p1->setName("Bill");
   p2->setName("Maria");

   std::cout << "p1:" << p1->getName( ) << std::endl;
   std::cout << "p2:" << p2->getName( ) << std::endl;
}
