#include <iostream>
#include "Base.h"
#include "Derived.h"
using namespace std;

Derived::Derived( ) { }
Derived::~Derived( ){ }

void Derived::m( )   {
   std::cout << "Derived:m( )" << std::endl;
}
