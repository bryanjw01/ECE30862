// This is the main class for HW3

#include "Base.h"
#include "D1.h"
#include "D1a.h"
#include "D2.h"
#include <iostream>

int main(int argc, char **argv) {

   Base *bP = new Base( );
   D1 *d1P = new D1( );
   D1a *d1aP = new D1a( );
   D2 *d2P = new D2( );
   Base bV;
   D1 d1V;
   D1a d1aV;
   D2 d2V;

std::cout<<"Q1";bV.f1( );// Q1
std::cout<<"Q2";bV.f3( ); // Q2
std::cout<<"Q3";bV.f4( ); // Q3
std::cout<<"Q4";bV.f5( ); // Q4
std::cout<<"Q5";std::cout << bV.i << ", " << bV.j << ", " << bV.k << std::endl;// Q5

std::cout<<"Q6";d1P->f1( ); // Q6
std::cout<<"Q7";d1P->f3( ); // Q7
std::cout<<"Q8";d1P->f4( ); // Q8
std::cout<<"Q9";d1P->f5( ); // Q9
std::cout<<"Q10";std::cout << d1P->i << ", " << d1P->j << ", " << d1P->k << std::endl;// Q10

std::cout<<"Q11";d1V.f1( ); // Q11
std::cout<<"Q12";d1V.f3( ); // Q12
std::cout<<"Q13";d1V.f4( ); // Q13
std::cout<<"Q14";d1V.f5( ); // Q14
std::cout<<"Q15";std::cout << d1V.i << ", " << d1V.j << ", " << d1V.k << std::endl;// Q15

std::cout<<"Q16";d1aP->f1( ); // Q16
std::cout<<"Q17";//d1aP->f2( ); // Q17
std::cout<<"Q18";d1aP->f3( ); // Q18
std::cout<<"Q19";d1aP->f4( ); // Q19
std::cout<<"Q20";//d1aP->f5( ); // Q20
std::cout<<"Q21";//std::cout << d1aP->i << ", " << d1aP->j << ", " << d1aP->k << std::endl; // Q21

std::cout<<"Q22";d1aV.f1( ); // Q22
std::cout<<"Q23";//d1aV.f2( ); // Q23
std::cout<<"Q24";d1aV.f3( ); // Q24
std::cout<<"Q25";d1aV.f4( ); // Q25
std::cout<<"Q26";//d1aV.f5( ); // Q26
std::cout<<"Q27";//std::cout << d1aV.i << ", " << d1aV.j << ", " << d1aV.k << std::endl; // Q27

std::cout<<"Q28";d2P->f1( ); // Q28
std::cout<<"Q29";d2P->f3( ); // Q29
std::cout<<"Q30";d2P->f4( ); // Q30
std::cout<<"Q31";d2P->f5( ); // Q31
std::cout<<"Q32";std::cout << d2P->i << ", " << d2P->j << ", " << d2P->k << std::endl;// Q32

std::cout<<"Q33";d2V.f1( ); // Q33
std::cout<<"Q34";d2V.f3( ); // Q34
std::cout<<"Q35";d2V.f4( ); // Q35
std::cout<<"Q36";d2V.f5( ); // Q36
std::cout<<"Q37";std::cout << d2V.i << ", " << d2V.j << ", " << d2V.k << std::endl; // Q37

bP = d2P; 
d1P = d2P; 
bV = d2V; 

std::cout<<"Q38";bP->f1( ); // Q38
std::cout<<"Q39";bP->f2( ); // Q39
std::cout<<"Q40";bP->f3( ); // Q40
std::cout<<"Q41";bP->f4( ); // Q41
std::cout<<"Q42";bP->f5( ); // Q42

std::cout<<"Q43";bV.f1( ); // Q43
std::cout<<"Q44";bV.f2( ); // Q44
std::cout<<"Q45";bV.f3( ); // Q45
std::cout<<"Q46";bV.f4( ); // Q46
std::cout<<"Q47";bV.f5( ); // Q47
std::cout<<"Q48";std::cout << bV.i << ", " << bV.j << ", " << bV.k << std::endl; // Q48

std::cout<<"Q49";d1P->f1( ); // Q49
std::cout<<"Q50";d1P->f2( ); // Q50
std::cout<<"Q51";d1P->f3( ); // Q51
std::cout<<"Q52";d1P->f4( ); // Q52
std::cout<<"Q53";d1P->f5( ); // Q53
std::cout<<"54";std::cout << d1P->i << ", " << d1P->j << ", " << d1P->k << std::endl; // Q54

std::cout<<"Q55";d1V.f1( ); // Q55
std::cout<<"Q56";d1V.f2( ); // Q56
std::cout<<"Q57";d1V.f3( ); // Q57
std::cout<<"Q58";d1V.f4( ); // Q58
std::cout<<"Q59";d1V.f5( ); // Q59
std::cout<<"Q60";std::cout << d1V.i << ", " << d1V.j << ", " << d1V.k << std::endl; // Q60

std::cout<<"Q61";d2P->f1( ); // Q61
std::cout<<"Q62";d2P->f2( ); // Q62
std::cout<<"Q63";d2P->f3( ); // Q63
std::cout<<"Q64";d2P->f4( ); // Q64
std::cout<<"Q65";d2P->f5( ); // Q65
std::cout<<"Q66";std::cout << d2P->i << ", " << d2P->j << ", " << d2P->k << std::endl; // Q66

std::cout<<"Q67";d2V.f1( ); // Q67
std::cout<<"Q68";d2V.f2( ); // Q68
std::cout<<"Q69";d2V.f3( ); // Q69
std::cout<<"Q70";d2V.f4( ); // Q70
std::cout<<"Q71";d2V.f5( ); // Q71
std::cout<<"Q72";std::cout << d2V.i << ", " << d2V.j << ", " << d2V.k << std::endl; // Q72

std::cout<<"Q73";//bP = d1aP; // Q73
std::cout<<"Q74";//bV = d1aV; // Q74
std::cout<<"Q75";//d1P = d1aP; // Q75
std::cout<<"Q76";//d1V = d1aV; // Q76

}

