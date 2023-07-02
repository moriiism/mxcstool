#include "mxcs_qdp_tool.h"

void MxcsQdpTool::GetRangeQdp(double min, double max,
                              double* const low_ptr, double* const up_ptr)
{
    double width = (max - min) * 1.2;
    double center = (max + min) / 2.;
    double low = center - width / 2.;
    double up  = center + width / 2.;
    *low_ptr = low;
    *up_ptr  = up;
}

void MxcsQdpTool::PrintQdpRead(FILE* fp, string format)
{
    fprintf(fp, "\n");    
    if("x" == format){
        MxcsPrintErr("bad format");
        abort();

    } else if ("x,y" == format){
        fprintf(fp, "\n");
    } else if ("x,y,ye" == format){
        fprintf(fp, "read serr 2\n");
    } else if ("x,xe,y,ye" == format){
        fprintf(fp, "read serr 1 2\n");
    } else if ("x,xe,y" == format){
        fprintf(fp, "read serr 1\n");
    } else if ("x,y,ye+,ye-" == format){
        fprintf(fp, "read terr 2\n");
    } else if ("x,xe,y,ye+,ye-" == format){
        fprintf(fp, "read serr 1\n");
        fprintf(fp, "read terr 2\n");
    } else if ("x,xe+,xe-,y" == format){
        fprintf(fp, "read terr 1\n");
    } else if ("x,xe+,xe-,y,ye" == format){
        fprintf(fp, "read terr 1\n");
        fprintf(fp, "read serr 2\n");
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        fprintf(fp, "read terr 1 2\n");
    } else {
        MxcsPrintErr("bad format");
        abort();        
    }
    fprintf(fp, "\n");
}

void MxcsQdpTool::PrintQdpCmdStd(FILE* fp)
{
    fprintf(fp, "\n");
    fprintf(fp, "la file\n");
    fprintf(fp, "time off\n");    
    fprintf(fp, "lw 5\n");
    fprintf(fp, "csize 1.2\n");
    fprintf(fp, "la rot \n");
    fprintf(fp, "loc 0.05 0.05 0.95 0.95\n");
    fprintf(fp, "la pos y 3.0\n");
    fprintf(fp, "\n");    
}

void MxcsQdpTool::PrintQdpAxisRescale(FILE* fp, string xy,
                                      double val_lo, double val_up)
{
    char cmd[kLineSize];
    sprintf(cmd, "r  %s  %.15e  %.15e", xy.c_str(), val_lo, val_up);
    if( fabs(val_up - val_lo) > DBL_EPSILON ){
        fprintf(fp, "%s\n", cmd);
    }
}

void MxcsQdpTool::PrintQdpAxisTitle(FILE* fp, string xy,
                                    string title, double offset)
{
    char cmd[kLineSize];
    if(fabs(offset) < DBL_EPSILON){
        sprintf(cmd, "la %s %s",
                xy.c_str(), title.c_str());
    } else {
        sprintf(cmd, "la %s %s (offset = %.5e)",
                xy.c_str(), title.c_str(), offset);
    }
    fprintf(fp, "%s\n", cmd);
}

void MxcsQdpTool::PrintQdpScale(FILE* fp, string xy, string scale)
{
    if("log" == scale){
        fprintf(fp, "log   %s  on\n",
                xy.c_str());
    } else if("lin" == scale){
        fprintf(fp, "log   %s  off\n",
                xy.c_str());
    } else {
        abort();
    }
}

void MxcsQdpTool::PrintQdpCmdDiffPlot(
    FILE* fp,
    double xval_lo_data, double xval_up_data,
    double oval_lo_w1_data, double oval_up_w1_data,
    double oval_lo_w2_data, double oval_up_w2_data,
    double offset_xval,
    double offset_oval,
    double offset_oval_res,
    string title_xval,
    string title_oval,
    string title_oval_res,
    string scale_xval,
    string scale_oval,
    string scale_oval_res)
{
    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo_w1 = 0.0;
    double oval_up_w1 = 0.0;
    double oval_lo_w2 = 0.0;
    double oval_up_w2 = 0.0;
    GetRangeQdp(xval_lo_data,
                xval_up_data,
                &xval_lo, &xval_up);
    GetRangeQdp(oval_lo_w1_data,
                oval_up_w1_data,
                &oval_lo_w1, &oval_up_w1);
    GetRangeQdp(oval_lo_w2_data,
                oval_up_w2_data,
                &oval_lo_w2, &oval_up_w2);        
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_w1_shifted = oval_lo_w1 - offset_oval;
    double oval_up_w1_shifted = oval_up_w1 - offset_oval;
    double oval_lo_w2_shifted = oval_lo_w2 - offset_oval_res;
    double oval_up_w2_shifted = oval_up_w2 - offset_oval_res;
    
    PrintQdpCmdStd(fp);
    fprintf(fp, "win 1\n");
    fprintf(fp, "LOC  0.05 0.3 0.95 0.9\n");
    fprintf(fp, "LAB  NX OFF\n");
    fprintf(fp, "yplot 1 2\n");
    fprintf(fp, "line st on 2\n");
    fprintf(fp, "la pos y 3.0\n");    
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);    
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w1_shifted, oval_up_w1_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    PrintQdpScale(fp, "y", scale_oval);    

    fprintf(fp, "win 2\n");
    fprintf(fp, "LOC  0.05 0.1 0.95 0.39\n");
    fprintf(fp, "yplot 3\n");
    fprintf(fp, "la pos y 3.0\n");    
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval_res, offset_oval_res);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w2_shifted, oval_up_w2_shifted);
    PrintQdpScale(fp, "y", scale_oval_res);        
    
    fprintf(fp, "mark 22 on 1 3\n");
    fprintf(fp, "la 1 line 0.0 1.0 pos %.15e %.15e \" \" lst 4\n",
            xval_lo_shifted, 0.0);
}


void MxcsQdpTool::PrintQdpCmdDiffPlot(
    FILE* fp,
    double xval_lo_data, double xval_up_data,
    double oval_lo_w1_data, double oval_up_w1_data,
    double oval_lo_w2_data, double oval_up_w2_data,
    double offset_xval,
    double offset_oval,
    double offset_oval_res,
    const MxcsPlotConf* const plot_conf)
{
    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo_w1 = 0.0;
    double oval_up_w1 = 0.0;
    double oval_lo_w2 = 0.0;
    double oval_up_w2 = 0.0;
    GetRangeQdp(xval_lo_data,
                xval_up_data,
                &xval_lo, &xval_up);
    GetRangeQdp(oval_lo_w1_data,
                oval_up_w1_data,
                &oval_lo_w1, &oval_up_w1);
    GetRangeQdp(oval_lo_w2_data,
                oval_up_w2_data,
                &oval_lo_w2, &oval_up_w2);        
    double xval_lo_shifted = 0.0;
    double xval_up_shifted = 0.0;
    double oval_lo_w1_shifted = 0.0;
    double oval_up_w1_shifted = 0.0;
    double oval_lo_w2_shifted = 0.0;
    double oval_up_w2_shifted = 0.0;
    if("none" == plot_conf->GetLoStrElm(0)){
        xval_lo_shifted = xval_lo - offset_xval;
    } else {
        xval_lo_shifted = atof(plot_conf->GetLoStrElm(0).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(0)){
        xval_up_shifted = xval_up - offset_xval;
    } else {
        xval_up_shifted = atof(plot_conf->GetUpStrElm(0).c_str());
    }
    if("none" == plot_conf->GetLoStrElm(1)){
        oval_lo_w1_shifted = oval_lo_w1 - offset_oval;
    } else {
        oval_lo_w1_shifted = atof(plot_conf->GetLoStrElm(1).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(1)){
        oval_up_w1_shifted = oval_up_w1 - offset_oval;
    } else {
        oval_up_w1_shifted = atof(plot_conf->GetUpStrElm(1).c_str());
    }

    if("none" == plot_conf->GetLoStrElm(2)){
        oval_lo_w2_shifted = oval_lo_w2 - offset_oval_res;
    } else {
        oval_lo_w2_shifted = atof(plot_conf->GetLoStrElm(2).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(2)){
        oval_up_w2_shifted = oval_up_w2 - offset_oval_res;
    } else {
        oval_up_w2_shifted = atof(plot_conf->GetUpStrElm(2).c_str());
    }

    string title_xval = plot_conf->GetLabelElm(0);
    string title_oval = plot_conf->GetLabelElm(1);
    string title_oval_res = plot_conf->GetLabelElm(2);
    string scale_xval = plot_conf->GetScaleElm(0);
    string scale_oval = plot_conf->GetScaleElm(1);
    string scale_oval_res = plot_conf->GetScaleElm(2);
    
    PrintQdpCmdStd(fp);
    fprintf(fp, "win 1\n");
    fprintf(fp, "LOC  0.05 0.3 0.95 0.9\n");
    fprintf(fp, "LAB  NX OFF\n");
    fprintf(fp, "yplot 1 2\n");
    fprintf(fp, "line st on 2\n");
    fprintf(fp, "la pos y 3.0\n");    
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);    
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w1_shifted, oval_up_w1_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    PrintQdpScale(fp, "y", scale_oval);    

    fprintf(fp, "win 2\n");
    fprintf(fp, "LOC  0.05 0.1 0.95 0.39\n");
    fprintf(fp, "yplot 3\n");
    fprintf(fp, "la pos y 3.0\n");    
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval_res, offset_oval_res);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_w2_shifted, oval_up_w2_shifted);
    PrintQdpScale(fp, "y", scale_oval_res);        
    
    fprintf(fp, "mark 22 on 1 3\n");
    fprintf(fp, "la 1 line 0.0 1.0 pos %.15e %.15e \" \" lst 4\n",
            xval_lo_shifted, 0.0);
}


void MxcsQdpTool::MkQdpMode1(const DataArray1d* const data_array,
                             string qdpout,
                             string title_oval,
                             double offset_oval,
                             string scale_xval,
                             string scale_oval)
{
    //
    // index  data
    //
    
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    if("DataArrayNerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y");
    } else if ("DataArraySerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y,ye");
    } else if ("DataArrayTerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y,ye+,ye-");
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad class name");
        MxcsPrintErr(msg);
        abort();
    }
    string title_xval = "index";
    double offset_xval = 0.0;

    int mode = 1;
    data_array->PrintData(fp, mode, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;

    GetRangeQdp(0.0, data_array->GetNdata(),
                &xval_lo, &xval_up);
    GetRangeQdp(data_array->GetValAndErrMin(),
                data_array->GetValAndErrMax(),
                &oval_lo, &oval_up);
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_shifted = oval_lo - offset_oval;
    double oval_up_shifted = oval_up - offset_oval;

    PrintQdpCmdStd(fp);
    fprintf(fp, "ma 6 on\n");
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    PrintQdpScale(fp, "y", scale_oval);
    fclose(fp);
}


void MxcsQdpTool::MkQdpMode1(const DataArray1d* const data_array,
                             string qdpout,
                             const MxcsPlotConf* const plot_conf)
{
    //
    // index  data
    //

    if(2 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 2");
        MxcsPrintErr(msg);
        abort();
    }

    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    if("DataArrayNerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y");
    } else if ("DataArraySerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y,ye");
    } else if ("DataArrayTerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y,ye+,ye-");
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad class name");
        MxcsPrintErr(msg);
        abort();
    }

    string title_xval  = plot_conf->GetLabelElm(0);
    string title_oval  = plot_conf->GetLabelElm(1);
    // offset_xval must be "no"
    if("no" !=  plot_conf->GetOffsetTagElm(0) ){
        char msg[kLineSize];
        sprintf(msg, "offset_xval must be zero. Then, set offset_xval = no.");
        MxcsPrintErr(msg);
        abort();
    }
    double offset_xval = 0.0;
    double offset_oval = data_array->GetOffsetValFromTag(
        plot_conf->GetOffsetTagElm(1));


    int mode = 1;
    data_array->PrintData(fp, mode, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;
    GetRangeQdp(0.0, data_array->GetNdata(),
                &xval_lo, &xval_up);
    GetRangeQdp(data_array->GetValAndErrMin(),
                data_array->GetValAndErrMax(),
                &oval_lo, &oval_up);
    double xval_lo_shifted = 0.0;
    double xval_up_shifted = 0.0;
    double oval_lo_shifted = 0.0;
    double oval_up_shifted = 0.0;
    if("none" == plot_conf->GetLoStrElm(0)){
        xval_lo_shifted = xval_lo - offset_xval;
    } else {
        xval_lo_shifted = atof(plot_conf->GetLoStrElm(0).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(0)){
        xval_up_shifted = xval_up - offset_xval;
    } else {
        xval_up_shifted = atof(plot_conf->GetUpStrElm(0).c_str());
    }

    if("none" == plot_conf->GetLoStrElm(1)){
        oval_lo_shifted = oval_lo - offset_oval;
    } else {
        oval_lo_shifted = atof(plot_conf->GetLoStrElm(1).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(1)){
        oval_up_shifted = oval_up - offset_oval;
    } else {
        oval_up_shifted = atof(plot_conf->GetUpStrElm(1).c_str());
    }

    PrintQdpCmdStd(fp);
    fprintf(fp, "ma 6 on\n");    
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);    
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", plot_conf->GetScaleElm(0));
    PrintQdpScale(fp, "y", plot_conf->GetScaleElm(1));
    
    fclose(fp);
}


void MxcsQdpTool::MkQdpMode2(const DataArray1d* const data_array,
                             string qdpout,
                             string title_xval,
                             double offset_xval,
                             string scale_xval)
{
    //
    // data  1.0
    //
    
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    if("DataArrayNerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y");
    } else if ("DataArraySerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,xe,y");
    } else if ("DataArrayTerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,xe+,xe-,y");
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad class name");
        MxcsPrintErr(msg);
        abort();
    }

    string title_oval = "event";
    double offset_oval = 0.0;

    int mode = 2;
    data_array->PrintData(fp, mode, offset_xval);
    
    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = -0.5;
    double oval_up = +1.5;
    GetRangeQdp(0.0, data_array->GetNdata(),
                &xval_lo, &xval_up);
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_shifted = oval_lo - offset_oval;
    double oval_up_shifted = oval_up - offset_oval;

    PrintQdpCmdStd(fp);
    fprintf(fp, "ma 6 on\n");
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    fclose(fp);
}


void MxcsQdpTool::MkQdpMode2(const DataArray1d* const data_array,
                             string qdpout,
                             const MxcsPlotConf* const plot_conf)
{
    //
    // data  1.0
    //

    if(2 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 2");
        MxcsPrintErr(msg);
        abort();
    }
    
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    if("DataArrayNerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,y");
    } else if ("DataArraySerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,xe,y");
    } else if ("DataArrayTerr1d" == data_array->GetClassName()){
        PrintQdpRead(fp, "x,xe+,xe-,y");
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad class name");
        MxcsPrintErr(msg);
        abort();
    }

    string title_xval = plot_conf->GetLabelElm(0);
    string title_oval = plot_conf->GetLabelElm(1);
    double offset_xval = data_array->GetOffsetValFromTag(
        plot_conf->GetOffsetTagElm(0));    
    // offset_oval must be "no"
    if("no" !=  plot_conf->GetOffsetTagElm(1) ){
        char msg[kLineSize];
        sprintf(msg, "offset_oval must be zero. Then, set offset_oval = no.");
        MxcsPrintErr(msg);
        abort();
    }
    double offset_oval = 0.0;

    int mode = 2;
    data_array->PrintData(fp, mode, offset_xval);


    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = -0.5;
    double oval_up = +1.5;
    GetRangeQdp(0.0, data_array->GetNdata(),
                &xval_lo, &xval_up);    
    double xval_lo_shifted = 0.0;
    double xval_up_shifted = 0.0;
    double oval_lo_shifted = 0.0;
    double oval_up_shifted = 0.0;
    if("none" == plot_conf->GetLoStrElm(0)){
        xval_lo_shifted = xval_lo - offset_xval;
    } else {
        xval_lo_shifted = atof(plot_conf->GetLoStrElm(0).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(0)){
        xval_up_shifted = xval_up - offset_xval;
    } else {
        xval_up_shifted = atof(plot_conf->GetUpStrElm(0).c_str());
    }
    if("none" == plot_conf->GetLoStrElm(1)){
        oval_lo_shifted = oval_lo - offset_oval;
    } else {
        oval_lo_shifted = atof(plot_conf->GetLoStrElm(1).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(1)){
        oval_up_shifted = oval_up - offset_oval;
    } else {
        oval_up_shifted = atof(plot_conf->GetUpStrElm(1).c_str());
    }

    PrintQdpCmdStd(fp);
    fprintf(fp, "ma 6 on\n");    
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);    
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", plot_conf->GetScaleElm(0));
    fclose(fp);
}


void MxcsQdpTool::MkQdp(const GraphData2d* const graph_data,
                        string qdpout,
                        string format,
                        string title_xval,
                        string title_oval,
                        double offset_xval,
                        double offset_oval,
                        string scale_xval,
                        string scale_oval,
                        int flag_line,
                        int flag_mark)
{
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    PrintQdpRead(fp, format);

    graph_data->PrintData(fp, format, offset_xval, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;
    GetRangeQdp(graph_data->GetXvalArr()->GetValAndErrMin(),
                graph_data->GetXvalArr()->GetValAndErrMax(),
                &xval_lo, &xval_up);
    GetRangeQdp(graph_data->GetOvalArr()->GetValAndErrMin(),
                graph_data->GetOvalArr()->GetValAndErrMax(),
                &oval_lo, &oval_up);    
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_shifted = oval_lo - offset_oval;
    double oval_up_shifted = oval_up - offset_oval;
    
    PrintQdpCmdStd(fp);
    if(1 == flag_line){
        fprintf(fp, "line on\n");
    }
    if(1 == flag_mark){
        fprintf(fp, "ma 6 on\n");
    }
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    PrintQdpScale(fp, "y", scale_oval);
    fclose(fp);
}


void MxcsQdpTool::MkQdp(const GraphData2d* const graph_data,
                        string qdpout,
                        string format,
                        const MxcsPlotConf* const plot_conf,
                        int flag_line,
                        int flag_mark)
{
    if(2 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 2");
        MxcsPrintErr(msg);
        abort();
    }
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing \n");
    PrintQdpRead(fp, format);

    string title_xval = plot_conf->GetLabelElm(0);
    string title_oval = plot_conf->GetLabelElm(1);
    double offset_xval = graph_data->GetOffsetXFromTag(
        plot_conf->GetOffsetTagElm(0));
    double offset_oval = graph_data->GetOffsetOFromTag(
        plot_conf->GetOffsetTagElm(1));

    graph_data->PrintData(fp, format, offset_xval, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;
    GetRangeQdp(graph_data->GetXvalArr()->GetValAndErrMin(),
                graph_data->GetXvalArr()->GetValAndErrMax(),
                &xval_lo, &xval_up);
    GetRangeQdp(graph_data->GetOvalArr()->GetValAndErrMin(),
                graph_data->GetOvalArr()->GetValAndErrMax(),
                &oval_lo, &oval_up);    
    double xval_lo_shifted = 0.0;
    double xval_up_shifted = 0.0;
    double oval_lo_shifted = 0.0;
    double oval_up_shifted = 0.0;
    if("none" == plot_conf->GetLoStrElm(0)){
        xval_lo_shifted = xval_lo - offset_xval;
    } else {
        xval_lo_shifted = atof(plot_conf->GetLoStrElm(0).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(0)){
        xval_up_shifted = xval_up - offset_xval;
    } else {
        xval_up_shifted = atof(plot_conf->GetUpStrElm(0).c_str());
    }
    if("none" == plot_conf->GetLoStrElm(1)){
        oval_lo_shifted = oval_lo - offset_oval;
    } else {
        oval_lo_shifted = atof(plot_conf->GetLoStrElm(1).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(1)){
        oval_up_shifted = oval_up - offset_oval;
    } else {
        oval_up_shifted = atof(plot_conf->GetUpStrElm(1).c_str());
    }
    
    PrintQdpCmdStd(fp);
    if(1 == flag_line){
        fprintf(fp, "line on\n");
    }
    if(1 == flag_mark){
        fprintf(fp, "ma 6 on\n");
    }
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", plot_conf->GetScaleElm(0));
    PrintQdpScale(fp, "y", plot_conf->GetScaleElm(1));
    fclose(fp);
}


void MxcsQdpTool::MkQdp(const HistData1d* const hist_data,
                        string outqdp,
                        string format,
                        string title_xval,
                        string title_oval,
                        double offset_xval,
                        double offset_oval,
                        string scale_xval,
                        string scale_oval)
{
    string format_this = "";
    if("def" == format){
        if("HistDataNerr1d" == hist_data->GetClassName()){
            format_this = "x,y";
        } else if ("HistDataSerr1d" == hist_data->GetClassName()){
            format_this = "x,y,ye";
        } else if ("HistDataTerr1d" == hist_data->GetClassName()){
            format_this = "x,y,ye+,ye-";
        } else {
            MxcsPrintErr("bad classname");
            abort();
        }
    } else {
        format_this = format;
    }
    
    FILE* fp = fopen(outqdp.c_str(), "w");
    fprintf(fp, "skip sing \n");
    PrintQdpRead(fp, format_this);
    
    hist_data->PrintData(fp, format_this, offset_xval, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;
    GetRangeQdp(hist_data->GetXvalLo(),
                hist_data->GetXvalUp(),
                &xval_lo, &xval_up);
    GetRangeQdp(hist_data->GetOvalArr()->GetValAndErrMin(),
                hist_data->GetOvalArr()->GetValAndErrMax(),
                &oval_lo, &oval_up);    
    double xval_lo_shifted = xval_lo - offset_xval;
    double xval_up_shifted = xval_up - offset_xval;
    double oval_lo_shifted = oval_lo - offset_oval;
    double oval_up_shifted = oval_up - offset_oval;

    PrintQdpCmdStd(fp);
    fprintf(fp, "line st\n");
    fprintf(fp, "ma 6 on\n");
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", scale_xval);
    PrintQdpScale(fp, "y", scale_oval);
    fclose(fp);
}


void MxcsQdpTool::MkQdp(const HistData1d* const hist_data,
                        string outqdp,
                        string format,
                        const MxcsPlotConf* const plot_conf)
{
    string format_this = "";
    if("def" == format){
        if("HistDataNerr1d" == hist_data->GetClassName()){
            format_this = "x,y";
        } else if ("HistDataSerr1d" == hist_data->GetClassName()){
            format_this = "x,y,ye";
        } else if ("HistDataTerr1d" == hist_data->GetClassName()){
            format_this = "x,y,ye+,ye-";
        } else {
            MxcsPrintErr("bad classname");
            abort();
        }
    } else {
        format_this = format;
    }
    if(2 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 2");
        MxcsPrintErr(msg);
        abort();
    }

    FILE* fp = fopen(outqdp.c_str(), "w");
    fprintf(fp, "skip sing \n");
    PrintQdpRead(fp, format_this);

    string title_xval = plot_conf->GetLabelElm(0);
    string title_oval = plot_conf->GetLabelElm(1);
    double offset_xval = hist_data->GetOffsetXFromTag(
        plot_conf->GetOffsetTagElm(0));
    double offset_oval = hist_data->GetOffsetOFromTag(
        plot_conf->GetOffsetTagElm(1));

    hist_data->PrintData(fp, format_this, offset_xval, offset_oval);

    double xval_lo = 0.0;
    double xval_up = 0.0;
    double oval_lo = 0.0;
    double oval_up = 0.0;
    GetRangeQdp(hist_data->GetXvalLo(),
                hist_data->GetXvalUp(),
                &xval_lo, &xval_up);
    GetRangeQdp(hist_data->GetOvalArr()->GetValAndErrMin(),
                hist_data->GetOvalArr()->GetValAndErrMax(),
                &oval_lo, &oval_up);    
    double xval_lo_shifted = 0.0;
    double xval_up_shifted = 0.0;
    double oval_lo_shifted = 0.0;
    double oval_up_shifted = 0.0;
    if("none" == plot_conf->GetLoStrElm(0)){
        xval_lo_shifted = xval_lo - offset_xval;
    } else {
        xval_lo_shifted = atof(plot_conf->GetLoStrElm(0).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(0)){
        xval_up_shifted = xval_up - offset_xval;
    } else {
        xval_up_shifted = atof(plot_conf->GetUpStrElm(0).c_str());
    }
    if("none" == plot_conf->GetLoStrElm(1)){
        oval_lo_shifted = oval_lo - offset_oval;
    } else {
        oval_lo_shifted = atof(plot_conf->GetLoStrElm(1).c_str());
    }
    if("none" == plot_conf->GetUpStrElm(1)){
        oval_up_shifted = oval_up - offset_oval;
    } else {
        oval_up_shifted = atof(plot_conf->GetUpStrElm(1).c_str());
    }

    PrintQdpCmdStd(fp);
    fprintf(fp, "line st\n");
    fprintf(fp, "ma 6 on\n");    
    PrintQdpAxisTitle(fp, "x", title_xval, offset_xval);
    PrintQdpAxisTitle(fp, "y", title_oval, offset_oval);
    PrintQdpAxisRescale(fp, "x", xval_lo_shifted, xval_up_shifted);
    PrintQdpAxisRescale(fp, "y", oval_lo_shifted, oval_up_shifted);
    PrintQdpScale(fp, "x", plot_conf->GetScaleElm(0));
    PrintQdpScale(fp, "y", plot_conf->GetScaleElm(1));
    fclose(fp);
}


void MxcsQdpTool::MkQdp(const MxcsFunc* const func, const double* const par,
                        int npoint, double xval_lo, double xval_up,
                        string outqdp,
                        string title_xval,
                        string title_oval,
                        double offset_xval,
                        double offset_oval,
                        string scale_xval,
                        string scale_oval)
{
    GraphDataNerr2d* gd2d = new GraphDataNerr2d;
    gd2d->InitSetByFunc(func, par, npoint, xval_lo, xval_up, scale_xval);
    MkQdp(gd2d, outqdp, "x,y",
          title_xval, title_oval,
          offset_xval, offset_oval,
          scale_xval, scale_oval, 1, 0);
    delete gd2d;
}

void MxcsQdpTool::MkQdp(const MxcsFunc* const func, const double* const par,
                        int npoint, double xval_lo, double xval_up,
                        string outqdp,
                        const MxcsPlotConf* const plot_conf)
{
    if(2 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 2");
        MxcsPrintErr(msg);
        abort();
    }
    GraphDataNerr2d* gd2d = new GraphDataNerr2d;
    gd2d->InitSetByFunc(func, par, npoint, xval_lo, xval_up,
                        plot_conf->GetScaleElm(0));
    MkQdp(gd2d, outqdp, "x,y", plot_conf, 1, 0);
    delete gd2d;
}


void MxcsQdpTool::MkQdp(const Interval* const interval,
                        string qdpout,
                        string title_xval,
                        double offset_xval,
                        string scale_xval)
{
    vector<double> xval_vec;
    vector<double> oval_vec;
    for(int iterm = 0; iterm < interval->GetNterm(); iterm++){
        xval_vec.push_back(interval->GetTstartElm(iterm));
        oval_vec.push_back(0.0);
        xval_vec.push_back(interval->GetTstartElm(iterm));
        oval_vec.push_back(1.0);
        xval_vec.push_back(interval->GetTstopElm(iterm));
        oval_vec.push_back(1.0);
        xval_vec.push_back(interval->GetTstopElm(iterm));
        oval_vec.push_back(0.0);
    }
    GraphDataNerr2d* gd2d = new GraphDataNerr2d;
    gd2d->Init(xval_vec.size());
    gd2d->SetXvalArr(xval_vec);
    gd2d->SetOvalArr(oval_vec);
    gd2d->SetFlagXvalSorted(0);

    string title_oval = "GTI";
    double offset_oval = 0.0;
    MkQdp(gd2d, qdpout, "x,y",
          title_xval, title_oval,
          offset_xval, offset_oval,
          scale_xval, "lin",
          1, 0);
    delete gd2d;
}


void MxcsQdpTool::MkQdp(const Interval* const interval,
                        string qdpout,
                        const MxcsPlotConf* const plot_conf)
{
    if(2 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 2");
        MxcsPrintErr(msg);
        abort();
    }
    
    vector<double> xval_vec;
    vector<double> oval_vec;
    for(int iterm = 0; iterm < interval->GetNterm(); iterm++){
        xval_vec.push_back(interval->GetTstartElm(iterm));
        oval_vec.push_back(0.0);
        xval_vec.push_back(interval->GetTstartElm(iterm));
        oval_vec.push_back(1.0);
        xval_vec.push_back(interval->GetTstopElm(iterm));
        oval_vec.push_back(1.0);
        xval_vec.push_back(interval->GetTstopElm(iterm));
        oval_vec.push_back(0.0);
    }
    GraphDataNerr2d* gd2d = new GraphDataNerr2d;
    gd2d->Init(xval_vec.size());
    gd2d->SetXvalArr(xval_vec);
    gd2d->SetOvalArr(oval_vec);
    gd2d->SetFlagXvalSorted(0);
    MkQdp(gd2d, qdpout, "x,y", plot_conf, 1, 0);
    delete gd2d;
}


void MxcsQdpTool::MkQdpDiff(const GraphData2d* const graph_data,
                            const GraphData2d* const graph_model,
                            const GraphData2d* const graph_res,
                            string qdpout,
                            string format, 
                            string title_xval,
                            string title_oval,
                            string title_oval_res,
                            double offset_xval,
                            double offset_oval,
                            double offset_oval_res,
                            string scale_xval,
                            string scale_oval,
                            string scale_oval_res)
{
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing\n");
    PrintQdpRead(fp, format);
    fprintf(fp, "\n");

    graph_data->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    graph_model->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    graph_res->PrintData(fp, format, offset_xval, offset_oval_res);

    fprintf(fp, "\n");

    PrintQdpCmdDiffPlot(fp,
                        graph_data->GetXvalArr()->GetValAndErrMin(),
                        graph_data->GetXvalArr()->GetValAndErrMax(),
                        graph_data->GetOvalArr()->GetValAndErrMin(),
                        graph_data->GetOvalArr()->GetValAndErrMax(),
                        graph_res->GetOvalArr()->GetValAndErrMin(),
                        graph_res->GetOvalArr()->GetValAndErrMax(),
                        offset_xval, offset_oval, offset_oval_res,                        
                        title_xval, title_oval, title_oval_res,
                        scale_xval, scale_oval, scale_oval_res);
    fclose(fp);
}


void MxcsQdpTool::MkQdpDiff(const GraphData2d* const graph_data,
                            const GraphData2d* const graph_model,
                            const GraphData2d* const graph_res,
                            string qdpout,
                            string format,
                            const MxcsPlotConf* const plot_conf)

{
    if(3 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 3");
        MxcsPrintErr(msg);
        abort();
    }
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing\n");
    PrintQdpRead(fp, format);
    fprintf(fp, "\n");

    double offset_xval = graph_data->GetOffsetXFromTag(
        plot_conf->GetOffsetTagElm(0));
    double offset_oval = graph_data->GetOffsetOFromTag(
        plot_conf->GetOffsetTagElm(1));
    double offset_oval_res = graph_res->GetOffsetOFromTag(
        plot_conf->GetOffsetTagElm(2));
    
    graph_data->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    graph_model->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    graph_res->PrintData(fp, format, offset_xval, offset_oval_res);

    fprintf(fp, "\n");

    PrintQdpCmdDiffPlot(fp,
                        graph_data->GetXvalArr()->GetValAndErrMin(),
                        graph_data->GetXvalArr()->GetValAndErrMax(),
                        graph_data->GetOvalArr()->GetValAndErrMin(),
                        graph_data->GetOvalArr()->GetValAndErrMax(),
                        graph_res->GetOvalArr()->GetValAndErrMin(),
                        graph_res->GetOvalArr()->GetValAndErrMax(),
                        offset_xval, offset_oval, offset_oval_res,
                        plot_conf);
    fclose(fp);
}


void MxcsQdpTool::MkQdpDiff(const HistData1d* const hist_data,
                            const HistData1d* const hist_model,
                            const HistData1d* const hist_res,
                            string qdpout,
                            string format, 
                            string title_xval,
                            string title_oval,
                            string title_oval_res,
                            double offset_xval,
                            double offset_oval,
                            double offset_oval_res,
                            string scale_xval,
                            string scale_oval,
                            string scale_oval_res)
{
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing\n");
    PrintQdpRead(fp, format);    
    fprintf(fp, "\n");

    hist_data->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    hist_model->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    hist_res->PrintData(fp, format, offset_xval, offset_oval_res);

    fprintf(fp, "\n");

    PrintQdpCmdDiffPlot(fp,
                        hist_data->GetXvalLo(),
                        hist_data->GetXvalUp(),
                        hist_data->GetOvalArr()->GetValAndErrMin(),
                        hist_data->GetOvalArr()->GetValAndErrMax(),
                        hist_res->GetOvalArr()->GetValAndErrMin(),
                        hist_res->GetOvalArr()->GetValAndErrMax(),
                        offset_xval, offset_oval, offset_oval_res,                        
                        title_xval, title_oval, title_oval_res,
                        scale_xval, scale_oval, scale_oval_res);
    fclose(fp);
}


void MxcsQdpTool::MkQdpDiff(const HistData1d* const hist_data,
                            const HistData1d* const hist_model,
                            const HistData1d* const hist_res,
                            string qdpout,
                            string format,
                            const MxcsPlotConf* const plot_conf)
{
    if(3 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 3");
        MxcsPrintErr(msg);
        abort();
    }
    FILE* fp = fopen(qdpout.c_str(), "w");
    fprintf(fp, "skip sing\n");
    PrintQdpRead(fp, format);
    fprintf(fp, "\n");

    double offset_xval = hist_data->GetOffsetXFromTag(
        plot_conf->GetOffsetTagElm(0));
    double offset_oval = hist_data->GetOffsetOFromTag(
        plot_conf->GetOffsetTagElm(1));
    double offset_oval_res = hist_res->GetOffsetOFromTag(
        plot_conf->GetOffsetTagElm(2));
    
    hist_data->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    hist_model->PrintData(fp, format, offset_xval, offset_oval);

    fprintf(fp, "\n");
    fprintf(fp, "no\n");
    fprintf(fp, "\n");

    hist_res->PrintData(fp, format, offset_xval, offset_oval_res);

    fprintf(fp, "\n");

    PrintQdpCmdDiffPlot(fp,
                        hist_data->GetXvalLo(),
                        hist_data->GetXvalUp(),
                        hist_data->GetOvalArr()->GetValAndErrMin(),
                        hist_data->GetOvalArr()->GetValAndErrMax(),
                        hist_res->GetOvalArr()->GetValAndErrMin(),
                        hist_res->GetOvalArr()->GetValAndErrMax(),
                        offset_xval, offset_oval, offset_oval_res,
                        plot_conf);
    fclose(fp);
}

void MxcsQdpTool::MkQdpDiff3Serr(const GraphData2d* const graph_data,
                                 const MxcsFunc* const func,
                                 const double* const par,
                                 int npoint_func,
                                 string outdir, string qdpout_head,
                                 string title_xval,
                                 string title_oval,
                                 double offset_xval,
                                 double offset_oval,
                                 string scale_xval,
                                 string scale_oval)
{
    double xval_lo = 0.0;
    double xval_up = 0.0;
    GetRangeQdp(graph_data->GetXvalArr()->GetValAndErrMin(),
                graph_data->GetXvalArr()->GetValAndErrMax(),
                &xval_lo, &xval_up);

    GraphDataNerr2d* graph_func = new GraphDataNerr2d;
    graph_func->InitSetByFunc(func, par,
                              npoint_func, xval_lo, xval_up,
                              scale_xval);

    GraphDataSerr2d* graph_res_val   = new GraphDataSerr2d;
    GraphDataSerr2d* graph_res_chi   = new GraphDataSerr2d;
    GraphDataSerr2d* graph_res_ratio = new GraphDataSerr2d;
    GraphData2dOpe::GetResValGd2d(graph_data, func, par,
                                  graph_res_val);
    GraphData2dOpe::GetResChiGd2d(graph_data, func, par,
                                  graph_res_chi);
    GraphData2dOpe::GetResRatioGd2d(graph_data, func, par,
                                    graph_res_ratio);
    string format = "x,xe,y,ye";
    MkQdpDiff(graph_data, graph_func, graph_res_val, 
              outdir + "/" + qdpout_head + "_diff_val.qdp",
              format,
              title_xval, title_oval, "res_val",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");

    MkQdpDiff(graph_data, graph_func, graph_res_chi, 
              outdir + "/" + qdpout_head + "_diff_chi.qdp",
              format, 
              title_xval, title_oval, "chi",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");

    MkQdpDiff(graph_data, graph_func, graph_res_ratio, 
              outdir + "/" + qdpout_head + "_diff_ratio.qdp",
              format,
              title_xval, title_oval, "ratio",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");


    delete graph_res_val;
    delete graph_res_chi;
    delete graph_res_ratio;
    delete graph_func;
}

void MxcsQdpTool::MkQdpDiff3Serr(const GraphData2d* const graph_data,
                                 const MxcsFunc* const func,
                                 const double* const par,
                                 int npoint_func,
                                 string outdir, string qdpout_head,
                                 const MxcsPlotConf* const plot_conf)
{
    if(5 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 5");
        MxcsPrintErr(msg);
        abort();
    }
    
    double xval_lo = 0.0;
    double xval_up = 0.0;
    GetRangeQdp(graph_data->GetXvalArr()->GetValAndErrMin(),
                graph_data->GetXvalArr()->GetValAndErrMax(),
                &xval_lo, &xval_up);

    GraphDataNerr2d* graph_func = new GraphDataNerr2d;
    graph_func->InitSetByFunc(func, par,
                              npoint_func, xval_lo, xval_up,
                              plot_conf->GetScaleElm(0));


    GraphDataSerr2d* graph_res_val   = new GraphDataSerr2d;
    GraphDataSerr2d* graph_res_chi   = new GraphDataSerr2d;
    GraphDataSerr2d* graph_res_ratio = new GraphDataSerr2d;
    GraphData2dOpe::GetResValGd2d(graph_data, func, par,
                                  graph_res_val);
    GraphData2dOpe::GetResChiGd2d(graph_data, func, par,
                                  graph_res_chi);
    GraphData2dOpe::GetResRatioGd2d(graph_data, func, par,
                                    graph_res_ratio);
    
    MxcsPlotConf* plot_conf_val   = NULL;
    MxcsPlotConf* plot_conf_chi   = NULL;
    MxcsPlotConf* plot_conf_ratio = NULL;
    MxcsPlotConf::GenPlotConf3(plot_conf,
                               &plot_conf_val,
                               &plot_conf_chi,
                               &plot_conf_ratio);

    
    string format = "x,xe,y,ye";
    MkQdpDiff(graph_data, graph_func, graph_res_val, 
              outdir + "/" + qdpout_head + "_diff_val.qdp",
              format,
              plot_conf_val);

    MkQdpDiff(graph_data, graph_func, graph_res_chi, 
              outdir + "/" + qdpout_head + "_diff_chi.qdp",
              format,
              plot_conf_chi);

    MkQdpDiff(graph_data, graph_func, graph_res_ratio, 
              outdir + "/" + qdpout_head + "_diff_ratio.qdp",
              format,
              plot_conf_ratio);

    delete graph_res_val;
    delete graph_res_chi;
    delete graph_res_ratio;
    delete graph_func;
    delete plot_conf_val;
    delete plot_conf_chi;
    delete plot_conf_ratio;
}

void MxcsQdpTool::MkQdpDiff2Terr(const GraphData2d* const graph_data,
                                 const MxcsFunc* const func,
                                 const double* const par,
                                 int npoint_func,
                                 string outdir, string qdpout_head,
                                 string title_xval,
                                 string title_oval,
                                 double offset_xval,
                                 double offset_oval,
                                 string scale_xval,
                                 string scale_oval)
{
    double xval_lo = 0.0;
    double xval_up = 0.0;
    GetRangeQdp(graph_data->GetXvalArr()->GetValAndErrMin(),
                graph_data->GetXvalArr()->GetValAndErrMax(),
                &xval_lo, &xval_up);
    GraphDataNerr2d* graph_func = new GraphDataNerr2d;
    graph_func->InitSetByFunc(func, par,
                              npoint_func, xval_lo, xval_up,
                              scale_xval);

    GraphDataTerr2d* graph_res_val   = new GraphDataTerr2d;
    GraphDataTerr2d* graph_res_ratio = new GraphDataTerr2d;
    GraphData2dOpe::GetResValGd2d(graph_data, func, par,
                                  graph_res_val);
    GraphData2dOpe::GetResRatioGd2d(graph_data, func, par,
                                    graph_res_ratio);
    string format = "x,xe+,xe-,y,ye+,ye-";
    MkQdpDiff(graph_data, graph_func, graph_res_val, 
              outdir + "/" + qdpout_head + "_diff_val.qdp",
              format,
              title_xval, title_oval, "res_val",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");
    MkQdpDiff(graph_data, graph_func, graph_res_ratio, 
              outdir + "/" + qdpout_head + "_diff_ratio.qdp",
              format,
              title_xval, title_oval, "ratio",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");


    delete graph_res_val;
    delete graph_res_ratio;
    delete graph_func;
}

void MxcsQdpTool::MkQdpDiff2Terr(const GraphData2d* const graph_data,
                                 const MxcsFunc* const func,
                                 const double* const par,
                                 int npoint_func,
                                 string outdir, string qdpout_head,
                                 const MxcsPlotConf* const plot_conf)
{
    if(4 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 4");
        MxcsPrintErr(msg);
        abort();
    }
    
    double xval_lo = 0.0;
    double xval_up = 0.0;
    GetRangeQdp(graph_data->GetXvalArr()->GetValAndErrMin(),
                graph_data->GetXvalArr()->GetValAndErrMax(),
                &xval_lo, &xval_up);

    GraphDataNerr2d* graph_func = new GraphDataNerr2d;
    graph_func->InitSetByFunc(func, par,
                              npoint_func, xval_lo, xval_up,
                              plot_conf->GetScaleElm(0));


    GraphDataTerr2d* graph_res_val   = new GraphDataTerr2d;
    GraphDataTerr2d* graph_res_ratio = new GraphDataTerr2d;
    GraphData2dOpe::GetResValGd2d(graph_data, func, par,
                                  graph_res_val);
    GraphData2dOpe::GetResRatioGd2d(graph_data, func, par,
                                    graph_res_ratio);
    
    MxcsPlotConf* plot_conf_val   = NULL;
    MxcsPlotConf* plot_conf_ratio = NULL;
    MxcsPlotConf::GenPlotConf2(plot_conf,
                               &plot_conf_val,
                               &plot_conf_ratio);
    string format = "x,xe+,xe-,y,ye+,ye-";
    MkQdpDiff(graph_data, graph_func, graph_res_val, 
              outdir + "/" + qdpout_head + "_diff_val.qdp",
              format,
              plot_conf_val);

    MkQdpDiff(graph_data, graph_func, graph_res_ratio, 
              outdir + "/" + qdpout_head + "_diff_ratio.qdp",
              format,
              plot_conf_ratio);

    delete graph_res_val;
    delete graph_res_ratio;
    delete graph_func;
    delete plot_conf_val;
    delete plot_conf_ratio;
}


// hist_data, func
void MxcsQdpTool::MkQdpDiff3Serr(const HistData1d* const hist_data,
                                 const MxcsFunc* const func,
                                 const double* const par,
                                 int npoint_func,
                                 string outdir, string qdpout_head,
                                 string title_xval,
                                 string title_oval,
                                 double offset_xval,
                                 double offset_oval,
                                 string scale_xval,
                                 string scale_oval)
{
    double xval_lo = 0.0;
    double xval_up = 0.0;
    GetRangeQdp(hist_data->GetHi1d()->GetLo(),
                hist_data->GetHi1d()->GetUp(),
                &xval_lo, &xval_up);

    HistDataNerr1d* hist_func = new HistDataNerr1d;
    hist_func->Init(npoint_func, xval_lo, xval_up);
    hist_func->SetByFunc(func, par);

    HistDataSerr1d* hist_res_val   = new HistDataSerr1d;
    HistDataSerr1d* hist_res_chi   = new HistDataSerr1d;
    HistDataSerr1d* hist_res_ratio = new HistDataSerr1d;
    HistData1dOpe::GetResValHd1d(hist_data, func, par,
                                 hist_res_val);
    HistData1dOpe::GetResChiHd1d(hist_data, func, par,
                                 hist_res_chi);
    HistData1dOpe::GetResRatioHd1d(hist_data, func, par,
                                   hist_res_ratio);
    string format = "x,xe,y,ye";
    MkQdpDiff(hist_data, hist_func, hist_res_val, 
              outdir + "/" + qdpout_head + "_diff_val.qdp",
              format,
              title_xval, title_oval, "res_val",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");

    MkQdpDiff(hist_data, hist_func, hist_res_chi, 
              outdir + "/" + qdpout_head + "_diff_chi.qdp",
              format, 
              title_xval, title_oval, "chi",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");

    MkQdpDiff(hist_data, hist_func, hist_res_ratio, 
              outdir + "/" + qdpout_head + "_diff_ratio.qdp",
              format,
              title_xval, title_oval, "ratio",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");

    delete hist_res_val;
    delete hist_res_chi;
    delete hist_res_ratio;
    delete hist_func;
}
   
    
void MxcsQdpTool::MkQdpDiff3Serr(const HistData1d* const hist_data,
                                 const MxcsFunc* const func,
                                 const double* const par,
                                 int npoint_func,
                                 string outdir, string qdpout_head,
                                 const MxcsPlotConf* const plot_conf)
{
    if(5 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 5");
        MxcsPrintErr(msg);
        abort();
    }
    
    double xval_lo = 0.0;
    double xval_up = 0.0;
    GetRangeQdp(hist_data->GetHi1d()->GetLo(),
                hist_data->GetHi1d()->GetUp(),
                &xval_lo, &xval_up);    

    HistDataNerr1d* hist_func = new HistDataNerr1d;
    hist_func->Init(npoint_func, xval_lo, xval_up);
    hist_func->SetByFunc(func, par);

    HistDataSerr1d* hist_res_val   = new HistDataSerr1d;
    HistDataSerr1d* hist_res_chi   = new HistDataSerr1d;
    HistDataSerr1d* hist_res_ratio = new HistDataSerr1d;
    HistData1dOpe::GetResValHd1d(hist_data, func, par,
                                 hist_res_val);
    HistData1dOpe::GetResChiHd1d(hist_data, func, par,
                                 hist_res_chi);
    HistData1dOpe::GetResRatioHd1d(hist_data, func, par,
                                   hist_res_ratio);

    MxcsPlotConf* plot_conf_val   = NULL;
    MxcsPlotConf* plot_conf_chi   = NULL;
    MxcsPlotConf* plot_conf_ratio = NULL;
    MxcsPlotConf::GenPlotConf3(plot_conf,
                               &plot_conf_val,
                               &plot_conf_chi,
                               &plot_conf_ratio);
    
    string format = "x,xe,y,ye";
    MkQdpDiff(hist_data, hist_func, hist_res_val, 
              outdir + "/" + qdpout_head + "_diff_val.qdp",
              format,
              plot_conf_val);

    MkQdpDiff(hist_data, hist_func, hist_res_chi, 
              outdir + "/" + qdpout_head + "_diff_chi.qdp",
              format,
              plot_conf_chi);

    MkQdpDiff(hist_data, hist_func, hist_res_ratio, 
              outdir + "/" + qdpout_head + "_diff_ratio.qdp",
              format,
              plot_conf_ratio);

    delete hist_res_val;
    delete hist_res_chi;
    delete hist_res_ratio;
    delete hist_func;
    delete plot_conf_val;
    delete plot_conf_chi;
    delete plot_conf_ratio;    
}

void MxcsQdpTool::MkQdpDiff2Terr(const HistData1d* const hist_data,
                                 const MxcsFunc* const func,
                                 const double* const par,
                                 int npoint_func,
                                 string outdir, string qdpout_head,
                                 string title_xval,
                                 string title_oval,
                                 double offset_xval,
                                 double offset_oval,
                                 string scale_xval,
                                 string scale_oval)
{
    double xval_lo = 0.0;
    double xval_up = 0.0;
    GetRangeQdp(hist_data->GetHi1d()->GetLo(),
                hist_data->GetHi1d()->GetUp(),
                &xval_lo, &xval_up);    

    HistDataNerr1d* hist_func = new HistDataNerr1d;
    hist_func->Init(npoint_func, xval_lo, xval_up);
    hist_func->SetByFunc(func, par);

    HistDataTerr1d* hist_res_val   = new HistDataTerr1d;
    HistDataTerr1d* hist_res_ratio = new HistDataTerr1d;
    HistData1dOpe::GetResValHd1d(hist_data, func, par,
                                 hist_res_val);
    HistData1dOpe::GetResRatioHd1d(hist_data, func, par,
                                   hist_res_ratio);
    string format = "x,xe+,xe-,y,ye+,ye-";
    MkQdpDiff(hist_data, hist_func, hist_res_val, 
              outdir + "/" + qdpout_head + "_diff_val.qdp",
              format,
              title_xval, title_oval, "res_val",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");
    MkQdpDiff(hist_data, hist_func, hist_res_ratio,
              outdir + "/" + qdpout_head + "_diff_ratio.qdp",
              format,
              title_xval, title_oval, "ratio",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");

    delete hist_res_val;
    delete hist_res_ratio;
    delete hist_func;
}

void MxcsQdpTool::MkQdpDiff2Terr(const HistData1d* const hist_data,
                                 const MxcsFunc* const func,
                                 const double* const par,
                                 int npoint_func,
                                 string outdir, string qdpout_head,
                                 const MxcsPlotConf* const plot_conf)
{
    if(4 != plot_conf->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf->GetNdim() != 4");
        MxcsPrintErr(msg);
        abort();
    }
    
    double xval_lo = 0.0;
    double xval_up = 0.0;
    GetRangeQdp(hist_data->GetHi1d()->GetLo(),
                hist_data->GetHi1d()->GetUp(),
                &xval_lo, &xval_up);    

    HistDataNerr1d* hist_func = new HistDataNerr1d;
    hist_func->Init(npoint_func, xval_lo, xval_up);
    hist_func->SetByFunc(func, par);

    HistDataTerr1d* hist_res_val   = new HistDataTerr1d;
    HistDataTerr1d* hist_res_ratio = new HistDataTerr1d;
    HistData1dOpe::GetResValHd1d(hist_data, func, par,
                                 hist_res_val);
    HistData1dOpe::GetResRatioHd1d(hist_data, func, par,
                                   hist_res_ratio);

    MxcsPlotConf* plot_conf_val   = NULL;
    MxcsPlotConf* plot_conf_ratio = NULL;
    MxcsPlotConf::GenPlotConf2(plot_conf,
                               &plot_conf_val,
                               &plot_conf_ratio);
    
    string format = "x,xe+,xe-,y,ye+,ye-";
    MkQdpDiff(hist_data, hist_func, hist_res_val, 
              outdir + "/" + qdpout_head + "_diff_val.qdp",
              format,
              plot_conf_val);

    MkQdpDiff(hist_data, hist_func, hist_res_ratio, 
              outdir + "/" + qdpout_head + "_diff_ratio.qdp",
              format,
              plot_conf_ratio);

    delete hist_res_val;
    delete hist_res_ratio;
    delete hist_func;
    delete plot_conf_val;
    delete plot_conf_ratio;    
}
        

// plot N HistData in one qdp file
void MxcsQdpTool::MkQdpNhist(const HistData1d* const* const hist_arr,
                             int nhist,
                             string qdpout, double offset_xval)
{
    string func_name = "HistData1d::MkQdpNhist()";
    int nwin = nhist;
    FILE* fp = fopen(qdpout.c_str(), "w");

    fprintf(fp, "skip sing\n");
    fprintf(fp, "\n");

    for(int ihist = 0; ihist < nhist - 1; ihist++){
        hist_arr[ihist]->PrintData(fp, "x,y", offset_xval, 0.0);

        fprintf(fp, "\n");
        fprintf(fp, "no\n");
        fprintf(fp, "\n");
    }
    hist_arr[nhist - 1]->PrintData(fp, "x,y", offset_xval, 0.0);
    fprintf(fp, "\n");

    
    double* x_lo = new double [nhist];
    double* x_up  = new double [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        GetRangeQdp(hist_arr[ihist]->GetXvalLo(),
                    hist_arr[ihist]->GetXvalUp(),
                    &x_lo[ihist], &x_up[ihist]);
    }
    double x_lo_common = MxcsMath::GetMin(nhist, x_lo);
    double x_up_common = MxcsMath::GetMax(nhist, x_up);

    double* y_lo = new double [nhist];
    double* y_up  = new double [nhist];    
    for(int ihist = 0; ihist < nhist; ihist++){
        GetRangeQdp(hist_arr[ihist]->GetOvalArr()->GetValAndErrMin(),
                    hist_arr[ihist]->GetOvalArr()->GetValAndErrMax(),
                    &y_lo[ihist], &y_up[ihist]);    
    }
  
    fprintf(fp, "\n");
    fprintf(fp, "p v\n");
    fprintf(fp, "lw 5\n");
    fprintf(fp, "la rot\n");
    fprintf(fp, "csize 1.2\n");
    fprintf(fp, "line st\n");

    int ilabel = 1;
    for(int iwin = 0; iwin < nwin; iwin++){
        fprintf(fp, "win %d\n", iwin + 1);
        if(nwin - 1 != iwin){
            fprintf(fp, "LAB  NX OFF\n");
        }
        fprintf(fp, "r y %.15e %.15e\n", y_lo[iwin], y_up[iwin]);
        if(y_lo[iwin] <= 0 && 0 <= y_up[iwin]){
            fprintf(fp, "la %d line 0.0 1.0 pos %.15e %.15e \" \" lst 4\n",
                    ilabel, x_lo_common - offset_xval, 0.0);
            ilabel ++;
        }
        fprintf(fp, "la y %s\n", hist_arr[iwin]->GetTitle().c_str());
    }
    fprintf(fp, "la x offset = %.10e\n", offset_xval);
    
    fprintf(fp, "win all\n");
    fprintf(fp, "r x %.15e %.15e\n",
            x_lo_common - offset_xval, x_up_common - offset_xval);
    fprintf(fp, "line on \n");
    
    fclose(fp);
}


void MxcsQdpTool::MkQdpProj(const MxcsFunc* const func,
                            const double* const par,
                            double xval_lo, double xval_up,
                            double yval_lo, double yval_up,
                            string outdir, string qdpout_head,
                            string calc_mode,
                            int npoint_func,
                            string title_xval, string title_yval,
                            string title_oval,
                            double offset_xval, double offset_yval,
                            double offset_oval,
                            string scale_xval, string scale_yval,
                            string scale_oval)
{
    int nbin_func_x = npoint_func;
    int nbin_func_y = npoint_func;
    HistDataNerr2d* h2d_func = new HistDataNerr2d;
    h2d_func->Init(nbin_func_x, xval_lo, xval_up,
                   nbin_func_y, yval_lo, yval_up);
    h2d_func->SetByFunc(func, par);

    HistDataNerr1d* h1d_func_projx = new HistDataNerr1d;
    HistData2dOpe::GetProjectX(h2d_func,
                               0, h2d_func->GetNbinY() - 1,
                               calc_mode,
                               h1d_func_projx);
    HistDataNerr1d* h1d_func_projy = new HistDataNerr1d;
    HistData2dOpe::GetProjectY(h2d_func,
                               0, h2d_func->GetNbinX() - 1,
                               calc_mode,
                               h1d_func_projy);
    string outqdp_projx = outdir + "/" + qdpout_head + "_projx.qdp";
    string outqdp_projy = outdir + "/" + qdpout_head + "_projy.qdp";

    MkQdp(h1d_func_projx, outqdp_projx, "x,y",
          title_xval, title_oval,
          offset_xval, offset_oval,
          scale_xval, scale_oval);
    MkQdp(h1d_func_projy, outqdp_projy, "x,y",
          title_yval, title_oval,
          offset_yval, offset_oval,
          scale_yval, scale_oval);

    delete h2d_func;    
    delete h1d_func_projx;
    delete h1d_func_projy;
}


void MxcsQdpTool::MkQdpProj(const MxcsFunc* const func, const double* const par,
                            double xval_lo, double xval_up,
                            double yval_lo, double yval_up,
                            string outdir, string qdpout_head,
                            string calc_mode,
                            int npoint_func,
                            const MxcsPlotConf* const plot_conf_projx,
                            const MxcsPlotConf* const plot_conf_projy)
{
    if(2 != plot_conf_projx->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf_projx->GetNdim() != 2");
        MxcsPrintErr(msg);
        abort();
    }
    if(2 != plot_conf_projy->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf_projy->GetNdim() != 2");
        MxcsPrintErr(msg);
        abort();
    }
    
    int nbin_func_x = npoint_func;
    int nbin_func_y = npoint_func;
    HistData2d* h2d_func = new HistDataNerr2d;
    h2d_func->Init(nbin_func_x, xval_lo, xval_up,
                   nbin_func_y, yval_lo, yval_up);
    h2d_func->SetByFunc(func, par);

    HistDataNerr1d* h1d_func_projx = new HistDataNerr1d;
    HistData2dOpe::GetProjectX(h2d_func,
                               0, h2d_func->GetNbinY() - 1,
                               calc_mode,
                               h1d_func_projx);
    HistDataNerr1d* h1d_func_projy = new HistDataNerr1d;
    HistData2dOpe::GetProjectY(h2d_func,
                               0, h2d_func->GetNbinX() - 1,
                               calc_mode,
                               h1d_func_projy);
    string outqdp_projx = outdir + "/" + qdpout_head + "_projx.qdp";
    string outqdp_projy = outdir + "/" + qdpout_head + "_projy.qdp";

    MkQdp(h1d_func_projx, outqdp_projx, "x,y",
          plot_conf_projx);
    MkQdp(h1d_func_projy, outqdp_projy, "x,y",
          plot_conf_projy);

    delete h2d_func;    
    delete h1d_func_projx;
    delete h1d_func_projy;
}


void MxcsQdpTool::MkQdpDiffProjSerr(const HistData2d* const hist_data,
                                    const MxcsFunc* const func,
                                    const double* const par,
                                    string outdir, string qdpout_head,
                                    string add_mode, string error_mode,
                                    string title_xval,
                                    string title_yval,
                                    string title_oval,
                                    double offset_xval,
                                    double offset_yval,
                                    double offset_oval,
                                    string scale_xval,
                                    string scale_yval,
                                    string scale_oval)
{
    HistDataSerr1d* h1d_projx = new HistDataSerr1d;
    HistData2dOpe::GetProjectX(hist_data,
                               0, hist_data->GetNbinY() - 1,
                               add_mode, error_mode,
                               h1d_projx);
    HistDataSerr1d* h1d_projy = new HistDataSerr1d;
    HistData2dOpe::GetProjectY(hist_data,
                               0, hist_data->GetNbinX() - 1,
                               add_mode, error_mode,
                               h1d_projy);
    long nbin_func_x = hist_data->GetNbinX();
    long nbin_func_y = hist_data->GetNbinY();    
    double xval_lo = hist_data->GetXvalLo();
    double xval_up = hist_data->GetXvalUp();
    double yval_lo = hist_data->GetYvalLo();
    double yval_up = hist_data->GetYvalUp();

    HistData2d* h2d_func = new HistDataNerr2d;
    h2d_func->Init(nbin_func_x, xval_lo, xval_up,
                   nbin_func_y, yval_lo, yval_up);

    h2d_func->SetByFunc(func, par);
    HistDataNerr1d* h1d_func_projx = new HistDataNerr1d;
    HistData2dOpe::GetProjectX(h2d_func,
                               0, h2d_func->GetNbinY() - 1,
                               add_mode,
                               h1d_func_projx);
    HistDataNerr1d* h1d_func_projy = new HistDataNerr1d;
    HistData2dOpe::GetProjectY(h2d_func,
                               0, h2d_func->GetNbinX() - 1,
                               add_mode,
                               h1d_func_projy);
    HistDataSerr1d* h1d_projx_res_val   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projx_res_chi   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projx_res_ratio = new HistDataSerr1d;
    HistData1dOpe::GetResValHd1d(h1d_projx, h1d_func_projx,
                                 h1d_projx_res_val);
    HistData1dOpe::GetResChiHd1d(h1d_projx, h1d_func_projx,
                                 h1d_projx_res_chi);
    HistData1dOpe::GetResRatioHd1d(h1d_projx, h1d_func_projx,
                                   h1d_projx_res_ratio);

    HistDataSerr1d* h1d_projy_res_val   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projy_res_chi   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projy_res_ratio = new HistDataSerr1d;
    HistData1dOpe::GetResValHd1d(h1d_projy, h1d_func_projy,
                                 h1d_projy_res_val);
    HistData1dOpe::GetResChiHd1d(h1d_projy, h1d_func_projy,
                                 h1d_projy_res_chi);
    HistData1dOpe::GetResRatioHd1d(h1d_projy, h1d_func_projy,
                                   h1d_projy_res_ratio);
    string format = "x,xe,y,ye";
    MkQdpDiff(h1d_projx, h1d_func_projx, h1d_projx_res_val, 
              outdir + "/" + qdpout_head + "_projx_diff_val.qdp",
              format,
              title_xval, title_oval, "res_val",
              offset_xval, offset_oval, 0.0,
              scale_xval, scale_oval, "lin");
    MkQdpDiff(h1d_projy, h1d_func_projy, h1d_projy_res_val, 
              outdir + "/" + qdpout_head + "_projy_diff_val.qdp",
              format,
              title_yval, title_oval, "res_val",
              offset_yval, offset_oval, 0.0,
              scale_yval, scale_oval, "lin");

    if(0 < g_flag_verbose){
        MkQdpDiff(h1d_projx, h1d_func_projx, h1d_projx_res_chi, 
                  outdir + "/" + qdpout_head + "_projx_diff_chi.qdp",
                  format,
                  title_xval, title_oval, "chi",
                  offset_xval, offset_oval, 0.0,
                  scale_xval, scale_oval, "lin");

        MkQdpDiff(h1d_projx, h1d_func_projx, h1d_projx_res_ratio, 
                  outdir + "/" + qdpout_head + "_projx_diff_ratio.qdp",
                  format,
                  title_xval, title_oval, "ratio",
                  offset_xval, offset_oval, 0.0,
                  scale_xval, scale_oval, "lin");

        MkQdpDiff(h1d_projy, h1d_func_projy, h1d_projy_res_chi, 
                  outdir + "/" + qdpout_head + "_projy_diff_chi.qdp",
                  format,
                  title_yval, title_oval, "chi",
                  offset_yval, offset_oval, 0.0,
                  scale_yval, scale_oval, "lin");

        MkQdpDiff(h1d_projy, h1d_func_projy, h1d_projy_res_ratio, 
                  outdir + "/" + qdpout_head + "_projy_diff_ratio.qdp",
                  format,
                  title_yval, title_oval, "ratio",
                  offset_yval, offset_oval, 0.0,
                  scale_yval, scale_oval, "lin");
    }
    
    delete h1d_projx;
    delete h1d_projy;
    delete h2d_func;
    delete h1d_func_projx;
    delete h1d_func_projy;
    delete h1d_projx_res_val;
    delete h1d_projx_res_chi;
    delete h1d_projx_res_ratio;
    delete h1d_projy_res_val;
    delete h1d_projy_res_chi;
    delete h1d_projy_res_ratio;
}



void MxcsQdpTool::MkQdpDiffProjSerr(const HistData2d* const hist_data,
                                    const MxcsFunc* const func,
                                    const double* const par,
                                    string outdir, string qdpout_head,
                                    string add_mode, string error_mode,
                                    const MxcsPlotConf* const plot_conf_projx,
                                    const MxcsPlotConf* const plot_conf_projy)
{
    if(5 != plot_conf_projx->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf_projx->GetNdim() != 5");
        MxcsPrintErr(msg);
        abort();
    }
    if(5 != plot_conf_projy->GetNdim()){
        char msg[kLineSize];
        sprintf(msg, "plot_conf_projy->GetNdim() != 5");
        MxcsPrintErr(msg);
        abort();
    }
   
    HistDataSerr1d* h1d_projx = new HistDataSerr1d;
    HistData2dOpe::GetProjectX(hist_data,
                               0, hist_data->GetNbinY() - 1,
                               add_mode, error_mode,
                               h1d_projx);
    HistDataSerr1d* h1d_projy = new HistDataSerr1d;
    HistData2dOpe::GetProjectY(hist_data,
                               0, hist_data->GetNbinX() - 1,
                               add_mode, error_mode,
                               h1d_projy);

    long nbin_func_x = hist_data->GetNbinX();
    long nbin_func_y = hist_data->GetNbinY();    
    double xval_lo = hist_data->GetXvalLo();
    double xval_up = hist_data->GetXvalUp();
    double yval_lo = hist_data->GetYvalLo();
    double yval_up = hist_data->GetYvalUp();

    HistData2d* h2d_func = new HistDataNerr2d;
    h2d_func->Init(nbin_func_x, xval_lo, xval_up,
                   nbin_func_y, yval_lo, yval_up);

    h2d_func->SetByFunc(func, par);
    HistDataNerr1d* h1d_func_projx = new HistDataNerr1d;
    HistData2dOpe::GetProjectX(h2d_func,
                               0, h2d_func->GetNbinY() - 1,
                               add_mode,
                               h1d_func_projx);
    HistDataNerr1d* h1d_func_projy = new HistDataNerr1d;
    HistData2dOpe::GetProjectY(h2d_func,
                               0, h2d_func->GetNbinX() - 1,
                               add_mode,
                               h1d_func_projy);
    HistDataSerr1d* h1d_projx_res_val   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projx_res_chi   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projx_res_ratio = new HistDataSerr1d;
    HistData1dOpe::GetResValHd1d(h1d_projx, h1d_func_projx,
                                 h1d_projx_res_val);
    HistData1dOpe::GetResChiHd1d(h1d_projx, h1d_func_projx,
                                 h1d_projx_res_chi);
    HistData1dOpe::GetResRatioHd1d(h1d_projx, h1d_func_projx,
                                   h1d_projx_res_ratio);

    HistDataSerr1d* h1d_projy_res_val   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projy_res_chi   = new HistDataSerr1d;
    HistDataSerr1d* h1d_projy_res_ratio = new HistDataSerr1d;
    HistData1dOpe::GetResValHd1d(h1d_projy, h1d_func_projy,
                                 h1d_projy_res_val);
    HistData1dOpe::GetResChiHd1d(h1d_projy, h1d_func_projy,
                                 h1d_projy_res_chi);
    HistData1dOpe::GetResRatioHd1d(h1d_projy, h1d_func_projy,
                                   h1d_projy_res_ratio);

    MxcsPlotConf* plot_conf_val_projx   = NULL;
    MxcsPlotConf* plot_conf_chi_projx   = NULL;
    MxcsPlotConf* plot_conf_ratio_projx = NULL;
    MxcsPlotConf* plot_conf_val_projy   = NULL;
    MxcsPlotConf* plot_conf_chi_projy   = NULL;
    MxcsPlotConf* plot_conf_ratio_projy = NULL;
    MxcsPlotConf::GenPlotConf3(plot_conf_projx,
                               &plot_conf_val_projx,
                               &plot_conf_chi_projx,
                               &plot_conf_ratio_projx);
    MxcsPlotConf::GenPlotConf3(plot_conf_projy,
                               &plot_conf_val_projy,
                               &plot_conf_chi_projy,
                               &plot_conf_ratio_projy);    
    
    string format = "x,xe,y,ye";
    MkQdpDiff(h1d_projx, h1d_func_projx, h1d_projx_res_val, 
              outdir + "/" + qdpout_head + "_projx_diff_val.qdp",
              format,
              plot_conf_val_projx);
    MkQdpDiff(h1d_projy, h1d_func_projy, h1d_projy_res_val, 
              outdir + "/" + qdpout_head + "_projy_diff_val.qdp",
              format,
              plot_conf_val_projy);

    if(0 < g_flag_verbose){
        MkQdpDiff(h1d_projx, h1d_func_projx, h1d_projx_res_chi, 
                  outdir + "/" + qdpout_head + "_projx_diff_chi.qdp",
                  format,
                  plot_conf_chi_projx);

        MkQdpDiff(h1d_projx, h1d_func_projx, h1d_projx_res_ratio, 
                  outdir + "/" + qdpout_head + "_projx_diff_ratio.qdp",
                  format,
                  plot_conf_ratio_projx);

        MkQdpDiff(h1d_projy, h1d_func_projy, h1d_projy_res_chi, 
                  outdir + "/" + qdpout_head + "_projy_diff_chi.qdp",
                  format,
                  plot_conf_chi_projy);

        MkQdpDiff(h1d_projy, h1d_func_projy, h1d_projy_res_ratio, 
                  outdir + "/" + qdpout_head + "_projy_diff_ratio.qdp",
                  format,
                  plot_conf_ratio_projy);
    }
    
    delete h1d_projx;
    delete h1d_projy;
    delete h2d_func;
    delete h1d_func_projx;
    delete h1d_func_projy;
    delete h1d_projx_res_val;
    delete h1d_projx_res_chi;
    delete h1d_projx_res_ratio;
    delete h1d_projy_res_val;
    delete h1d_projy_res_chi;
    delete h1d_projy_res_ratio;
    delete plot_conf_val_projx;
    delete plot_conf_chi_projx;
    delete plot_conf_ratio_projx;
    delete plot_conf_val_projy;
    delete plot_conf_chi_projy;
    delete plot_conf_ratio_projy;
}

