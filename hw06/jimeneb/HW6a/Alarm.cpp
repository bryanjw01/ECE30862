#include <iostream>
#include <cmath>
#include "Alarm.h"

Alarm::Alarm(Subject * s, int i, double xx, double yy, double alarm):id(i),x(xx),y(yy),soundAlarm(alarm) {  
    s->subscribe(this);
}
void Alarm::notify(double xx,double yy){
    double delta=0; 
    delta=std::sqrt(pow(xx-x,2)+pow(yy-y,2));
    if(delta>soundAlarm){
        std::cout<<"Alarm sounded: moved "<<delta<<" meters"<<std::endl;
    }
}

Alarm::~Alarm( ) { 

}
