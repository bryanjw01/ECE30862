#ifndef TRIGGER_H
#define TRIGGER_H

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cassert>
//#include "Condition.h"


using namespace rapidxml;
using namespace std;
class Trigger
{
    public:
    Trigger(xml_node<> * node);
    bool has_command;
    string command;
    int times;
    string print;
    vector <string> condition;
    vector <string> action;
    string type;
};

#endif
