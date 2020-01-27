#include "Trigger.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
//#include "Condition.h"

using namespace std;
using namespace rapidxml;

Trigger::Trigger(xml_node<> * node)
{
	has_command = false;
	times=0;
	for(xml_node<> *n = node->first_node(); n; n=n->next_sibling()){
		string n_name = n->name();
		
		if(n_name.compare("type") == 0){
			type= n->value();
			
		}
		else if(n_name.compare("command") == 0){
			
			command = n->value();
			has_command=true;
		}
		else if(n_name.compare("condition") == 0){
			//Condition *condition2=new Condition(n);
			for (xml_node<> *p=n->first_node();p; p=p->next_sibling()){
				condition.push_back(p->value());
				/*string name_p = p->name();
				string value_p = p->value();
				if(name_p.compare("has") == 0){
					condition2->has = value_p;
				}
				else if(name_p.compare("object") == 0){
					condition2->object = value_p;
				}
				else if(name_p.compare("owner") == 0){
					condition2->owner = value_p;
				}
				else if(name_p.compare("status") == 0){
					condition2->status = value_p;
				}*/

			}
			
		}
		else if(n_name.compare("print") == 0){
			print = n->value();
		}
		else if(n_name.compare("action") == 0){
			action.push_back(n->value());
		}

	}
	if(type.size()==0){
		type="permanent";
	}
}
