#ifndef DERIVED_H_
#define DERIVED_H_
#include "Base.h"

class Derived : public Base {
public:
   Derived( );
   virtual ~Derived( );
    virtual void f1();
    void f2();
   // add necessary functions herea
   

};
#endif /*DERIVED_H*/
