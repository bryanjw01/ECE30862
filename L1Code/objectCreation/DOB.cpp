#include "DOB.h"
#include <iostream>

   DOB::DOB(int m, int d, int y) : month(m), day(d), year(y)  {
      monthToStr[0]="Jan"; monthToStr[1]="Feb"; monthToStr[2]="Mar"; 
      monthToStr[3] = "Apr"; monthToStr[4]="May"; monthToStr[5]="Jun"; 
      monthToStr[6]="Jul"; monthToStr[7] = "Aug"; monthToStr[8]="Sep"; 
      monthToStr[9]="Oct"; monthToStr[10]="Nov"; monthToStr[11] = "Dec";
   }
     
   DOB::~DOB( ) { };
   void DOB::print( ) {
      std::cout << monthToStr[month] << " " << day << ", " << year << std::endl;
   }
