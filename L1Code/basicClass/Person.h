#ifndef PERSON_H_
#define PERSON_H_
#include <string>
using namespace std;

class Person {
public:
   std::string name;

   Person( );
   virtual ~Person( );

   void setName(string);
   string getName( );

};
#endif /* PERSON_H_ */
