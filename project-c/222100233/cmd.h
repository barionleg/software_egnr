#pragma once 
#include "Entities.h"
string cmd_players(const ofstream ofs);
string cmd_result(const ofstream ofs, const string& taks_name);
string cmd_result_detail(const ofstream ofs, const string& task_name);
void organize_maps();//整理已存储的映射关系

namespace cmd_output{

struct Result
{
    string player_name;
    int rank;
    double total_score;
    Result(string, int ,double);
};

struct Result_detail
{
    string player_name;
    int rank;
    double total_score;
    //不写了，去死吧
};

struct Players
{
    string gender;
    string country;
    string name;
};

}

