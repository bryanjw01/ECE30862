#include "DOB.h"

int main (int argc, char *argv[]) { 

   DOB *dp = new DOB(3,4,2020);
   DOB dv(1,2,2020); 

   dp->print( );
   dv.print( );
}
