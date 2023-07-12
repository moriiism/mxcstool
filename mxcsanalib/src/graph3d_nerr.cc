#include "mxcs_graph3d_nerr.h"

//
// public
//

void GraphDataNerr3d::Init(long ndata)
{
    NullGraphData3d();
    NewXvalArrAsDataArrayNerr1d();
    NewYvalArrAsDataArrayNerr1d();
    NewOvalArrAsDataArrayNerr1d();
    GetXvalArrNonConst()->Init(ndata);
    GetYvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);
}

GraphDataNerr3d* const GraphDataNerr3d::Clone() const
{
    GraphDataNerr3d* obj_new = new GraphDataNerr3d;
    obj_new->Copy(this);
    return obj_new;
}

void GraphDataNerr3d::Load(string file)
{
    NullGraphData3d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MxcsIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, yval, oval;
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
        if(3 != ncolumn){
            MxcsPrintErrClass("ncolumn != 3");
            abort();
        }
        istringstream iss(line_arr[idata]);
        iss >> xval >> yval >> oval;
        SetPoint(idata, xval, yval, oval);
    }
    MxcsIolib::DelReadFile(line_arr);
}


void GraphDataNerr3d::Load(string file, string format)
{
    NullGraphData3d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MxcsIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, yval, oval;
    if("x,y,z" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(3 != ncolumn){
                MxcsPrintErrClass("ncolumn != 3");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> yval >> oval;
            SetPoint(idata, xval, yval, oval);
        }
    } else {
        MxcsPrintErrClass("bad format");
        abort();
    }
    MxcsIolib::DelReadFile(line_arr);
}

const DataArrayNerr1d* const GraphDataNerr3d::GetXvalArr() const
{
    return dynamic_cast<const DataArrayNerr1d*>(GetXvalArrNonConst());
}

const DataArrayNerr1d* const GraphDataNerr3d::GetYvalArr() const
{
    return dynamic_cast<const DataArrayNerr1d*>(GetYvalArrNonConst());
}

const DataArrayNerr1d* const GraphDataNerr3d::GetOvalArr() const
{
    return dynamic_cast<const DataArrayNerr1d*>(GetOvalArrNonConst());
}

void GraphDataNerr3d::PrintData(FILE* fp, string format,
                                double offset_xval,
                                double offset_yval,
                                double offset_oval) const
{
    long ndata = GetNdata();
    if("x,y,z" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetYvalElm(idata) - offset_yval,
                    GetOvalElm(idata) - offset_oval);
        }
    } else if ("x,y,z,ze" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetYvalElm(idata) - offset_yval,
                    GetOvalElm(idata) - offset_oval,
                    0.0);
        }
    } else if ("x,xe,y,ye,z,ze" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0,
                    GetYvalElm(idata) - offset_yval,
                    0.0,                    
                    GetOvalElm(idata) - offset_oval,
                    0.0);
        }
    } else if ("x,xe,y,ye,z" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0,
                    GetYvalElm(idata) - offset_yval,
                    0.0,                    
                    GetOvalElm(idata) - offset_oval);
        }
    } else if ("x,y,z,ze+,ze-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetYvalElm(idata) - offset_yval,
                    GetOvalElm(idata) - offset_oval,
                    0.0, 0.0);
        }
    } else if ("x,xe,y,ye,z,ze+,ze-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0,
                    GetYvalElm(idata) - offset_yval,
                    0.0,
                    GetOvalElm(idata) - offset_oval,
                    0.0, 0.0);
        }
    } else if ("x,xe+,xe-,y,ye+,ye-,z,ze+,ze-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e  "
                    "%.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0, 0.0,
                    GetYvalElm(idata) - offset_yval,
                    0.0, 0.0,
                    GetOvalElm(idata) - offset_oval,
                    0.0, 0.0);
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MxcsPrintErrClass(msg);
        abort();
    }
}
