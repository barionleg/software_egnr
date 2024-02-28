#include "Entities.h"
vector<Player> player_list;
vector<Task> task_list;
map<string,string> event;

void add_event(map<string,string>& event,Json::Value& value){

}
void read_events(){
    
}
void read_players(){
    
}
void read_tasks(){

}
void read_jsons(){
    read_events();
    read_players();
    read_tasks();
}


Player::Player(string firstName, string lastName, string country)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->country = country;
}