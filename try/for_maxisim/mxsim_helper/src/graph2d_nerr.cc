#include "mxcs_graph2d_nerr.h"

//
// public
//

void GraphDataNerr2d::Init(long ndata)
{
    NullGraphData2d();
    NewXvalArrAsDataArrayNerr1d();
    NewOvalArrAsDataArrayNerr1d();
    SetFlagXvalSorted(0);
    GetXvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);
}

GraphDataNerr2d* const GraphDataNerr2d::Clone() const
{
    GraphDataNerr2d* obj_new = new GraphDataNerr2d;
    obj_new->Copy(this);
    return obj_new;
}


void GraphDataNerr2d::Load(string file)
{
    NullGraphData2d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MxcsIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
        if(2 != ncolumn){
            MxcsPrintErrClass("ncolumn != 2");
            abort();
        }
        istringstream iss(line_arr[idata]);
        double xval, oval;
        iss >> xval >> oval;
        SetPoint(idata, xval, oval);
    }
    MxcsIolib::DelReadFile(line_arr);

    int flag_xval_sorted = 0;
    ReadInfo(file, &flag_xval_sorted);
    SetFlagXvalSorted(flag_xval_sorted);
}

void GraphDataNerr2d::Load(string file, string format)
{
    NullGraphData2d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MxcsIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, oval;
    if("x,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(2 != ncolumn){
                MxcsPrintErrClass("ncolumn != 2");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> oval;
            SetPoint(idata, xval, oval);
        }
    } else {
        MxcsPrintErrClass("bad format");
        abort();
    }
    MxcsIolib::DelReadFile(line_arr);

    int flag_xval_sorted = 0;
    ReadInfo(file, &flag_xval_sorted);
    SetFlagXvalSorted(flag_xval_sorted);
}


void GraphDataNerr2d::Sort()
{
    if(1 == GetFlagXvalSorted()){
        MxcsPrintInfoClass("It has been already sorted. Then return.");
        return;
    }
    if(NULL == GetXvalArr() || NULL == GetOvalArr()){
        MxcsPrintErrClass("GetXvalArr() == NULL or GetOvalArr() == NULL");
        abort();
    }

    long ndata = GetNdata();
    double* xval_org = new double [ndata];
    double* oval_org = new double [ndata];
    for(long idata = 0; idata < ndata; idata++){
        xval_org[idata] = GetXvalElm(idata);
        oval_org[idata] = GetOvalElm(idata);
    }

    long* index = new long [ndata];  // to store sort result
    bool down = false;
    MxcsSort::Sort<double, long>(ndata, xval_org, index, down);
  
    for(long idata = 0; idata < ndata; idata++){
        SetPoint(idata, xval_org[index[idata]], oval_org[index[idata]]);
    }

    delete [] xval_org; xval_org = NULL;
    delete [] oval_org; oval_org = NULL;
    delete [] index; index = NULL;
    SetFlagXvalSorted(1);
}

const DataArrayNerr1d* const GraphDataNerr2d::GetXvalArr() const
{
    return dynamic_cast<const DataArrayNerr1d*>(GetXvalArrNonConst());
}
    
const DataArrayNerr1d* const GraphDataNerr2d::GetOvalArr() const
{
    return dynamic_cast<const DataArrayNerr1d*>(GetOvalArrNonConst());
}

void GraphDataNerr2d::PrintData(FILE* fp, string format,
                                double offset_xval,
                                double offset_oval) const
{
    long ndata = GetNdata();
    if("x,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetOvalElm(idata) - offset_oval);
        }
    } else if ("x,y,ye" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetOvalElm(idata) - offset_oval,
                    0.0);
        }
    } else if ("x,xe,y,ye" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0,
                    GetOvalElm(idata) - offset_oval,
                    0.0);
        }
    } else if ("x,xe,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0,
                    GetOvalElm(idata) - offset_oval);
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
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

