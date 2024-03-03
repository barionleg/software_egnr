// #pragma once 
#include "Entities.h"
#include <algorithm>
using std::ofstream;
using std::ifstream;

void cmd_players(ofstream& ofs);

void cmd_result(ofstream& ofs, const string& taks_name);

string cmd_result_detail(ofstream& ofs, const string& task_name);

void organize_maps();//整理已存储的映射关系

std::string trim(const string & str);//去除字符串中的空格

void cmd_error(ofstream& ofs);

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

