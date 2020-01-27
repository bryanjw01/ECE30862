#ifndef Item_h
#define Item_h
#include "rapidxml.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cassert>
#include "Trigger.h"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
using namespace std;
using namespace rapidxml;
struct T_O{
    string print;
    vector <string> action;
};
class Item
{
public:
    bool turnonAble;
    T_O turnon;
    Item(xml_node<> * node);
    vector <Trigger*> trigger;
    string name;
    string status;
    string description;
    string writing;
};

#endif /* Item_h */
