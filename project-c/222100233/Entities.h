#pragma once
#include <json/json.h>
#include <json/reader.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;
using std::pair;
class Player;
class Heat;
class Task;

#if !defined(FINALS)
#define FINALS 3
#endif // FINALS
#if !defined(SEMIFINALS)
#define SEMIFINALS 2
#endif // SEMIFINALS
#if !defined(PRELIMINARIES)
#define PRELIMINARIES 1
#endif // PRELIMINARIES


//event记录映射关 2需要一个添加键值对的函数
void add_event(map<string,string>& event,Json::Value& value);//添加映射关系
void read_jsons();//读取json文件到内存

class Player
{
private:
    string firstName;
    string lastName;
    string country;

public:
    Player(string firstName, string lastName, string country);
    Player(Json::Value& participation);
    string get_info();
    
};

struct Score
{
    string competitor_name;
    int rank;
    vector<double> score_per_dive;
    double total;
    string get_info();
    Score(Json::Value& score_json);
};

class Task
{
private:
    string name;
    vector<Heat> heats;

public:
    Task(Heat *heat, string name);
    Task(Json::Value& task_root);
    string get_info();
};

class Heat
{
private:
    vector<Score> record;
    string name;
public:
    string get_info();
    Heat(Json::Value& heat_json);
    Heat();
};
