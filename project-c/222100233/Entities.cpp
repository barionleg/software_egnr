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
    root=(root["Sports"])[0]["DisciplineList"];//是个数组
    // 遍历整个keys,只取出正赛的id和姓名关系
    for(int i=0;i<root.size();i++){
        auto e=root[i];
        event.insert(std::pair((root[i])["DisciplineName"].asString(),
        root[i]["Id"].asString()));
    }
    for (auto i : event)
    {
        std::cout<<i.first<<' '<<i.second<<'\n';
    }
    // std::cout<<root.toStyledString();
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