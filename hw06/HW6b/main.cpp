#include "Base.h"
#include "Derived.h"
#include <string>
#include <iostream>
void foo(Base b) { }
void foo(Derived d) { }
void foo(Base* b) { }
void foo(Derived* d) { }

int main(void) {
     std::cout<<"1"<<std::endl;
   Base* bP = new Base( ); // LINE 1
    std::cout<<"2"<<std::endl;
   Derived* dP = new Derived( ); // LINE 2
 std::cout<<"3"<<std::endl;
   Base b; // LINE 3
 std::cout<<"4"<<std::endl;
   Derived d; // LINE 4
 std::cout<<"5"<<std::endl;
   foo(b); // LINE 5
 std::cout<<"6"<<std::endl;
   foo(d); // LINE 6
 std::cout<<"7"<<std::endl;
   foo((Base) d); // LINE 7
 std::cout<<"8"<<std::endl;
   foo(bP); // LINE 8
 std::cout<<"9"<<std::endl;
   foo(dP); // LINE 9
    std::cout<<"10"<<std::endl;
} // LINE 10 (what is printed as the program completes?
