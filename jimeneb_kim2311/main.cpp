#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cassert>
#include "Room.h"
#include "Container.h"
#include "Creature.h"
#include "Item.h"
#include "Trigger.h"
#include "attack.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_iterators.hpp"

using namespace rapidxml;
using namespace std;


bool End_Game();
void checkAction(string action);
bool Check_Trigger();
bool Check_Trigger(string input);
void Check_Input(string input);
void take_item(string input);
void check_inventory();
void direction(string input);
void open_item(string input);
void read_item(string input);
void attack(string input);
void put(string input);
void turn_on(string input);
void drop_item(string input);
void add_helper(const string input);
void delete_helper(const string input);
void update_helper(const string input);
void check_quit(string input);
void Check_Input2(string input);
bool Check_Trigger_helper(string object,string status);
bool Check_Trigger_helper(string object,string has,string owner);


bool finish=false;

//vector for variables pointing to classes
vector <string> v_inventory;
vector <Room*> v_room;
vector <Container*>v_container;
vector<Creature*> v_creature;
vector <Item*> v_item;

//Getting access to function inside classes.
//Also going to be used in multiple functions as a place holder.
//Will keep track of the current room that the player is in.
Room * room;
Trigger* trigger;

int main(int argc,char * argv[]){
	
	//Getting access to function inside classes 
	Container * container;
	Creature * creature;
	Item * item;
	
	//parsing xml file
	file<> xmlFile(argv[1]); 
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
	
	//getting access to the DOM tree
	xml_node<> *node =doc.first_node();
	
	//Going through the xml file and assigning it to variables that have access to classes
	for (xml_node<> *temp = node->first_node(); temp; temp = temp->next_sibling()){
		
		if(temp->name()==string("room")){
			room=new Room(temp);
			v_room.push_back(room);
			
		}
		
		else if(temp->name()==string("container")){
			container=new Container(temp);
			v_container.push_back(container);

		}
		
		else if(temp->name()==string("item")){
			item=new Item(temp);
			v_item.push_back(item);
		}
		
		else if(temp->name()==string("creature")){
			creature=new Creature(temp);
			v_creature.push_back(creature);
		}

	}

	
	string input;
	room=v_room[0];
    cout<< room-> description<<endl;
	while(true){
        
		if(End_Game()){
			break;
		}
        
		Check_Trigger();
			
		
         
		if(End_Game()){
			break;
		}

		getline(cin,input);
		
		check_quit(input);
        
		if(End_Game()){
			break;
		}
        
		if(Check_Trigger(input)){
			continue;
		}
		
		 
		if(End_Game()){
			break;
		}
        
		Check_Input(input);
		
		if(End_Game()){
			break;
		}

    }

    return EXIT_SUCCESS;
}
void check_quit(string input){
	if(input.compare("q")==0){
		finish=true;
	}
}
void check_inventory(){
	cout<<"Inventory: ";
	if(v_inventory.size()!=0){
		for(int i=0;i<v_inventory.size();i++){
			if(i==v_inventory.size()-1){
				cout<<v_inventory[i]<<".";
			}
			else{
				cout<<v_inventory[i]<<", ";
			}
		}
		cout<<endl;
	}
	else{
		cout<< "empty." << endl;
		return;
	}
}

bool End_Game(){
	
	if(finish){
		return true;
	}
	
	return false;
}

void drop_item(string input){
	bool found=false;
	if(input.compare("drop")==0){
		cout<<"What do you want to drop?"<<endl;
		getline(cin,input);
	}
	else{
		input=input.erase(0,5);
	}
	if(v_inventory.size()==0){
		cout<<"Inventory is empty. Can't drop any items."<<endl;
		return;
	}
	for(int i=0;i<v_inventory.size();i++){
		if(v_inventory[i]==input){
			(room -> item).push_back(input);
			v_inventory.erase(v_inventory.begin()+i);
			found=true;
			break;
		}
	}
	if(found){
		cout<<input<<" was dropped from inventory."<<endl;
	}
	else{
		cout<<input<<" was not found in inventory."<<endl;
	}

}

void take_item(string input){
	if(input.compare("take")==0){
		cout<<"What do you want to take?"<<endl;
		getline(cin,input);
	}
	else{
		input=input.erase(0,5);
	}
	for(int i=0;i<(room->item).size();i++){
		if(room->item[i].compare(input)==0){
			v_inventory.push_back(room->item[i]);
			cout<<"Item "<<room->item[i]<<" added to inventory"<<endl;
			(room->item).erase((room->item).begin()+i);	
			return;
		}
	}
	for(int i=0;i<(room->container).size();i++){
		for(int j=0;j<v_container.size();j++){
			if(room->container[i].compare(v_container[j]->name)==0){
				for(int k=0;k<v_container[j]->item.size();k++){
					if(v_container[j]->item[k].compare(input)==0&&(v_container[j]->status.compare("unlocked")==0)){
						cout<<"Item "<<input<<" added to inventory"<<endl;
						v_inventory.push_back(input);
						v_container[j]->item.erase(v_container[j]->item.begin()+k);
						return;
					}
				}
			}
		}
	}
	cout<<"couldn't find "<<input<<endl;

}

void read_item(string input){
	bool exist=false;

	if(input.compare("read")==0){
		cout<<"What do you want to read?"<<endl;
		getline(cin,input);
	}

	else{
		input=input.erase(0,5);
	}

	for(int i=0;i<v_inventory.size();i++){
		
		if(v_inventory[i].compare(input)==0){
			exist=true;
		}

	}
	
	if(exist){
		for(int i=0;i<v_item.size();i++){
			
			if(v_item[i]->name.compare(input)==0){
				
				if(v_item[i]->writing.size()>0){
					cout<<v_item[i]->writing<<endl;
					return;
				}
				
				else{
					cout<<"Item cannot be read"<<endl;
					return;
				}
				
			}
		}
		
	}
	cout<<"There is no such item."<<endl;
}
	
void Check_Input(string input){
	
	if(input.compare("q")==0){
		finish=true;
	}

	if(input.compare("n")==0||input.compare("s")==0||input.compare("e")==0||input.compare("w")==0){
		direction(input);
	}

	else if(input.compare("i")==0){
		check_inventory();
	}

	else if(input.compare("take")==0||input.substr(0,5).compare("take ")==0){
		take_item(input);
	}

	else if(input.compare("open")==0|| input.substr(0,5).compare("open ")==0){
		open_item(input);
	}

	else if(input.compare("read")==0||input.substr(0,5).compare("read ")==0){
	 	read_item(input);
	}

	else if(input.compare("drop")==0||input.substr(0,5).compare("drop ")==0){
		drop_item(input);
	}

	else if(input.compare("put")==0||input.substr(0,4).compare("put ")==0){
		put(input);
	}

	else if(input.compare("turn on")==0||input.substr(0,8).compare("turn on ")==0){
		turn_on(input);
	}

	else if(input.compare("attack")==0||input.substr(0,7).compare("attack ")==0){
		attack(input);
	}

	else{
		cout<<"Invalid input."<<endl;
	}

}

void Check_Input2(string input){
	
	if(input.compare("q")==0){
		finish=true;
	}

	if(input.compare("n")==0||input.compare("s")==0||input.compare("e")==0||input.compare("w")==0){
		direction(input);
	}

	else if(input.compare("i")==0){
		check_inventory();
	}

	else if(input.compare("take")==0||input.substr(0,5).compare("take ")==0){
		take_item(input);
	}

	else if(input.compare("open")==0|| input.substr(0,5).compare("open ")==0){
		open_item(input);
	}

	else if(input.compare("read")==0||input.substr(0,5).compare("read ")==0){
	 	read_item(input);
	}

	else if(input.compare("drop")==0||input.substr(0,5).compare("drop ")==0){
		drop_item(input);
	}

	else if(input.compare("put")==0||input.substr(0,4).compare("put ")==0){
		put(input);
	}

	else if(input.compare("turn on")==0||input.substr(0,8).compare("turn on ")==0){
		turn_on(input);
	}

	else if(input.compare("attack")==0||input.substr(0,7).compare("attack ")==0){
		attack(input);
	}
}

void direction(string input){
	for(int i=0;i<room->border.size();i++){
		if(room->border[i]->direction==input){
			for(int j=0;j<v_room.size();j++){
				if(v_room[j]->name==room->border[i]->name){
					room=v_room[j];
					if(v_room[j]->description.size()!=0){
						cout<<v_room[j]->description<<endl;
					}
					return;
				}
			}
		}
	}
	cout<<"Can't go that way."<<endl;
}
void checkAction(string action){
    if(action.find("Add") != string::npos){
       add_helper(action);
        return;
    }
    if(action.find("Delete") != string::npos){
        delete_helper(action);
        return;
    }
    if(action.find("Update") != string::npos){
       update_helper(action);
        return;
    }
    if(action == "Game Over"){
		cout<<"victory"<<endl;
		finish=true;
        return;
    }
    Check_Input2(action);
}
void attack(string input){
	string input2;
	string monster; 
	string weapon;
	bool creature=false;
	bool item=false;
	if(input.compare("attack")==0){
		cout<<"who do you want to attack?"<<endl;
		getline(cin,input);
		cout<<"what item do you want to use?"<<endl;
		getline(cin,input2);
	}
	else{
		input=input.erase(0,7);
		int index=input.find(" ");
		input2=input;
		monster=input.substr(0,index);
		weapon=input2.erase(0,index+6);
	}
	int i,j;
    for(i = 0; i < room -> creature.size(); i++){
        if(room -> creature[i] == monster){ break; }
    }
    
    if(i == room -> creature.size()){
        cout<<"There is no such creature called "<<monster<<" here."<<endl;
        return;
    }
    
    for(i = 0; i<v_inventory.size(); i++){
        if(v_inventory[i] == weapon){ break; }
    }
    
    if(i == v_inventory.size()){
        cout<<"There is no such thing called "<<weapon<<" in your inventory."<<endl;
        return;
    }
    cout<<"You assault the "<<monster<<" with the "<<weapon<<endl;
    
    for(i = 0; i<v_creature.size(); i++){
        if(v_creature[i]->name == monster){ break;}
    }
    for(j = 0; j < v_creature[i]->vulnerability.size();j++){
        if(v_creature[i]->vulnerability[j] == weapon){ break;}
    }
    
    if(j == v_creature[i]->vulnerability.size()){
        cout<<"It seems "<<weapon<<" is useless to "<<monster<<endl;
        return;
    }
    
    if(v_creature[i]->attack == NULL){
        return;
    }
    if(v_creature[i]->attack->has_condition){
        
        string object = v_creature[i]->attack->condition.object;
       
        string status = v_creature[i]->attack->condition.status;
        bool found = false;
        bool match = false;
        for(j = 0; j < v_item.size(); j++){
            if(v_item[j]->name == object){
                found = true;
                match = v_item[j]->status == status;
                break;
            }
        }
        if(!found){
            for(j = 0; j < v_room.size(); j++){
                if(v_room[j]->name == object){
                    found = true;
                    match = v_room[j]->status == status;
                    break;
                }
            }
        }
        if(!found){
            for(j = 0; j < v_container.size(); j++){
                if(v_container[j]->name == object){
                    found = true;
                    match = v_container[j]->status == status;
                    break;
                }
            }
        }
        if(!found){
            for(j = 0; j < v_creature.size(); j++){
                if(v_creature[j]->name == object){
                    found = true;
                    match = v_creature[j]->status == status;
                    break;
                }
            }
        }
        
        if(!match){
            cout<<"You need make sure "<<object<<" is "<<status<<endl;
            return;
        }
    }
    
    if(v_creature[i]->attack->has_print){
        cout<<v_creature[i]->attack->print<<endl;
    }
    if(v_creature[i]->attack->has_action){
        for(j = 0; j<v_creature[i]->attack->action.size();j++){
            checkAction(v_creature[i]->attack->action[j]);
        }
    }
	return;
}

void put(string input){
	string object;
	string container;
	if(input.compare("put")==0){
		cout<<"what object do you want to put?"<<endl;
		getline(cin,object);
		cout<<"Where do you wnat to put the object?"<<endl;
		getline(cin,container);
	}
	else{
		int size=0;
		input=input.erase(0,4);
		size=input.find("in");
		object=input.substr(0,size-1);
		input.erase(0,size+3);
		container=input;
	}
	for(int i=0;i<v_inventory.size();i++){
		if(object.compare(v_inventory[i])==0){
			for(int j=0;j<room->container.size();j++){
				if(room->container[j]==container){
					for(int k=0;k<v_container.size();k++){
						if(v_container[k]->name==container){
							for(int l=0;l<v_container[k]->accept.size();l++){
								if(v_container[k]->accept[l].compare(object)==0){
									v_inventory.erase(v_inventory.begin()+i);
									v_container[k]->item.push_back(object);
									cout<<object<<" was put in "<<container<<endl;
									return;
								}
								if(v_container[k]->status==""||v_container[k]->status=="unlocked"){	
									v_container[k]->status="unlocked";
									cout<<object<<" was put in "<<container<<endl;
									return;
								}
							}
							if(v_container[k]->accept.size()==0){
								v_inventory.erase(v_inventory.begin()+i);
								v_container[k]->item.push_back(object);
								cout<<object<<" was put in "<<container<<endl;
								return;
							}
							cout<<"cant put item in "<<container<<endl;
							return;
						}
						
					}
					cout<<container<<" not found"<<endl;
						return;
				}
			}
		}
	}
	cout<<"Item not in inventory"<<endl;
}

void turn_on(string input){
	if(input.compare("turn on")==0){
		cout<<"What do you want to turn on?"<<endl;
		getline(cin,input);
	}
	else{
		input=input.erase(0,8);
	}
	for(int i=0;i<v_inventory.size();i++){
		if(input==v_inventory[i]){
			for(int j=0;v_item.size();j++){
				if(v_item[j]->name.compare(input)==0){
					if(v_item[j]->turnonAble==false){
						cout<<"item cannot be turn on"<<endl;
						return;
					}
					else{
						cout<<"item got turned on"<<endl;
						cout<<v_item[j]->turnon.print<<endl;
						for(int k=0;k<(v_item[j]->turnon.action).size();k++){
							checkAction(v_item[j]->turnon.action[k]);
							if(v_item[j]->turnon.action[k].find("Update")!=-1){
								int size=v_item[j]->turnon.action[k].find("to ");
								v_item[j]->status=v_item[j]->turnon.action[k].substr(size+3);
							}
							
						}
						
						return;
					}
				}
			}
		}
	}
	
	cout<<"could not find item in inventory"<<endl;
	
}

void open_item(string input){
	if(input.compare("open")==0){
		cout<<"what do you want to open?"<<endl;
		getline(cin,input);
	}
	else{
		input=input.erase(0,5);
	}
	if(input.compare("exit")==0){
		if(room->type.compare("exit")==0){
			cout<<"Game Over"<<endl;
			finish=true;
		}
		else{
			cout<<"invalid"<<endl;
		}
		return;
	}
	for(int i=0;i<room->container.size();i++){
		if(room->container[i].compare(input)==0){
			for(int j=0;j<v_container.size();j++){
				if(v_container[j]->name==input){
					if(v_container[j]->status=="locked"){
						cout<<input<<"cant be open because its locked"<<endl;
					}
					else{
						v_container[j]->status="unlocked";
						cout<<v_container[j]->name;
						for(int k=0;k<v_container[j]->item.size();k++){
							if(k==0){
								cout<<" contains: "<<v_container[j]->item[k];
							
							}
							else if(k==v_container[j]->item.size()-1){
								cout<<", "<<v_container[j]->item[k]<<".";;
								
							}
							else{
								cout<<", "<<v_container[j]->item[k];
							}
						}
						if(v_container[j]->item.size()==0){
						cout<<"is empty"<<endl;
						return;
						}
						cout<<endl;
						return;
					}
					
				}
			}
		}
	}
	cout<<input<<"could not be found"<<endl;
}

void add_helper(const string input){
	string temp=input;
	string object;
	string r_c;
	int size=0;
	if(temp.find("Add")==-1){
		return;
	}
	else{
		temp=temp.erase(0,4);
		size=temp.find("to");
		object=temp.substr(0,size-1);
		r_c=temp.substr(size+3);
	}   
	for(int i=0;i<v_item.size();i++){
		if(v_item[i]->name==object){
			for(int j=0;j<v_room.size();j++){
				if(r_c.compare(v_room[j]->name)==0){
					v_room[j]->item.push_back(object);
					room=v_room[j];
					return;
				}
			}
			for(int j=0;j<v_container.size();j++){
				if(r_c.compare(v_container[j]->name)==0){
					v_container[j]->item.push_back(object);
					return;
				}
			}
		}
	}
	for(int i=0;i<v_creature.size();i++){
		if(v_creature[i]->name==object){
			for(int j=0;j<v_room.size();j++){
				if(r_c.compare(v_room[j]->name)==0){
					v_room[j]->creature.push_back(object);
					return;
				}
			}
		}
	}
	for(int i=0;i<v_container.size();i++){
		if(v_container[i]->name==object){
			for(int j=0;j<v_room.size();j++){
				if(r_c.compare(v_room[j]->name)==0){
					v_room[j]->container.push_back(object);
					return;
				}
			}
		}
	}
	for(int i;i<v_room.size();i++){
		if(room->name==v_room[i]->name){
			room=v_room[i];
		}
	}
}

void delete_helper(const string input){
	string temp =input;
	
	if(temp.find("Delete")==-1){
		
		return;
	}
	else{
		temp=temp.erase(0,7);	
		
	}
	for(int i=0;i<v_room.size();i++){
		
		if(v_room[i]->name.compare(temp)==0){
			
			for(int k=0;k<v_room[i]->border.size();k++){
				
				if(v_room[i]->border[k]->name.compare(temp)==0){
					
					v_room[i]->border.erase(v_room[i]->border.begin()+k);
				}
			}
			
		}
	}
	for(int i=0;i<v_creature.size();i++){
		
		if(v_creature[i]->name.compare(temp)==0){
			for(int k=0;k<v_room.size();k++){
				for(int j=0;j<v_room[k]->creature.size();j++){
					if(v_room[k]->creature[j].compare(temp)==0){
						v_room[k]->creature.erase(v_room[k]->creature.begin()+j);
					}
				}
			}
		}
	}
	for(int i=0;i<v_item.size();i++){
		
		if(v_item[i]->name.compare(temp)==0){
			
			for(int k=0;k<v_room.size();k++){
				
				for(int j=0;j<v_room[k]->item.size();j++){
					
					if(v_room[k]->item[j].compare(temp)==0){
						
						v_room[k]->item.erase(v_room[k]->item.begin()+j);
					}
				}
			}
		}
	}
	for(int i=0;i<v_container.size();i++){
		
		if(v_container[i]->name.compare(temp)==0){
			for(int k=0;k<v_room.size();k++){
				for(int j=0;j<v_room[k]->container.size();j++){
					if(v_room[k]->container[j].compare(temp)==0){
						v_room[k]->container.erase(v_room[k]->container.begin()+j);
					}
				}
			}
		}
	}
	for(int i;i<v_room.size();i++){
		
		if(room->name==v_room[i]->name){
			room=v_room[i];
		}
	}
}

void update_helper(const string input){
	string temp=input;
	int size=0;
	string old_status;
	string new_status;
	if(temp.find("Update")==-1){
		return;
	}
	else{
		temp=temp.erase(0,7);
		size=temp.find("to ");
		old_status=temp.substr(0,size-1);
		new_status=temp.substr(size+3);
	}
	for(int i=0;i<v_item.size();i++){
		if(old_status.compare(v_item[i]->name)==0){
			v_item[i]->status=new_status;
		}
	}
	for(int i=0;i<v_room.size();i++){
		if(old_status.compare(v_room[i]->name)==0){
			v_room[i]->status=new_status;
		}
	}
	for(int i;i<v_container.size();i++){
		if(old_status.compare(v_container[i]->name)==0){
			v_container[i]->status=new_status;
		}
	}
	for(int i;i<v_creature.size();i++){
		if(old_status.compare(v_creature[i]->name)==0){
			v_creature[i]->status=new_status;
		}
	}
	for(int i;i<v_room.size();i++){
		if(room->name==v_room[i]->name){
			room=v_room[i];
		}
	}
}

bool Check_Trigger(){
	bool check=false;
	for(int i=0;i<room->trigger.size();i++){
		if(room->trigger[i]->command.size()==0||room->trigger[i]->has_command==false){
			if(room->trigger[i]->type == "permanent" || (room->trigger[i]->type == "single" && room->trigger[i]->times == 0)){
                    if(room->trigger[i]->condition.size() == 2){ 
						check=Check_Trigger_helper(room->trigger[i]->condition[0],room->trigger[i]->condition[1]);
					}
                    else if(room->trigger[i]->condition.size() == 3){
						check=Check_Trigger_helper(room->trigger[i]->condition[0],room->trigger[i]->condition[1],room->trigger[i]->condition[2]);
					}
                    if(check == true){
						
						room->trigger[i]->times++;
						
						for(int m=0;room->trigger[i]->print.size();m++){
							cout<<room->trigger[i]->print<<endl;
						}
						for(int j=0;j<room->trigger[i]->action.size();j++){
							add_helper(room->trigger[i]->action[j]);
							delete_helper(room->trigger[i]->action[j]);
							update_helper(room->trigger[i]->action[j]);
							if(room->trigger[i]->action[j].find("Game Over")!=-1){
							 	cout<<"You win"<<endl;
							 	finish=true;
							}
							Check_Input2(room->trigger[i]->action[j]);
						}
					}
                }
		}
	}
	bool check1=false;
	for(int i=0;i<room->item.size();i++){
		for(int j=0;j<v_item.size();j++){
			if(room->item[i]==v_item[j]->name){
				for(int k=0;k<v_item[j]->trigger.size();k++){
					if(v_item[j]->trigger[k]->command.size()==0||v_item[j]->trigger[k]->has_command==false){
						if(v_item[j]->trigger[k]->type == "permanent" || (v_item[j]->trigger[k]->type == "single" && v_item[j]->trigger[k]->times == 0)){
                    		if(v_item[j]->trigger[k]->condition.size() == 2){ 
								check1=Check_Trigger_helper(v_item[j]->trigger[k]->condition[0],v_item[j]->trigger[k]->condition[1]);
							}
                    		if(v_item[j]->trigger[k]->condition.size() == 3){
								check1=Check_Trigger_helper(v_item[j]->trigger[k]->condition[0],v_item[j]->trigger[k]->condition[1],v_item[j]->trigger[k]->condition[2]);
							}
                    		if(check1 == true){
								
								v_item[j]->trigger[k]->times++;
								if(v_item[j]->trigger[k]->print.size()!=0){
									cout<<v_item[j]->trigger[k]->print<<endl;
								}
								for(int l=0;l<v_item[j]->trigger[k]->action.size();l++){
									add_helper(v_item[j]->trigger[k]->action[l]);
									delete_helper(v_item[j]->trigger[k]->action[l]);
									update_helper(v_item[j]->trigger[k]->action[l]);
									if(v_item[j]->trigger[k]->action[l].find("Game Over")!=-1){
										cout<<"You win"<<endl;
									 	finish=true;
									}
									Check_Input2(v_item[j]->trigger[k]->action[l]);
								}
							}
                		}
					}
				}
			}
		}
	}
	bool check2=false;
	for(int i=0;i<room->creature.size();i++){
		for(int j=0;j<v_creature.size();j++){
			if(room->creature[i]==v_creature[j]->name){
				for(int k=0;k<v_creature[j]->trigger.size();k++){	
					if(v_creature[j]->trigger[k]->command.size()==0||v_creature[j]->trigger[k]->has_command==false){
						if(v_creature[j]->trigger[k]->type == "permanent" || (v_creature[j]->trigger[k]->type == "single" && v_creature[j]->trigger[k]->times == 0)){
							
							if(v_creature[j]->trigger[k]->condition.size() == 2){ 
							
								
								check2=Check_Trigger_helper(v_creature[j]->trigger[k]->condition[0],v_creature[j]->trigger[k]->condition[1]);
							}
                    		if(v_creature[j]->trigger[k]->condition.size() == 3){
								check2=Check_Trigger_helper(v_creature[j]->trigger[k]->condition[0],v_creature[j]->trigger[k]->condition[1],v_creature[j]->trigger[k]->condition[2]);
							}
                    		if(check2 == true){
								v_creature[j]->trigger[k]->times++;
								if(v_creature[j]->trigger[k]->print.size()!=0){
									cout<<v_creature[j]->trigger[k]->print<<endl;
								}
								for(int l=0;l<v_creature[j]->trigger[k]->action.size();l++){
									add_helper(v_creature[j]->trigger[k]->action[l]);
									delete_helper(v_creature[j]->trigger[k]->action[l]);
									update_helper(v_creature[j]->trigger[k]->action[l]);
									if(v_creature[j]->trigger[k]->action[l].find("Game Over")!=-1){
									 	cout<<"Victory!"<<endl;
									 	finish=true;
									 	return true;
									}
									Check_Input2(v_creature[j]->trigger[k]->action[l]);
								}
							}
                		}
					}
				}
			}
		}
	}
	bool check3=false;
	for(int i=0;i<room->container.size();i++){
		for(int j=0;j<v_container.size();j++){
			if(room->container[i]==v_container[j]->name){
				for(int k=0;k<v_container[j]->trigger.size();k++){
					if(v_container[j]->trigger[k]->command.size()==0||v_container[j]->trigger[k]->has_command==false){
						if(v_container[j]->trigger[k]->type == "permanent" || (v_container[j]->trigger[k]->type == "single" && v_container[j]->trigger[k]->times == 0)){
                    		if(v_container[j]->trigger[k]->condition.size()== 2){ 
								check3=Check_Trigger_helper(v_container[j]->trigger[k]->condition[0],v_container[j]->trigger[k]->condition[1]);
							}
                    		if(v_container[j]->trigger[k]->condition.size() == 3){
								check3=Check_Trigger_helper(v_container[j]->trigger[k]->condition[0],v_container[j]->trigger[k]->condition[1],v_container[j]->trigger[k]->condition[2]);
							}
							
                    		if(check3 == true){
								
								v_container[j]->trigger[k]->times++;
								if(v_container[j]->trigger[k]->print.size()!=0){
									cout<<v_container[j]->trigger[k]->print<<endl;
								}
								for(int l=0;l<v_container[j]->trigger[k]->action.size();l++){
									add_helper(v_container[j]->trigger[k]->action[l]);
									delete_helper(v_container[j]->trigger[k]->action[l]);
									update_helper(v_container[j]->trigger[k]->action[l]);
									if(v_container[j]->trigger[k]->action[l].find("Game Over")!=-1){
										cout<<"You win"<<endl;
									 	finish=true;
									}
									 Check_Input2(v_container[j]->trigger[k]->action[l]);
								}
							}
                		}
					}
				}
			}
		}
	}

	return check|check1|check2|check3;
}

bool Check_Trigger(string input){
	bool check=false;
	for(int i=0;i<room->trigger.size();i++){
		if(room->trigger[i]->command.compare(input)==0){
			if(room->trigger[i]->type == "permanent" || (room->trigger[i]->type == "single" && room->trigger[i]->times == 0)){
                    if(room->trigger[i]->condition.size()== 2){ 
						check=Check_Trigger_helper(room->trigger[i]->condition[0],room->trigger[i]->condition[1]);
					}
                    else if(room->trigger[i]->condition.size() == 3){
						check=Check_Trigger_helper(room->trigger[i]->condition[0],room->trigger[i]->condition[1],room->trigger[i]->condition[2]);
					}
                    if(check == true){
						room->trigger[i]->times++;
						if(room->trigger[i]->print.size()!=0){
									cout<<room->trigger[i]->print<<endl;
								}
								for(int j=0;j<room->trigger[i]->action.size();j++){
									add_helper(room->trigger[i]->action[j]);
								 	delete_helper(room->trigger[i]->action[j]);
									update_helper(room->trigger[i]->action[j]);
									if(room->trigger[i]->action[j].find("Game Over")!=-1){
										cout<<"You win"<<endl;
									 	finish=true;
									}
								 	Check_Input2(room->trigger[i]->action[j]);
								}
					}
                }
		}
	}
	bool check1=false;
	for(int i=0;i<room->item.size();i++){
		for(int j=0;j<v_item.size();j++){
			if(room->item[i]==v_item[j]->name){
				for(int k=0;k<v_item[j]->trigger.size();k++){
					if(v_item[j]->trigger[k]->command.compare(input)==0){
						if(v_item[j]->trigger[k]->type == "permanent" || (v_item[j]->trigger[k]->type == "single" && v_item[j]->trigger[k]->times == 0)){
                    		if(v_item[j]->trigger[k]->condition.size() == 2){ 
								check1=Check_Trigger_helper(v_item[j]->trigger[k]->condition[0],v_item[j]->trigger[k]->condition[1]);
							}
                    		if(v_item[j]->trigger[k]->condition.size() == 3){
								check1=Check_Trigger_helper(v_item[j]->trigger[k]->condition[0],v_item[j]->trigger[k]->condition[1],v_item[j]->trigger[k]->condition[2]);
							}
                    		if(check1 == true){
								v_item[j]->trigger[k]->times++;
								if(v_item[j]->trigger[k]->print.size()!=0){
									cout<<v_item[j]->trigger[k]->print<<endl;
								}
								for(int l=0;l<v_item[j]->trigger[k]->action.size();l++){
									add_helper(v_item[j]->trigger[k]->action[l]);
									delete_helper(v_item[j]->trigger[k]->action[l]);
									update_helper(v_item[j]->trigger[k]->action[l]);
									if(v_item[j]->trigger[k]->action[l].find("Game Over")!=-1){
										cout<<"You win"<<endl;
									 	finish=true;
									}
									Check_Input2(v_item[j]->trigger[k]->action[l]);
								}
							}
                		}
					}
				}
			}
		}
	}
	bool check2=false;
	
	for(int i=0;i<room->creature.size();i++){
		for(int j=0;j<v_creature.size();j++){
			if(room->creature[i]==v_creature[j]->name){
				for(int k=0;k<v_creature[j]->trigger.size();k++){
					if(v_creature[j]->trigger[k]->command.compare(input)==0){
						if(v_creature[j]->trigger[k]->type == "permanent" || (v_creature[j]->trigger[k]->type == "single" && v_creature[j]->trigger[k]->times == 0)){
                    		
							if(v_creature[j]->trigger[k]->condition.size() == 2){ 
								check2=Check_Trigger_helper(v_creature[j]->trigger[k]->condition[0],v_creature[j]->trigger[k]->condition[1]);
							}
                    		if(v_creature[j]->trigger[k]->condition.size() == 3){
								check2=Check_Trigger_helper(v_creature[j]->trigger[k]->condition[0],v_creature[j]->trigger[k]->condition[1],v_creature[j]->trigger[k]->condition[2]);
							}
                    		if(check2 == true){
								v_creature[j]->trigger[k]->times++;
								if(v_creature[j]->trigger[k]->print.size()!=0){
									cout<<v_creature[j]->trigger[k]->print<<endl;
								}
								for(int l=0;l<v_creature[j]->trigger[k]->action.size();l++){
										add_helper(v_creature[j]->trigger[k]->action[l]);
									 delete_helper(v_creature[j]->trigger[k]->action[l]);
									 update_helper(v_creature[j]->trigger[k]->action[l]);
									 if(v_creature[j]->trigger[k]->action[l].find("Game Over")!=-1){
									 	cout<<"Victory"<<endl;
									 	finish=true;
									 }
									 Check_Input2(v_creature[j]->trigger[k]->action[l]);
								}
							}
                		}
					}
				}
			}
		}
	}
	bool check3=false;
	for(int i=0;i<room->container.size();i++){
		for(int j=0;j<v_container.size();j++){
			if(room->container[i]==v_container[j]->name){
				for(int k=0;k<v_container[j]->trigger.size();k++){
					if(v_container[j]->trigger[k]->command.compare(input)==0){
						if(v_container[j]->trigger[k]->type == "permanent" || (v_container[j]->trigger[k]->type == "single" && v_container[j]->trigger[k]->times == 0)){
                    		if(v_container[j]->trigger[k]->condition.size()== 2){ 
								check3=Check_Trigger_helper(v_container[j]->trigger[k]->condition[0],v_container[j]->trigger[k]->condition[1]);
							}
                    		if(v_container[j]->trigger[k]->condition.size() == 3){
								check3=Check_Trigger_helper(v_container[j]->trigger[k]->condition[0],v_container[j]->trigger[k]->condition[1],v_container[j]->trigger[k]->condition[2]);
							}
                    		if(check3 == true){
								v_container[j]->trigger[k]->times++;
								if(v_container[j]->trigger[k]->print.size()!=0){
									cout<<v_container[j]->trigger[k]->print<<endl;
								}
								for(int l=0;l<v_container[j]->trigger[k]->action.size();l++){
									add_helper(v_container[j]->trigger[k]->action[l]);
									delete_helper(v_container[j]->trigger[k]->action[l]);
									update_helper(v_container[j]->trigger[k]->action[l]);
									if(v_container[j]->trigger[k]->action[l].find("Game Over")!=-1){
										cout<<"You win"<<endl;
									 	finish=true;
									}
									Check_Input2(v_container[j]->trigger[k]->action[l]);
								}
							}
                		}
					}
				}
			}
		}
	}

	return check|check1|check2|check3;
}

bool Check_Trigger_helper(string object,string status){
	
	for(int i=0;i<v_inventory.size();i++){
		if(object.compare(v_inventory[i])==0){
			for(int j=0;j<v_item.size();j++){
				if(v_inventory[i].compare(v_item[j]->name)==0){
					if(v_item[j]->status.compare(status)==0){
						return true;
					}
				}
			}
		}
	}
	
	for(int i=0;i<room->container.size();i++){
		if(object.compare(room->container[i])==0){
			for(int j=0;j<v_container.size();j++){
				if(v_container[j]->name.compare(room->container[i])==0){
					if(v_container[j]->status.compare(status)==0){
						
						return true;
					}
				}
			}
		}
	}
	
	
	for(int i=0;i<room->item.size();i++){
		if(object.compare(room->item[i])==0){
			for(int j=0;j<v_item.size();j++){
				if(v_item[j]->name.compare(room->item[i])==0){
					if(v_item[j]->status.compare(status)==0){
						
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

bool Check_Trigger_helper(string has,string object,string owner){

	bool container=false;
	bool inventory=false;
	if(owner.compare("inventory")==0){
		for(int i=0;i<v_inventory.size();i++){
			if(object==v_inventory[i]){
				inventory=true;
				if(has.compare("yes")==0){
					return true;
				}
			}
		}
		if(has.compare("no")==0&&inventory==false){
			
			return true;
		}
		return false;
	}
	
	for(int i=0;i<room->container.size();i++){
		if(room->container[i]==owner){
			for(int j=0;j<v_container.size();j++){
				if(room->container[i]==v_container[j]->name){
					for(int k=0;k<v_container[j]->item.size();k++){
						if(v_container[j]->item[k]==object){
							container=true;
							if(has.compare("yes")==0){
								return true;
							}
						}
					}
				}
			}
		}
		if(has.compare("no")==0&&container==false){
	
				return true;
			}
	}
	
	return false;
}