#ifndef SET_H
#define SET_H
#include <iostream>

class Set {
public:
   Set(int);
   Set( const Set&);
   virtual ~Set( );
   int count;
   static int copy;
   int *array;
   int size;
   int getCopyCount();
   friend Set& operator + (Set&,int);
   friend Set& operator - (Set&,int);
   friend Set& operator / (Set&,Set&);
   friend Set& operator ~ (Set&);
   friend Set& operator&(Set&,Set&);
   friend std::ostream& operator<<(std::ostream&,Set);
};
#endif /* BASE_H */
