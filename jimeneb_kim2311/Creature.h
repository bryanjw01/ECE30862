#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cassert>
#include "rapidxml.hpp"
#include "Trigger.h"
//#include "Condition.h"
#include "attack.h"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;
// typedef struct _Attack {
//     Condition* condition;
//     string print;
//     vector <string> action;
//     bool has_action;
//     bool has_print;
// }Atk;
class Creature
{
public:
    
    Creature(xml_node<> * node);
    vector <string> vulnerability;
    vector <Trigger*> trigger;
    //Atk* attack;
    //vector <Atk *> attack;
	string name;
	string status;
    vector <string> accept;
	string description;
    Attack *attack;
    
    
};


