#include <iostream>
#include <json/json.h>
#include <json/reader.h>
#include "cmd.h"
#include "Entities.h"
using namespace std;

int main(int argc, char const *argv[])
{
    if (argc!=3)
    {
        // std::cerr<<"unexpexted form"<<endl;
        throw "unexpexted form\n";
    }
    
    string in=argv[1],out=argv[2];//输入输出的文件名
    ifstream ifs(in);
    ofstream ofs(out);
    vector<string> cmds;//指令序列
    if (!ifs.is_open())
        throw("unable to find input file\n");
    
    read_jsons();//从json读入数据
    string cmd;
    while (getline(ifs,cmd))
    {
        string res="";
        if (cmd.compare("players")){
            res=cmd_players(ofs);
        }
        else if (cmd.find("result")==0){
            res=cmd_task();
        }
        else{
            res="Error\n";
        }
    }
    return 0;
}
