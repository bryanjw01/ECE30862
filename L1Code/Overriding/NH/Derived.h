#ifndef DERIVED_H_
#define DERIVED_H_
#include "Base.h"
using namespace std;

class Derived : public Base {
public:

   Derived( );
   virtual ~Derived( );
   virtual void m( );

};

#endif /* DERIVED_H_ */
