#include "mxcs_graph2d_terr.h"

//
// public
//

// Init

void GraphDataTerr2d::Init(long ndata)
{
    NullGraphData2d();
    NewXvalArrAsDataArrayTerr1d();
    NewOvalArrAsDataArrayTerr1d();
    SetFlagXvalSorted(0);
    GetXvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);    
}

void GraphDataTerr2d::SetXvalTerrArr(long ndata, const double* const val_serr)
{
    GetXvalArrNonConst()->SetValTerr(ndata, val_serr);
}

void GraphDataTerr2d::SetXvalTerrArr(vector<double> val_serr)
{
    GetXvalArrNonConst()->SetValTerr(val_serr);
}
    
void GraphDataTerr2d::SetXvalTerrArr(long ndata,
                                     const double* const val_terr_plus,
                                     const double* const val_terr_minus)
{
    GetXvalArrNonConst()->SetValTerr(ndata, val_terr_plus, val_terr_minus);
}

void GraphDataTerr2d::SetXvalTerrArr(vector<double> val_terr_plus,
                                     vector<double> val_terr_minus)
{
    GetXvalArrNonConst()->SetValTerr(val_terr_plus, val_terr_minus);
}


void GraphDataTerr2d::SetOvalTerrArr(long ndata, const double* const val_serr)
{
    GetOvalArrNonConst()->SetValTerr(ndata, val_serr);
}

void GraphDataTerr2d::SetOvalTerrArr(vector<double> val_serr)
{
    GetOvalArrNonConst()->SetValTerr(val_serr);
}
    
void GraphDataTerr2d::SetOvalTerrArr(long ndata,
                                     const double* const val_terr_plus,
                                     const double* const val_terr_minus)
{
    GetOvalArrNonConst()->SetValTerr(ndata, val_terr_plus, val_terr_minus);
}

void GraphDataTerr2d::SetOvalTerrArr(vector<double> val_terr_plus,
                                     vector<double> val_terr_minus)
{
    GetOvalArrNonConst()->SetValTerr(val_terr_plus, val_terr_minus);
}

void GraphDataTerr2d::SetPoint(long idata,
                               double xval,
                               double xval_terr_plus,
                               double xval_terr_minus,
                               double oval,
                               double oval_terr_plus,
                               double oval_terr_minus)
{
    GetXvalArrNonConst()->SetValElm(idata, xval);
    GetXvalArrNonConst()->SetValTerrPlusElm(idata, xval_terr_plus);
    GetXvalArrNonConst()->SetValTerrMinusElm(idata, xval_terr_minus);
    GetOvalArrNonConst()->SetValElm(idata, oval);
    GetOvalArrNonConst()->SetValTerrPlusElm(idata, oval_terr_plus);
    GetOvalArrNonConst()->SetValTerrMinusElm(idata, oval_terr_minus);
}

void GraphDataTerr2d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}


GraphDataTerr2d* const GraphDataTerr2d::Clone() const
{
    GraphDataTerr2d* obj_new = new GraphDataTerr2d;
    obj_new->Copy(this);
    return obj_new;
}



void GraphDataTerr2d::Load(string file)
{
    NullGraphData2d();

    string* line_arr = NULL;
    long ndata = 0;
    MxcsIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
        if(6 != ncolumn){
            MxcsPrintErrClass("ncolumn != 6");
            abort();
        }
        istringstream iss(line_arr[idata]);
        double xval, xval_terr_plus, xval_terr_minus;
        double oval, oval_terr_plus, oval_terr_minus;
        iss >> xval >> xval_terr_plus >> xval_terr_minus
            >> oval >> oval_terr_plus >> oval_terr_minus;
        SetPoint(idata,
                 xval, xval_terr_plus, xval_terr_minus,
                 oval, oval_terr_plus, oval_terr_minus);
    }
    MxcsIolib::DelReadFile(line_arr);
    int flag_xval_sorted = 0;
    ReadInfo(file, &flag_xval_sorted);
    SetFlagXvalSorted(flag_xval_sorted);
}

void GraphDataTerr2d::Load(string file, string format)
{
    NullGraphData2d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MxcsIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, xval_terr_plus, xval_terr_minus;
    double oval, oval_terr_plus, oval_terr_minus;
    if("x,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(2 != ncolumn){
                MxcsPrintErrClass("ncolumn != 2");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> oval;
            xval_terr_plus  = 0.0;
            xval_terr_minus = 0.0;
            oval_terr_plus  = 0.0;
            oval_terr_minus = 0.0;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,y,ye" == format){
        double oval_serr;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(3 != ncolumn){
                MxcsPrintErrClass("ncolumn != 3");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> oval >> oval_serr;
            xval_terr_plus  = 0.0;
            xval_terr_minus = 0.0;
            oval_terr_plus = oval_serr;
            oval_terr_minus = -1 * oval_serr;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(4 != ncolumn){
                MxcsPrintErrClass("ncolumn != 4");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval
                >> oval >> oval_terr_plus >> oval_terr_minus;
            xval_terr_plus  = 0.0;
            xval_terr_minus = 0.0;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,xe,y" == format){
        double xval_serr;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(3 != ncolumn){
                MxcsPrintErrClass("ncolumn != 3");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_serr >> oval;
            xval_terr_plus  = xval_serr; 
            xval_terr_minus = -1 * xval_serr; 
            oval_terr_plus  = 0.0;
            oval_terr_minus = 0.0;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,xe,y,ye" == format){
        double xval_serr, oval_serr;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(4 != ncolumn){
                MxcsPrintErrClass("ncolumn != 4");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_serr >> oval >> oval_serr;
            xval_terr_plus = xval_serr;
            xval_terr_minus = -1 * xval_serr;
            oval_terr_plus = oval_serr;
            oval_terr_minus = -1 * oval_serr;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);            
        }
    } else if("x,xe,y,ye+,ye-" == format){
        double xval_serr;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(5 != ncolumn){
                MxcsPrintErrClass("ncolumn != 5");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_serr
                >> oval >> oval_terr_plus >> oval_terr_minus;
            xval_terr_plus = xval_serr;
            xval_terr_minus = -1 * xval_serr;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,xe+,xe-,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(4 != ncolumn){
                MxcsPrintErrClass("ncolumn != 4");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_terr_plus >> xval_terr_minus
                >> oval;
            oval_terr_plus  = 0.0;
            oval_terr_minus = 0.0;            
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,xe+,xe-,y,ye" == format){
        double oval_serr;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(5 != ncolumn){
                MxcsPrintErrClass("ncolumn != 5");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_terr_plus >> xval_terr_minus
                >> oval >> oval_serr;
            oval_terr_plus  = oval_serr;
            oval_terr_minus = -1 * oval_serr;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,xe+,xe-,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MxcsStr::GetNcolumn(line_arr[idata]);
            if(6 != ncolumn){
                MxcsPrintErrClass("ncolumn != 6");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_terr_plus >> xval_terr_minus
                >> oval >> oval_terr_plus >> oval_terr_minus;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
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


void GraphDataTerr2d::Sort()
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
    double* xval_org      = new double [ndata];
    double* xval_terr_plus_org = new double [ndata];
    double* xval_terr_minus_org = new double [ndata];
    double* oval_org      = new double [ndata];
    double* oval_terr_plus_org = new double [ndata];
    double* oval_terr_minus_org = new double [ndata];
    for(long idata = 0; idata < ndata; idata++){
        xval_org[idata]            = GetXvalElm(idata);
        xval_terr_plus_org[idata]  = GetXvalTerrPlusElm(idata);
        xval_terr_minus_org[idata] = GetXvalTerrMinusElm(idata);
        oval_org[idata]            = GetOvalElm(idata);    
        oval_terr_plus_org[idata]  = GetOvalTerrPlusElm(idata);
        oval_terr_minus_org[idata] = GetOvalTerrMinusElm(idata);
    }

    long* index = new long [ndata];  // to store sort result
    bool down = false;
    MxcsSort::Sort<double, long>(ndata, xval_org, index, down);

    for(long idata = 0; idata < ndata; idata++){
        SetPoint(idata,
                 xval_org[index[idata]],
                 xval_terr_plus_org[index[idata]],
                 xval_terr_minus_org[index[idata]],
                 oval_org[index[idata]],
                 oval_terr_plus_org[index[idata]],
                 oval_terr_minus_org[index[idata]] );
    }
    
    delete [] xval_org;
    delete [] xval_terr_plus_org;
    delete [] xval_terr_minus_org;
    delete [] oval_org;
    delete [] oval_terr_plus_org;
    delete [] oval_terr_minus_org;
    delete [] index;

    SetFlagXvalSorted(1);
}

const DataArrayTerr1d* const GraphDataTerr2d::GetXvalArr() const
{
    return dynamic_cast<const DataArrayTerr1d*>(GetXvalArrNonConst());
}
    
const DataArrayTerr1d* const GraphDataTerr2d::GetOvalArr() const
{
    return dynamic_cast<const DataArrayTerr1d*>(GetOvalArrNonConst());
}


double GraphDataTerr2d::GetXvalTerrPlusElm(long idata) const
{
    return GetXvalArr()->GetValTerrPlusElm(idata);
}

double GraphDataTerr2d::GetXvalTerrMinusElm(long idata) const
{
    return GetXvalArr()->GetValTerrMinusElm(idata);
}

double GraphDataTerr2d::GetOvalTerrPlusElm(long idata) const
{
    return GetOvalArr()->GetValTerrPlusElm(idata);
}

double GraphDataTerr2d::GetOvalTerrMinusElm(long idata) const
{
    return GetOvalArr()->GetValTerrMinusElm(idata);
}

void GraphDataTerr2d::PrintData(FILE* fp, string format,
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
                    (GetOvalTerrPlusElm(idata) - GetOvalTerrMinusElm(idata))/2.);
        }
    } else if ("x,xe,y,ye" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    (GetXvalTerrPlusElm(idata) - GetXvalTerrMinusElm(idata))/2.,
                    GetOvalElm(idata) - offset_oval,
                    (GetOvalTerrPlusElm(idata) - GetOvalTerrMinusElm(idata))/2.);
        }
    } else if ("x,xe,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    (GetXvalTerrPlusElm(idata) - GetXvalTerrMinusElm(idata))/2.,
                    GetOvalElm(idata) - offset_oval);
        }
    } else if ("x,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetOvalElm(idata) - offset_oval,
                    GetOvalTerrPlusElm(idata),
                    GetOvalTerrMinusElm(idata));
        }
    } else if ("x,xe,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    (GetXvalTerrPlusElm(idata) - GetXvalTerrMinusElm(idata))/2.,
                    GetOvalElm(idata) - offset_oval,
                    GetOvalTerrPlusElm(idata),
                    GetOvalTerrMinusElm(idata));
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetXvalTerrPlusElm(idata),
                    GetXvalTerrMinusElm(idata),
                    GetOvalElm(idata) - offset_oval,
                    GetOvalTerrPlusElm(idata),
                    GetOvalTerrMinusElm(idata));
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MxcsPrintErrClass(msg);
        abort();
    }
}

Interval* const GraphDataTerr2d::GenInterval() const
{
    vector<double> tstart_vec;
    vector<double> tstop_vec;
    for(long idata = 0; idata < GetNdata(); idata ++){
        tstart_vec.push_back(GetXvalElm(idata) + GetXvalTerrMinusElm(idata));
        tstop_vec.push_back(GetXvalElm(idata) + GetXvalTerrPlusElm(idata));
    }

    Interval* interval = new Interval;
    interval->Init(tstart_vec.size());
    interval->Set(tstart_vec, tstop_vec);
    double* term_half_width_arr = interval->GenTermHalfWidth();
    double term_half_width_min = MxcsMath::GetMin(interval->GetNterm(),
                                                  term_half_width_arr);

    double tdiff = term_half_width_min / 10.; 
    interval->Clean(tdiff);

    delete [] term_half_width_arr;
    return interval;
}

Interval* const GraphDataTerr2d::GenIntervalAboveThreshold(double threshold) const
{
    vector<double> tstart_vec;
    vector<double> tstop_vec;
    for(long idata = 0; idata < GetNdata(); idata ++){
        if(GetOvalElm(idata) > threshold){
            tstart_vec.push_back(GetXvalElm(idata) + GetXvalTerrMinusElm(idata));
            tstop_vec.push_back(GetXvalElm(idata) + GetXvalTerrPlusElm(idata));
        }
    }

    Interval* interval = new Interval;
    interval->Init(tstart_vec.size());
    interval->Set(tstart_vec, tstop_vec);
    double* term_half_width_arr = interval->GenTermHalfWidth();
    double term_half_width_min = MxcsMath::GetMin(interval->GetNterm(),
                                                  term_half_width_arr);

    double tdiff = term_half_width_min / 10.; 
    interval->Clean(tdiff);

    delete [] term_half_width_arr;
    return interval;

}

Interval* const GraphDataTerr2d::GenIntervalBelowThreshold(double threshold) const
{
    vector<double> tstart_vec;
    vector<double> tstop_vec;
    for(long idata = 0; idata < GetNdata(); idata ++){
        if(GetOvalElm(idata) < threshold){
            tstart_vec.push_back(GetXvalElm(idata) + GetXvalTerrMinusElm(idata));
            tstop_vec.push_back(GetXvalElm(idata) + GetXvalTerrPlusElm(idata));
        }
    }

    Interval* interval = new Interval;
    interval->Init(tstart_vec.size());
    interval->Set(tstart_vec, tstop_vec);
    double* term_half_width_arr = interval->GenTermHalfWidth();
    double term_half_width_min = MxcsMath::GetMin(interval->GetNterm(),
                                                  term_half_width_arr);

    double tdiff = term_half_width_min / 10.; 
    interval->Clean(tdiff);

    delete [] term_half_width_arr;
    return interval;
}
