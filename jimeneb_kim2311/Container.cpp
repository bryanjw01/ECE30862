#include "Container.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;
Container::Container(){
	
}
Container::Container(xml_node<> * node)
{
	opened = false;
	for(xml_node<> * n = node->first_node(); n; n=n->next_sibling()){
		string n_name = n->name();
		string n_value = n->value();
        
		if(n_name.compare("name") == 0){
			name = n->value();
		}
        else if(n_name.compare("description") == 0){
            description = n->value();
        }
        else if(n_name.compare("accept") == 0){
            accept.push_back(n->value());
        }
		else if(n_name.compare("status") == 0){
			status = n->value();
		}
		else if(n_name.compare("item") == 0){
			item.push_back(n->value());
		}
		else if(n_name.compare("trigger") == 0){
            Trigger * trigger2 = new Trigger(n);
            trigger.push_back(trigger2);
		}
	}

}


