#include "mxcs_iolib.h"
#include "mxcs_interval.h"
#include "mxcs_qdp_tool.h"
#include "arg_gti_index_list.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValGtiIndexList* argval = new ArgValGtiIndexList;
    argval->Init(argc, argv);
    argval->Print(stdout);
    
    Interval* gti = new Interval;
    gti->Load(argval->GetGti());

    string* line_arr = NULL;
    long nline = 0;
    MxcsIolib::GenReadFileSkipComment(argval->GetTimeList(),
                                      &line_arr,
                                      &nline);

    FILE* fp = fopen(argval->GetIndexListOut().c_str(), "w");
    for(long iline = 0; iline < nline; iline ++){
        int ncolumn = 0;
        string* split_arr = NULL;
        MxcsStr::GenSplit(line_arr[iline], &ncolumn, &split_arr);
        if(1 > ncolumn){
            MxcsPrintWarn("ncolum < 1");
            continue;
        }
        double time = atof(split_arr[0].c_str());
        long index = gti->GetIndexByTimeQuick(time);
        fprintf(fp, "%ld  %.15e  %.15e  %s  !  index  st  ed  <mjd etc>\n",
                index,
                gti->GetTstartElm(index),
                gti->GetTstopElm(index),
                line_arr[iline].c_str());
    }
    fclose(fp);
    MxcsIolib::DelReadFile(line_arr);


    delete argval;
    delete gti;
    
    return status;
}
