// This is the main class for HW2
// This assignment demonstrates inheritance, overriding and polymorphism
//
// Modify the Base and Derived classes to get the output indicated below.
#include "Base.h"
#include "Derived.h"
#include <iostream>

int main(int argc, char **argv) {
   Base b1;
   Derived d1;
   b1.f3();
   d1.f3();
   b1=d1;
   b1.f1();
   d1.f1();
    Base *b = new Base( );
    Derived *d = new Derived( );
    b->f1( ); // prints "Base f1"
    b->f2( ); // prints "Base f2"
    b->f3();
    d->f1( ); // prints "Base f1"
    d->f2( ); // prints "Derived f2"
    d->f3();
//    d=b;
//    b->f1( ); // prints "Base f1"
//    b->f2();
//    d1->f1();
}

