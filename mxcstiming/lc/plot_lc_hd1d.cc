#include "mxcs_hist1d_serr.h"
#include "mxcs_qdp_tool.h"
#include "arg_plot_lc_hd1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValPlotLcHd1d* argval = new ArgValPlotLcHd1d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    MxcsPlotConf* plot_conf = new MxcsPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    plot_conf->Print(stdout);

    HistData1d* hd1d = HistData1dOpe::GenHd1dByLoad(argval->GetFileIn());
    MxcsQdpTool::MkQdp(hd1d, argval->GetFileOut(),
                       argval->GetFormat(), plot_conf);

    //
    // cleaning
    //
    delete argval;
    if(NULL != hd1d) {delete hd1d;}
    if(NULL != plot_conf) {delete plot_conf;}
    
    return status;
}

