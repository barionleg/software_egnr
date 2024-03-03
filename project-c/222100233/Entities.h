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


#if !defined(FINAL)
#define FINAL 2
#endif // FINALS
#if !defined(SEMIFINAL)
#define SEMIFINAL 1
#endif // SEMIFINALS
#if !defined(PRELIMINARIE)
#define PRELIMINARY 0
#endif // PRELIMINARIES


//event记录映射关 2需要一个添加键值对的函数
void read_jsons();//读取json文件到内存

class Player
{
public:
    string firstName;
    string lastName;
    string country;
    string gender;
    Player(string firstName, string lastName, string country);
    Player(Json::Value& participation);
    string get_info();
    
};

struct Score
{
    string competitor_name;
    Heat* parent;
    int rank;
    vector<double> score_per_dive;
    double total;
    string get_info();
    void print();
    Score(Json::Value& score_json,Heat* parent);
};

class Task
{
public:
    string name;
    vector<Heat> heats;
    Task(Heat *heat, string name);
    Task(Json::Value& task_root);
    void print();
};

class Heat
{
public:
    vector<Score> record;
    string name;
    Task* parent;
public:
    void print();
    Heat(Json::Value& heat_json,Task* parent);
    Heat(string name,Task* parent);
    Heat();
};
