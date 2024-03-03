#include "cmd.h"
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
        if (cmd.compare("players")==0){
            cmd_players(ofs);
        }
        else if (cmd.find("result")==0){
            cmd.erase(cmd.begin(),cmd.begin()+6);//删命令中的“result”这个子串
            string task_name=trim(cmd);
            cmd_result(ofs,task_name);
        }
        else{
            cmd_error(ofs);
        }
    }
    return 0;
}
