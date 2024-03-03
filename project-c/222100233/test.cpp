// #include "Entities.h"
#include "cmd.h"
int main(int argc, char const *argv[])
{
    ofstream ofs("./out.txt");
    read_jsons();
    cmd_result(ofs,"Women 1m Springboard");
    return 0;
}
