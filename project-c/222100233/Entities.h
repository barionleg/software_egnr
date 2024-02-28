#pragma once
#include <json/json.h>
#include <iostream>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;
using std::pair;
class Player;
class Phase;
class Task;
//event记录映射关系,需要一个添加键值对的函数
void add_event(map<string,string>& event,Json::Value& value);//添加映射关系
void read_jsons();//读取json文件到内存

enum Phases
{
    Pre,
    Semi,
    Final
};

class Player
{
private:
    string firstName;
    string lastName;
    string country;

public:
    Player(string firstName, string lastName, string country);
    Player(Json::Value participation);
    string get_info();
    
};

struct Score
{
    string competitor_name;
    int rank;
    double score_per_judge[7];
    string get_info();
};

class Task
{
private:
    string name;
    Phase phases[3];

public:
    Task(Phase *phase, string name);
    Task(Json::Value result);
    string get_info();
};

class Phase
{
private:
    vector<Score> record;

public:
    string get_info();
    Phase(Json::Value heat);
};
