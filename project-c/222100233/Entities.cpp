#include "Entities.h"
#include "settings.h"
using std::ifstream;

vector<Player> player_list;
vector<Task> task_list;
map<string,string> event;


void add_event(map<string,string>& event,Json::Value& value){
    
}
void read_events(){
    ifstream ifs;
    ifs.open(EVENT_JSON_PATH,std::ios_base::in);
    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(ifs,root)){
        throw "add_event parse json error\n";
    }
    auto test=root.toStyledString();
    std::cout<<test<<std::endl;
    ifs.close();
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