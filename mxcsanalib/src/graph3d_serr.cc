#include "mxcs_graph3d_serr.h"

//
// public
//

// Init

void GraphDataSerr3d::Init(long ndata)
{
    NullGraphData3d();
    NewXvalArrAsDataArraySerr1d();
    NewYvalArrAsDataArraySerr1d();
    NewOvalArrAsDataArraySerr1d();
    GetXvalArrNonConst()->Init(ndata);
    GetYvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);    
}

void GraphDataSerr3d::SetXvalSerrArr(long ndata, const double* const val_serr)
{
    GetXvalArrNonConst()->SetValSerr(ndata, val_serr);
}

void GraphDataSerr3d::SetXvalSerrArr(vector<double> val_serr)
{
    GetXvalArrNonConst()->SetValSerr(val_serr);
}

void GraphDataSerr3d::SetYvalSerrArr(long ndata, const double* const val_serr)
{
    GetYvalArrNonConst()->SetValSerr(ndata, val_serr);
}

void GraphDataSerr3d::SetYvalSerrArr(vector<double> val_serr)
{
    GetYvalArrNonConst()->SetValSerr(val_serr);
}

void GraphDataSerr3d::SetOvalSerrArr(long ndata, const double* const val_serr)
{
    GetOvalArrNonConst()->SetValSerr(ndata, val_serr);
}

void GraphDataSerr3d::SetOvalSerrArr(vector<double> val_serr)
{
    GetOvalArrNonConst()->SetValSerr(val_serr);
}

void GraphDataSerr3d::SetPoint(long idata,
                               double xval, double xval_serr,
                               double yval, double yval_serr,
                               double oval, double oval_serr)
{
    GetXvalArrNonConst()->SetValElm(idata, xval);
    GetXvalArrNonConst()->SetValSerrElm(idata, xval_serr);
    GetYvalArrNonConst()->SetValElm(idata, yval);
    GetYvalArrNonConst()->SetValSerrElm(idata, yval_serr);    
    GetOvalArrNonConst()->SetValElm(idata, oval);
    GetOvalArrNonConst()->SetValSerrElm(idata, oval_serr);
}


void GraphDataSerr3d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}


GraphDataSerr3d* const GraphDataSerr3d::Clone() const
{
    GraphDataSerr3d* obj_new = new GraphDataSerr3d;
    obj_new->Copy(this);
    return obj_new;
}

void GraphDataSerr3d::Load(string file)
{
    NullGraphData3d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MxcsIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, xval_serr, yval, yval_serr, oval, oval_serr;
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
        if(6 != ncolumn){
            MxcsPrintErrClass("ncolumn != 6");
            abort();
        }
        istringstream iss(line_arr[idata]);
        iss >> xval >> xval_serr
            >> yval >> yval_serr
            >> oval >> oval_serr;
        SetPoint(idata,
                 xval, xval_serr,
                 yval, yval_serr,
                 oval, oval_serr);
    }
    MxcsIolib::DelReadFile(line_arr);
}


void GraphDataSerr3d::Load(string file, string format)
{
    NullGraphData3d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MxcsIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, xval_serr, yval, yval_serr, oval, oval_serr;
    if("x,xe,y,ye,z,ze" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(6 != ncolumn){
                MxcsPrintErrClass("ncolumn != 6");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_serr
                >> yval >> yval_serr
                >> oval >> oval_serr;
            SetPoint(idata,
                     xval, xval_serr,
                     yval, yval_serr,
                     oval, oval_serr);
        }
    } else if("x,y,z,ze" == format){
        xval_serr = 0.0;
        yval_serr = 0.0;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(4 != ncolumn){
                MxcsPrintErrClass("ncolumn != 4");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval
                >> yval
                >> oval >> oval_serr;
            SetPoint(idata,
                     xval, xval_serr,
                     yval, yval_serr,
                     oval, oval_serr);
        }
    } else {
        MxcsPrintErrClass("bad format");
        abort();
    }
    MxcsIolib::DelReadFile(line_arr);
}


//
// const functions
//

const DataArraySerr1d* const GraphDataSerr3d::GetXvalArr() const
{
    return dynamic_cast<const DataArraySerr1d*>(GetXvalArrNonConst());
}

const DataArraySerr1d* const GraphDataSerr3d::GetYvalArr() const
{
    return dynamic_cast<const DataArraySerr1d*>(GetYvalArrNonConst());
}

const DataArraySerr1d* const GraphDataSerr3d::GetOvalArr() const
{
    return dynamic_cast<const DataArraySerr1d*>(GetOvalArrNonConst());
}

double GraphDataSerr3d::GetXvalSerrElm(long idata) const
{
    return GetXvalArr()->GetValSerrElm(idata);
}

double GraphDataSerr3d::GetYvalSerrElm(long idata) const
{
    return GetYvalArr()->GetValSerrElm(idata);
}

double GraphDataSerr3d::GetOvalSerrElm(long idata) const
{
    return GetOvalArr()->GetValSerrElm(idata);
}

// output

void GraphDataSerr3d::PrintData(FILE* fp, string format,
                                double offset_xval,
                                double offset_yval,
                                double offset_oval) const
{
    long ndata = GetNdata();
    if("x,xe,y,ye,z,ze" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetXvalSerrElm(idata),
                    GetYvalElm(idata) - offset_yval,
                    GetYvalSerrElm(idata),
                    GetOvalElm(idata) - offset_oval,
                    GetOvalSerrElm(idata));
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MxcsPrintErrClass(msg);
        abort();
    }
}
