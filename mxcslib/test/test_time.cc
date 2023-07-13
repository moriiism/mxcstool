#include "mxcs_base.h"
#include "mxcs_time.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

    double time1 = MxcsTime::GetTimeSec();
    printf("time1 = %e\n", time1);

    double time2 = MxcsTime::GetTimeSec();
    printf("time2 - time1 = %e\n", time2 - time1);

    double time3 = MxcsTime::GetTimeSec();
    printf("time3 - time1 = %e\n", time3 - time1);

    return status_prog;
}
