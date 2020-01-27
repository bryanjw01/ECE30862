#ifndef _ATTACK_H
#define _ATTACK_H

#include<iostream>
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<string>
#include<list>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

typedef struct _condition{
    string object;
    string status;
}Condition;

class Attack{
public:
    Condition condition;
    string print;
    vector<string> action;
    
    bool has_condition;
    bool has_print;
    bool has_action;
    
	Attack(xml_node<>* node){
        setupAttack(node);
	}
	virtual ~Attack(){};
private:
    void setupAttack(xml_node<>* node){
        has_condition = false;
        has_print = false;
        has_action = false;
        
        for(xml_node<>* kid = node -> first_node();
            kid; kid = kid -> next_sibling()){
            if(string(kid->name()) == "condition"){
                has_condition = true;
                for(xml_node<>* kid2 = kid -> first_node();
                    kid2; kid2 = kid2 -> next_sibling()){
                    if(string(kid2->name()) == "object"){
                        condition.object = kid2->value();
                    }
                    if(string(kid2->name()) == "status"){
                        condition.status = kid2->value();
                    }
                }
            }
            if(string(kid->name()) == "print"){
                has_print = true;
                print = kid -> value();
            }
            if(string(kid->name()) == "action"){
                has_action = true;
                string buffer = kid -> value();
                action.push_back(buffer);
            }
        }
    }
};

#endif
