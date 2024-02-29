#include "cmd.h"
extern vector<Player> player_lists;
extern vector<Task> task_list;
extern map<string,string> event;
using std::cout;
using std::endl;
using std::ofstream;
string cmd_players(const ofstream& out){
    for (auto player : player_lists)
    {
        cout<<"Full Name:"<<player.firstName<<' '<<player.lastName<<endl;
        cout<<"Gender:"<<player.gender<<endl;
        cout<<"Country:"<<player.country<<endl;
        cout<<"-----------------"<<endl;
    }
    
}
string cmd_task();
string cmd_task_detail();