#ifndef STUDENT_H_
#define STUDENT_H_
#include "Person.h"

class Student : public Person {
public:
   int id;

   Student( );
   virtual ~Student( );

   void setID(int);
   int getID( );

};
#endif /* STUDENT_H_ */
