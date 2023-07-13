#include "mxcs_iolib.h"
#include "mxcs_interval.h"
#include "mxcs_qdp_tool.h"
#include "arg_gti_margin.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValMargin* argval = new ArgValMargin;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MxcsIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log = NULL;
    fp_log = fopen((argval->GetOutdir() + "/"
                    + argval->GetProgname() + ".log").c_str(), "w");

    Interval* gti = new Interval;
    gti->Load(argval->GetGtiFile());
  
    Interval* gti_out = new Interval;
    gti_out->AddMargin(gti, argval->GetTimeMargin(),
                       Telescope::GetTimeAccuracy(argval->GetTelescope(),
                                                  argval->GetTunit()));
    double offset = gti_out->GetOffsetFromTag(argval->GetOffsetTag());
    MxcsIolib::Printf2(fp_log, "gti_out->GetNterm(): %d\n", gti_out->GetNterm());
    MxcsQdpTool::MkQdp(gti_out, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + ".qdp");
    MxcsQdpTool::MkQdp(gti_out, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + "_offset.qdp",
                       "", offset);
    gti_out->Save(argval->GetGtiOut());
  
    return status;
}
