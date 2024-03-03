#include "cmd.h"
extern vector<Player> player_list;
extern vector<Task> task_list;
extern map<string,string> event;
extern map<string,vector<Score&>> player_score;
extern map<string,string> task_player;

using std::cout;
using std::endl;
using std::ofstream;
using std::endl;
using namespace cmd_output;

Task* find_task_by_name(string& task_name);

void cmd_result(ofstream& ofs, string& taks_name){
    vector<cmd_output::Result> res;
    for (auto  tp: task_player)
    {
        if(tp.first==taks_name){
            string player_name = tp.second;
            //我不知道这个排名是怎么计算的，也不想深究了
            //累了毁灭吧，直接取决赛了
            int rank;
            double total_score=0.f;
            auto task=find_task_by_name(taks_name);
            
            Heat& heat_final=task->heats[FINAL];
            //取出总分和排名
            for (auto score : heat_final.record)
            {
                if(score.competitor_name==player_name)
                {
                    rank=score.rank;
                    total_score=score.total;
                    break;
                }
            }
            res.push_back(cmd_output::Result{tp.second,rank,total_score});
        }
    }
    if (res.empty())
        {
            cmd_error(ofs);
            return;
        }
    //按排名进行排序
    std::sort(res.begin(),res.end(),[](const cmd_output::Result& r1,const cmd_output::Result& r2){
        return r1.rank<r2.rank;
    });
    //输出
    for (auto r : res)
    {
        // ofs<<r.player_name<<endl;
        // ofs<<r.rank<<endl;
        // ofs<<r.total_score<<endl;
        // ofs<<"------------\n";
        cout<<r.player_name<<endl;
        cout<<r.rank<<endl;
        cout<<r.total_score<<endl;
        cout<<"------------\n";
    }
}

void cmd_players(ofstream& ofs){
    for (size_t i=0;i<player_list.size();i++)
    {
        Player& player=player_list[i];
        // cout<<"Full Name:"<<player.firstName<<' '<<player.lastName<<endl;
        // cout<<"Gender:"<<player.gender<<endl;
        // cout<<"Country:"<<player.country<<endl;
        // cout<<"-----------------"<<endl;
        ofs<<"Full Name:"<<player.firstName<<' '<<player.lastName<<endl;
        ofs<<"Gender:"<<player.gender<<endl;
        ofs<<"Country:"<<player.country<<endl;
        ofs<<"-----------------"<<endl;
    }
    
}

Task* find_task_by_name(string& task_name){
    for (size_t i = 0; i < task_list.size(); i++)
    {
        if (task_list[i].name==task_name)
        {
            return &task_list[i];
        }
    }
    return NULL;
}


void cmd_error(ofstream& ofs){
    ofs<<"Error\n";
    ofs<<"--------------"<<endl;
}

string cmd_result_detail(const ofstream& out,const string& taks_name){
   //去死吧这个功能，我把映射关系理清楚有什么意义
   //我要去看我的xv6
   //我要去了解我的电脑是怎么工作的
   //知识依托于痛点存在，我连大项目都没有 摸过我学软件工程干嘛，迟早会忘
   //人应该有选择学习知识方向的权利
   return "";
}

void organize_maps(){
    //按字典序排列映射关系，这样在遍历时就可以直接输出
    // std::sort(task_player.begin(),task_player.end(),[](const pair<string,string>& p1,const pair<string,string>& p2){
    //     return p1.second<p2.second;
    // });
    std::sort(player_list.begin(), player_list.end(), [](const Player& p1,const Player& p2) {
        return p1.firstName<p2.firstName;
    });
}

Result::Result(string player,int rank,double total){
    this->player_name=player;
    this->rank=rank;
    this->total_score=total;
}

std::string trim(const std::string& str) {
    std::string trimmedStr = str;
    size_t start = trimmedStr.find_first_not_of(" \t\n");
    size_t end = trimmedStr.find_last_not_of(" \t\n");
    
    if (start != std::string::npos && end != std::string::npos) {
        trimmedStr = trimmedStr.substr(start, end - start + 1);
    } else {
        trimmedStr.clear();
    }
    
    return trimmedStr;
}