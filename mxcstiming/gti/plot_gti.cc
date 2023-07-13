#include "mxcs_iolib.h"
#include "mxcs_interval.h"
#include "mxcs_qdp_tool.h"
#include "arg_plot_gti.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValPlotGti* argval = new ArgValPlotGti;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MxcsIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log = fopen((argval->GetOutdir() + "/"
                          + argval->GetProgname() + ".log").c_str(), "w");
    
    Interval* gti = new Interval;
    gti->Load(argval->GetGtiFile());
    
    double offset = gti->GetOffsetFromTag(argval->GetOffsetTag());
    printf("gti->GetNterm(): %ld\n", gti->GetNterm());
    fprintf(fp_log, "gti->GetNterm(): %ld\n", gti->GetNterm());

    MxcsQdpTool::MkQdp(gti, argval->GetOutdir() + "/"
                       + argval->GetOutfileHead()
                       + ".qdp");
    MxcsQdpTool::MkQdp(gti, argval->GetOutdir() + "/"
                       + argval->GetOutfileHead() 
                       + "_offset.qdp",
                       "", offset);
    return status;
}
