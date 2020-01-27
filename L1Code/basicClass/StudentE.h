#ifndef STUDENT_H_
#define STUDENT_H_
#include "Person.h"

class Student : public Person {

public:
   Student( );
   virtual ~Student( );

   void setID(int);

   int getID( );

private:
   int id;

};
#endif /* STUDENT_H_ */
