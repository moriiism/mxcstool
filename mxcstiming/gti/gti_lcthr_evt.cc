#include "mxcs_graph2d_serr.h"
#include "mxcs_hist_info.h"
#include "mxcs_hist1d_nerr.h"
#include "mxcs_qdp_tool.h"

#include "arg_gti_lcthr_evt.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValLcthrEvt* argval = new ArgValLcthrEvt;
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

    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    da1d->Load(argval->GetFile());
    da1d->Sort();
    
    //
    // hist_info
    //
    HistInfo1d* hist_info = new HistInfo1d;
    hist_info->InitSetByWidth(floor(da1d->GetValMin()),
                              ceil(da1d->GetValMax()),
                              argval->GetBinWidth(),
                              "ceil");
    //
    // count
    //
    HistDataSerr1d* hd1d_count = new HistDataSerr1d;
    hd1d_count->Init(hist_info);

    for(long idata = 0; idata < da1d->GetNdata(); idata ++){
        double time = da1d->GetValElm(idata);
        hd1d_count->Fill(time);
    }
    string outdat_count = argval->GetOutdir() + "/"
        + argval->GetOutfileHead() + "_count.dat";
    hd1d_count->Save(outdat_count, "x,xe,y,ye");

    //
    // rate (counts/sec)
    //
    HistDataSerr1d* hd1d_rate = new HistDataSerr1d;
    HistData1dOpe::GetScale(hd1d_count,
                            1./hd1d_count->GetHi1d()->GetBinWidth(),
                            0.0, hd1d_rate);

    string outdat_rate = argval->GetOutdir() + "/"
        + argval->GetOutfileHead() + "_rate.dat";
    hd1d_rate->Save(outdat_rate, "x,xe,y,ye");


    Interval* gti = hd1d_rate->GenIntervalAboveThreshold(
        argval->GetThreshold());

    double offset = gti->GetOffsetFromTag(argval->GetOffsetTag());
    MxcsIolib::Printf2(fp_log, "gti->GetNterm(): %d\n",
                       gti->GetNterm());
    MxcsQdpTool::MkQdp(gti, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + ".qdp");
    MxcsQdpTool::MkQdp(gti, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + "_offset.qdp",
                       "", offset);
    gti->Save(argval->GetGtiOut());

    // clean
    fclose(fp_log);
    delete argval;
    delete da1d;
    delete hd1d_count;
    delete hd1d_rate;
    delete gti;

    return status;
}
