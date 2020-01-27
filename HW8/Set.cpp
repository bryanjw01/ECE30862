#include "Set.h"
#include<iostream>
int Set::copy=0;
Set::Set(int s):count(0),size(s+1){
    array=new int[size];
    for(int i=0;i<size;i++){
        array[i]=0;
    }
}
Set::Set(const Set& s):size(s.size),count(s.count){
    copy++;
    array=new int[size];
    for(int i=0;i<size;i++){
        array[i]=s.array[i];
    }  
}
Set& operator+(Set& a,int num){
   for(int i=0;i<a.count;i++){
        if(a.array[i]==num){
            return a;
        }
   }
    a.array[a.count]=num;
    a.count++;
    return a;
}
Set &operator-(Set& a,int num){
    if(a.count==0){
        return a;
    }
    for(int i=0;i<a.count;i++){
        if(a.array[i]==num){
            for(int j=i;j<(a.count-1);j++){
                    std::swap(a.array[j],a.array[j+1]);
            }    
            a.array[a.count]=0;
            --a.count;
            return a;
        }
    }
    return a;
}
Set &operator/(Set& a, Set& b){
    
    for(int j=0;j<a.count;j++){
        for(int i=0;i<b.count;i++){
            if(a.array[j]==b.array[i]){
                for(int h=j;h<(a.count-1);h++){
                    std::swap(a.array[h],a.array[h+1]);
                }    
                a.array[a.count]=0;
                --a.count;   
                j--;
            }
        }
    }
    return a;
}
int Set::getCopyCount(){
     return copy;
}
std::ostream&  operator<<(std::ostream & b,Set a){
    for(int i=0;i<a.count;i++){
        if(i<a.count-1){
            b<<a.array[i]<<", ";
        }
        else{
            b<<a.array[i]<<std::endl;
        }
    }
    return b;
}
Set& operator ~ (Set& a){
    Set *temp=new Set(a.size-1);
    int t=0;
    int h=0;
    for(int i=0;i<a.size;i++){
        for(int j=0;j<a.count;j++){
            if(t==a.array[j]){
                t+=1;
                h+=1;
                break;
            }
        }
        temp->array[i]=t;
        t+=1;
    }
    temp->count=temp->size-h;
    return *temp;
}
Set& operator&(Set& a,Set& b){
    Set temp=Set(a.count-1);
    int k=0;
    for(int i=0;i<a.count;i++){
        for(int j=0;j<b.count;j++){
            if(a.array[i]==b.array[j]){
                temp.array[k]=a.array[i];
                k++;
            }
        }
    }
    temp.count=k;
    a.array=temp.array;
    a.count=temp.count;
    return a;
}
Set::~Set(){
    delete[] array;
}