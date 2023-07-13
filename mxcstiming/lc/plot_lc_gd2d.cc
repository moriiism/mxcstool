#include "mxcs_graph2d_serr.h"
#include "mxcs_graph2d_terr.h"
#include "mxcs_qdp_tool.h"
#include "arg_plot_lc_gd2d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValPlotLcGd2d* argval = new ArgValPlotLcGd2d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    GraphData2d* gd2d = GraphData2dOpe::GenGd2dByLoad(
        argval->GetFileIn(), argval->GetFormat() );
    gd2d->Sort();

    MxcsPlotConf* plot_conf = new MxcsPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());

    MxcsQdpTool::MkQdp(gd2d, argval->GetFileOut(), argval->GetFormat());

    // cleaning
    delete argval;
    if(NULL != gd2d) {delete gd2d;}
    if(NULL != plot_conf) {delete plot_conf;}

    return status;
}

