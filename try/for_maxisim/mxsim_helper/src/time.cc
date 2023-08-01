#include "mxcs_time.h"

double MxcsTime::GetTimeSec()
{
    struct timespec time_spec;
    clock_gettime(CLOCK_REALTIME, &time_spec);
    //printf("time: %10ld.%09ld CLOCK_REALTIME\n",
    //       time_spec_st.tv_sec, time_spec_st.tv_nsec);
    double time = time_spec.tv_sec + time_spec.tv_nsec * 1.0e-9;
    return time;
}
