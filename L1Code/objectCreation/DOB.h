#ifndef DOB_H_
#define DOB_H_
#include <string>

class DOB {

public:
   DOB(int, int, int);
   virtual ~DOB( );
    void print( );

private:
   std::string monthToStr[12];
   int day;
   int month;
   int year;
};
#endif /* DOB */
