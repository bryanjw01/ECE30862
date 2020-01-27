#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
   Observer( );
   virtual ~Observer( );
   virtual void notify(double,double)=0;
   // need an abstract notify function here
};

#endif /* OBSERVER_H */
