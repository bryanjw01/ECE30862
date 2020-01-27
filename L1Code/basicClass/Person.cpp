#include "Person.h"

Person::Person( ) { }
Person::~Person( ){ }

void Person::setName(string n) {
   name = n;
}

string Person::getName( ) {
   return name;
};
