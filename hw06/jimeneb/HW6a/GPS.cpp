#include <iostream>
#include "GPS.h"

GPS::GPS(int s) : x(0.0),y(0.0),size(s),idx(0){
   obs = new Observer*[size];
}
void GPS::subscribe(Observer* o){
    if(idx>=size){
        std::cout<<"ERROR: obs full, size: "<<size <<", id: "<<idx<<std::endl;
    }
    else{
        obs[idx]=o;
        idx++;
    }
}
void GPS::update(double xx, double yy) {
    this->x=xx;
    this->y=yy;
    notify();
}
void GPS::notify( ){
    for(int i=0;i<size;i++){
        obs[i]->notify(x,y);
    }
}
GPS::~GPS( ) {
   delete obs;
}
