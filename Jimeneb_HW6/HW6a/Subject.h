#ifndef SUBJECT_H
#define SUBJECT_H
#include "Observer.h"

class Subject {
public:
   Subject( );
   virtual ~Subject( );
   virtual void subscribe(Observer*)=0;
   // need an abstract subscribe function declaration 
};

#endif /* SUBJECT_H */
