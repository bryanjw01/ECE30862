#include "Student.h"
#include <iostream>

Student::Student( ) { }
Student::~Student( ) { }

void Student::setID(int i) {
   if (id > 0) id = i;
   std::cout << "Err, id < 0 " << i << std::endl;
}

int Student::getID( ) {
   return id;
};
