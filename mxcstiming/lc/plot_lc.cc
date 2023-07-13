#include "mxcs_hist1d_serr.h"
#include "arg_plot_lc.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValPlotLc* argval = new ArgValPlotLc;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MxcsIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log;
    fp_log = fopen((argval->GetOutdir() + "/"
                    + argval->GetProgname() + ".log").c_str(), "w");
    
    DataArray1d* data_arr = NULL;
    GraphDataSerr2d* g2d  = NULL;

    if("x" == argval->GetFormat()){
        data_arr = new DataArray1d;
        data_arr->Load(argval->GetFile());
        data_arr->Sort();

        if("none" == argval->GetTbinfwidthStr()){
            MxcsPrintErr("bad tbinfwidth");
            abort();
        }
        double tbinfwidth = atof(argval->GetTbinfwidthStr().c_str());
        double time_lo = data_arr->GetValMin() - 0.5 * tbinfwidth;
        double time_up = data_arr->GetValMax() + 0.5 * tbinfwidth;
        long nbin_lc = MxcsMath::GetNbin(time_lo, time_up, tbinfwidth, "ceil");
        printf("nbin_lc = %ld\n", nbin_lc);
    
        HistData1d* h1d_lcbin = new HistData1d;
        h1d_lcbin->Init(nbin_lc, time_lo, time_up);

        for(long idata = 0; idata < data_arr->GetNdata(); idata ++){
            double time = data_arr->GetValElm(idata);
            h1d_lcbin->Fill(time);
        }
        string outqdp = argval->GetOutdir() + "/"
            + argval->GetOutfileHead() + ".qdp";
        h1d_lcbin->MkQdp(outqdp);

    } else {
        printf("format is (%s), then tbinfwidth_str (=%s) is ignored.\n",
               argval->GetFormat().c_str(),
               argval->GetTbinfwidthStr().c_str());
        
        g2d = new GraphDataSerr2d;
        g2d->Load(argval->GetFile(), argval->GetFormat());
        g2d->Sort();
        string outqdp = argval->GetOutdir() + "/"
            + argval->GetOutfileHead() + ".qdp";
        g2d->MkQdp(outqdp);
    }
    
    // cleaning
    delete argval;
    if(NULL != data_arr) { delete data_arr;}
    if(NULL != g2d) {delete g2d;}

    return status;
}

