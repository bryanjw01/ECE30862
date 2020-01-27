#include <iostream>
#include "Base.h"
using namespace std;

Base::Base( ) { }
Base::~Base( ){ }

void Base::m( ) {
   std::cout << "Base:m( )" << std::endl;
}
