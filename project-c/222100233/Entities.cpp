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
    //我不知道为什么有一个test,删掉好了
    
    ifs.close();
}
void read_players(){
    ifstream ifs;
    ifs.open(ATHELETS_JSON_PATH,std::ios_base::in);
    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(ifs,root)){
        throw "add_player parse json error\n";
    }                        
    for (int i = 0; i < root.size(); i++)//循环的是国家
    {
        auto participants=root[i]["Participations"];
        for (int j = 0; j < participants.size(); i++)
        {
            auto participant=participants[j];
            player_list.push_back(Player(participant));
        }
        
    }
    ifs.close ();
}
void read_tasks(){
    ifstream ifs;
    for (auto it=event.begin(); it != event.end(); it++)
    {
        //通过event映射找出文件名和比赛的对应关系
        string fileId=it->second;
        ifs.open(RESULTS_JSON_DIR+fileId,std::ios_base::in);
        Json::Reader reader;
        Json::Value root;
        if (!reader.parse(ifs,root)){
            std::cerr<<it->first<<" no such file\n";
        }
        task_list.push_back(Task(root));
    }
    
    
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
Player::Player(Json::Value& participant){
    this->country=participant["NAT"].asString();
    this->firstName=participant["PreferredFirstName"].asString();   
    this->lastName=participant["PreferredLastName"].asString();
}

Task::Task(Json::Value& task_root){
    this->name=task_root["DisciplineName"].asString();
    this->heats.resize(3);
    //接下来添加各个赛程
    auto heats_json=task_root["Heats"];
    for (int i = 0; i < heats_json.size(); i++)
    {
        string heat_name=heats_json[i]["Name"].asString();
        Heat heat=Heat(heats_json[i]);//一个heat
        //添加到task中
        if (heat_name=="Finals")
        {
            this->heats[FINALS]=heat;
        }
        else if(heat_name=="Semifinals"){
            this->heats[SEMIFINALS]=heat;
        }
        else if(heat_name=="Preliminaries"){
            this->heats[PRELIMINARIES]=heat;
        }
        else
            throw "heat name unkonwn";
    }
    
}

Heat::Heat(Json::Value& heat_json){
    this->name=heat_json["Name"].asString();
    auto result_json=heat_json["Results"];
    for (int i = 0; i < result_json.size(); i++)
    {
        this->record.push_back(Score(result_json[i]));
    }
}

Score::Score(Json::Value& score_json){
    this->total=score_json["TotalPoints"].asDouble();
    auto dives_json=score_json["Dives"];
    //
    for (int i = 0; i < dives_json.size(); i++)
    {
        auto points=dives_json[i]["DivePoints"].asDouble();
        this->score_per_dive.push_back(points);
    }
    this->rank=score_json["Rank"].asInt();
    this->competitor_name=score_json["FullName"].asString();
    this->rank=score_json["Rank"].asInt();
}