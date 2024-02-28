#include <iostream>
#include <fstream>
#include <json/json.h>
#include <json/reader.h>
#include "Service.h"
#include "Entities.h"
using namespace std;
//处理获取的参数，存入main函数变量中
void getargs(string& in,string& out,vector<string>& cmds){

};

int main(int argc, char const *argv[])
{
    string in,out;//输入输出的文件名
    vector<string> cmds;//指令序列

    getargs(in,out,cmds);//读入上面变量
    read_jsons();//从json读入数据
    for (size_t i = 0; i < cmds.size(); i++)
    {
        string cmd=cmds[i];
        string res="";
        if (cmd.compare("players")){
            res=cmd_players();
        }
        else if (cmd.find("result")==0){
            res=cmd_result();
        }
        else{
            res="Error\n";
        }
    }
    return 0;
}

void init_objs(){
    string addr="./datas/atheletes.json";
    // string addr="./datas/test.json";
    ifstream ifs;
    ifs.open(addr,ios_base::in);
    Json::Reader reader;
    Json::Value value;
    if (reader.parse(ifs,value))
    {
        cout<<"success"<<endl;
    }
    auto str=value.toStyledString();
    cout << str;
}