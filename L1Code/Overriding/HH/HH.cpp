#include "Base.h"
#include "Derived.h"
#include <iostream>

int main (int argc, char *argv[]) { 
   Base* b = new Base( );
   Derived* d = new Derived( );
   Base* b2d = d;

   std::cout << "calling m( ) on b " << std::endl; b->m( );
   std::cout << "calling m( ) on d " << std::endl; d->m( );
   std::cout << "calling m( ) on b2d" << std::endl; b2d->m( );
}
