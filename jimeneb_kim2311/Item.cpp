#include "Item.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

Item::Item(xml_node<> * node)
{
	turnonAble = false;
	for(xml_node<> *n = node->first_node(); n; n=n->next_sibling()){
		string n_name = n->name();
		string n_value = n->value();
		
		if(n_name.compare("name") == 0){
			name = n_value;
		}
        else if(n_name.compare("description") == 0){
            description = n_value;
        }
        else if(n_name.compare("writing") == 0){
            writing = n_value;
        }
		else if(n_name.compare("status") == 0){
			status = n_value;
		}
		else if(n_name.compare("turnon") == 0){
			turnonAble = true;
			for (xml_node<> *p=n->first_node();p; p=p->next_sibling()){
				string name_p = p->name();
				string value_p = p->value();
				if(name_p.compare("print") == 0){
					turnon.print = value_p;
				}
				else if(name_p.compare("action") == 0){
					turnon.action.push_back(value_p);
				}
			}
		}
		else if(n_name.compare("trigger") == 0){
            Trigger * trigger2 = new Trigger(n);
			trigger.push_back(trigger2);
		}
	}

}
