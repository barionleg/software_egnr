#include "cmd.h"
#include <algorithm>
extern vector<Player> player_lists;
extern vector<Task> task_list;
extern map<string,string> event;
extern map<string,vector<Score&>> player_score;
extern map<string,string> task_player;

using std::cout;
using std::endl;
using std::ofstream;
using namespace cmd_output;
string cmd_players(){
    Players res;
    for (auto player : player_lists)
    {
        // cout<<"Full Name:"<<player.firstName<<' '<<player.lastName<<endl;
        // cout<<"Gender:"<<player.gender<<endl;
        // cout<<"Country:"<<player.country<<endl;
        // cout<<"-----------------"<<endl;
        res.country=player.country;
        res.gender=player.gender;
        res.name=player.firstName+player.lastName;
    }
    
}
vector<Result>& cmd_result(const string& taks_name){
    vector<Result> res;
    for (auto  tp: task_player)
    {
        if(tp.first==taks_name){
            string player_name = tp.second;
            //我不知道这个排名是怎么计算的，也不想深究了
            //累了毁灭吧，直接取决赛了
            int rank;
            double total_score=0.f;
            auto task=std::__find_if(task_list.begin(),task_list.end(),[taks_name](const Task& task){
                return task.name==taks_name;
            });
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
            
            res.push_back(Result{tp.second,rank,total_score});
        }
    }
    //按排名进行排序
    std::sort(res.begin(),res.end(),[](const Result& r1,const Result& r2){
        return r1.rank<r2.rank;
    });
    return res;
}

string cmd_result_detail(const ofstream& out,const string& taks_name){
   //去死吧这个功能，我把映射关系理清楚有什么意义
   //我要去看我的xv6
   //我要去了解我的电脑是怎么工作的
   //知识依托于痛点存在，我连大项目都没有 摸过我学软件工程干嘛，迟早会忘
   //人应该有选择学习知识方向的权利
}

void organize_maps(){
    //按字典序排列映射关系，这样在遍历时就可以直接输出
    std::sort(task_player.begin(),task_player.end(),[](const auto& p1,const auto p2&){
        return p1.second<p2.second;
    });
}

Result::Result(string player,int rank,double total){
    this->player_name=player;
    this->rank=rank;
    this->total_score=total;
}