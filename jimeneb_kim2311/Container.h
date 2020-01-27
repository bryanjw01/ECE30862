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
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;
class Container
{
public:
	Container();
	Container(xml_node<> * node);
    string status;
    string description;
	string name;
	vector <string> accept;
	vector <string> item;
	vector <Trigger*> trigger;
	bool opened;
};
