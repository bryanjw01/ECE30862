#include "Creature.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "Trigger.h"
//#include "Condition.h"

using namespace std;
using namespace rapidxml;

Creature::Creature(xml_node<> * node)
{
	
	for(xml_node<> *n = node->first_node(); n; n=n->next_sibling()){
		string n_name = n->name();
		string n_value = n->value();
		
		if(n_name.compare("name") == 0){
			name = n_value;
		}
        else if(n_name.compare("description") == 0){
            description = n_value;
        }
        else if(n_name.compare("vulnerability") == 0){
            vulnerability.push_back(n_value);
        }
		else if(n_name.compare("status") == 0){
			status = n_value;
		}
		else if(n_name.compare("attack") == 0){
			attack = new Attack(n);
            
        }
		else if(n_name.compare("trigger") == 0){
            Trigger *trigger2 = new Trigger(n); 
            trigger.push_back(trigger2);
		}
	}

}
