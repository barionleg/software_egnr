#include "Entities.h"
#include "settings.h"
#include "cmd.h"
using std::ifstream;

//这些理论上来说封装一下的好
//但是按c风格就无所谓,反正最后要打包成库
vector<Player> player_list;
vector<Task> task_list;
//可以的话我也不想存那么多映射关系
map<string,string> event;
map<string,vector<Score*>> player_score;
map<string,string> task_player;
void read_events(){
    ifstream ifs;
    ifs.open(EVENT_JSON_PATH,std::ios_base::in);
    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(ifs,root)){
        std::cerr<<   "##add_event parse json error\n";
    }                        
    root=(root["Sports"])[0]["DisciplineList"];//是个数组
    // 遍历整个keys,只取出正赛的id和姓名关系
    for(int i=0;i<root.size();i++){
        auto e=root[i];
        event.insert(std::pair((root[i])["DisciplineName"].asString(),
        root[i]["Id"].asString()));
    }
    
    ifs.close();
}
void read_players(){
    ifstream ifs;
    ifs.open(ATHELETS_JSON_PATH,std::ios_base::in);
    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(ifs,root)){
        std::cerr<<   "###add_player parse json error\n";
    }                        
    for (int i = 0; i < root.size(); i++)//循环的是国家
    {
        auto participants=root[i]["Participations"];
        
        for (int j = 0; j < participants.size(); j++)
        {
            auto participant=participants[j];
            player_list.push_back(Player(participant));
        }
    }
    ifs.close ();
}
void read_tasks(){
   
    for (auto it=event.begin(); it != event.end(); it++)
    { 
        ifstream ifs;
        //通过event映射找出文件名和比赛的对应关系
        string fileId=it->second;
        string json_addr=RESULTS_JSON_DIR+fileId+".json";
        ifs.open(json_addr,std::ios_base::in);
        Json::Reader reader;
        Json::Value root;
        if (!reader.parse(ifs,root)){
            std::cerr<<"###"<<json_addr<<" no such file\n";
        }
        task_list.push_back(Task(root));
        ifs.close();
    }
    //for test
    // task_list[1].print();  
}


void read_jsons(){
    read_events();
    read_players();
    read_tasks();
    organize_maps();
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
    this->gender=participant["Gender"].asString();
}

Task::Task(Json::Value& task_root){
    this->name=task_root["DisciplineName"].asString();
    this->heats.resize(3);
    //接下来添加各个赛程
    auto heats_json=task_root["Heats"];
    for (int i = 0; i < heats_json.size(); i++)
    {
        string heat_name=heats_json[i]["Name"].asString();
        Heat heat=Heat(heats_json[i],this);//一个heat
        //添加到task中
        if (heat_name=="Final")
        {
            this->heats[FINAL]=heat;
        }
        else if(heat_name=="Semifinal"){
            this->heats[SEMIFINAL]=heat;
        }
        else if(heat_name=="Preliminary"){
            this->heats[PRELIMINARY]=heat;
        }
        else
            std::cerr<<"###heat name unkonwn\n";
    }
}

void Task::print(){
    std::cout<<this->name<<"\n";
    for (auto heat : this->heats)
    {
        heat.print();
    }
    printf("----------------------\n");
}

Heat::Heat(string name,Task* parent){
    this->name=name;
    this->parent=parent;
}

Heat::Heat(){
    this->name="null";
}

Heat::Heat(Json::Value& heat_json,Task* parent){
    this->name=heat_json["Name"].asString();
    auto result_json=heat_json["Results"];
    for (int i = 0; i < result_json.size(); i++)
    {
        this->record.push_back(Score(result_json[i],this));
    }
}

void Heat::print(){
    std::cout<<'@'<<this->name<<'\n';
    for (auto score : this->record)
    {
        score.print();
    }
}

void inser_player_scores(string participant_name,Score* score){
    vector<Score*> player_scores;
    player_scores.push_back(score);
    player_score.insert_or_assign(participant_name,player_scores);
}

void insert_task_player(string player,string task){
    task_player.insert_or_assign(task,player);
}

Score::Score(Json::Value& score_json,Heat* parent){
    this->total=std::stod(score_json["TotalPoints"].asString());
    this->parent=parent;
    auto dives_json=score_json["Dives"];
    for (int i = 0; i < dives_json.size(); i++)
    {
        auto points=dives_json[i]["DivePoints"].asString();
        this->score_per_dive.push_back(std::stod(points));
    }
    this->rank=score_json["Rank"].asInt();
    this->competitor_name=score_json["FullName"].asString();
    this->rank=score_json["Rank"].asInt();
    //插入全局变量
    inser_player_scores(this->competitor_name,this);
    insert_task_player(this->competitor_name,this->parent->parent->name);
}

void Score::print(){
    std::cout<<this->competitor_name<<'\n';
    std::cout<<"Rank:"<<this->rank<<'\n';
    for (auto score : this->score_per_dive)
    {
        std::cout<<score<<' ';
    }
    std::cout<<'\n';
    std::cout<<"Total Score:"<<this->total<<'\n';    
}

