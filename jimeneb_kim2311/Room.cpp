#include "Room.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "Trigger.h"

using namespace std;
using namespace rapidxml;

Room::Room(xml_node<> * node)
{
	for(xml_node<> *n = node->first_node(); n; n=n->next_sibling()){
		string n_name = n->name();
		string n_value = n->value();
		
		if(n_name.compare("name") == 0){
			name = n_value;
		}
        else if(n_name.compare("type") == 0){
            type = n_value;
        }
		else if(n_name.compare("status") == 0){
			status = n_value;
		}
		else if(n_name.compare("description") == 0){
			description = n_value;
		}
		else if(n_name.compare("border") == 0){
			B * bord = new B();
			string _name_, direction;
			for(xml_node<>* p = n -> first_node();p; p = p -> next_sibling()){
				if(string(p->name()) == "name"){
					_name_ = p -> value();
				}
				if(string(p->name()) == "direction"){
					direction = p->value();
					if(direction == "north"){
						direction = "n";
					}
					if(direction == "south"){
						direction = "s";
					}
					if(direction == "west"){
						direction = "w";
					}
					if(direction == "east"){
						direction = "e";
					}
				}
			}
			bord -> direction = direction;
			bord -> name = _name_;
			border.push_back(bord);
		}
        else if(n_name.compare("item") == 0){
            item.push_back(n_value);
        }
        else if(n_name.compare("creature") == 0){
            creature.push_back(n_value);
        }
		else if(n_name.compare("container") == 0){
			container.push_back(n_value);
		}
		else if(n_name.compare("trigger") == 0){
            Trigger *trigger2 = new Trigger(n);
            trigger.push_back(trigger2);
		}
	}

}
