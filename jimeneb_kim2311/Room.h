#ifndef ROOM_H
#define ROOM_H

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
struct B {
    string direction;
    string name;
};
class Room {
public:
    Room(xml_node<> * node);
    string description;
    string status;
    string name;
    string type;
    vector <B *> border;
    vector <string> item;
    vector <string> container;
    vector <string> creature;
    vector <Trigger*> trigger;
};

#endif /*ROOM_H_*/
