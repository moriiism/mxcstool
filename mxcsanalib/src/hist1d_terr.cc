#include "mxcs_hist1d_terr.h"

//
// public
//

void HistDataTerr1d::Init(long nbin_xval,
                          double xval_lo,
                          double xval_up)
{
    NullHistData1d();
    NewHi1d();
    GetHi1dNonConst()->InitSetByNbin(xval_lo, xval_up, nbin_xval);
    NewOvalArrAsDataArrayTerr1d();
    GetOvalArrNonConst()->Init(nbin_xval);
}

void HistDataTerr1d::Init(const HistInfo1d* const hist_info)
{
    NullHistData1d();
    NewHi1d();
    GetHi1dNonConst()->InitSetByNbin(hist_info->GetLo(),
                                     hist_info->GetUp(),
                                     hist_info->GetNbin());
    NewOvalArrAsDataArrayTerr1d();
    GetOvalArrNonConst()->Init(hist_info->GetNbin());
}

void HistDataTerr1d::SetOvalTerrArr(long ndata, const double* const val_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerr(ndata, val_serr);
}

void HistDataTerr1d::SetOvalTerrArr(vector<double> val_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerr(val_serr);
}

void HistDataTerr1d::SetOvalTerrArr(long ndata,
                                    const double* const val_terr_plus,
                                    const double* const val_terr_minus)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerr(ndata, val_terr_plus, val_terr_minus);
}

void HistDataTerr1d::SetOvalTerrArr(vector<double> val_terr_plus,
                                    vector<double> val_terr_minus)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerr(val_terr_plus, val_terr_minus);
}

void HistDataTerr1d::SetOvalTerrElm(long ibin,
                                    double oval_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerrElm(ibin, oval_serr);
}


void HistDataTerr1d::SetOvalTerrPlusElm(long ibin,
                                        double oval_terr_plus)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerrPlusElm(ibin, oval_terr_plus);
}

void HistDataTerr1d::SetOvalTerrMinusElm(long ibin,
                                         double oval_terr_minus)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerrMinusElm(ibin, oval_terr_minus);
}


void HistDataTerr1d::FillByLarger(double xval,
                                  double oval,
                                  double oval_terr_plus,
                                  double oval_terr_minus)
{
    IsOvalArrNotNull();
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->FillByLarger(ibin,
                                       oval,
                                       oval_terr_plus,
                                       oval_terr_minus);
}

void HistDataTerr1d::FillBySmaller(double xval,
                                   double oval,
                                   double oval_terr_plus,
                                   double oval_terr_minus)
{
    IsOvalArrNotNull();
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->FillBySmaller(ibin,
                                        oval,
                                        oval_terr_plus,
                                        oval_terr_minus);
}

void HistDataTerr1d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}


HistDataTerr1d* const HistDataTerr1d::Clone() const
{
    HistDataTerr1d* obj_new = new HistDataTerr1d;
    obj_new->Copy(this);
    return obj_new;
}

void HistDataTerr1d::Load(string file)
{
    NullHistData1d();
    
    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    string format = "";
    ReadInfo(file, &nbin_xval, &xval_lo, &xval_up, &format);
    Init(nbin_xval, xval_lo, xval_up);

    if("x,y,ye+,ye-" != format){
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MxcsPrintErrClass(msg);
        abort();
    }
    string* line_arr = NULL;
    long nline = 0;
    MxcsIolib::GenReadFileSkipComment(file, &line_arr, &nline);
    if(nline != nbin_xval){
        char msg[kLineSize];
        sprintf(msg, "nline != nbin_xval");
        MxcsPrintErrClass(msg);
        abort();
    }
    double xval = 0.0;
    double oval = 0.0;
    double oval_terr_plus = 0.0;
    double oval_terr_minus = 0.0; 
    for(long iline = 0; iline < nline; iline ++){
        int ncolumn = MxcsStr::GetNcolumn(line_arr[iline]);
        if(4 != ncolumn){
            MxcsPrintErrClass("ncolumn != 4");
            abort();
        }
        istringstream iss(line_arr[iline]);
        iss >> xval >> oval >> oval_terr_plus >> oval_terr_minus;
        long ibin = GetIbin(xval);
        SetOvalElm(ibin, oval);
        SetOvalTerrPlusElm(ibin, oval_terr_plus);
        SetOvalTerrMinusElm(ibin, oval_terr_minus);
    }
    MxcsIolib::DelReadFile(line_arr);
}

const DataArrayTerr1d* const HistDataTerr1d::GetOvalArr() const
{
    return dynamic_cast<const DataArrayTerr1d*>(GetOvalArrNonConst());
}

double HistDataTerr1d::GetOvalSerrElm(long ibin) const
{
    IsOvalArrNotNull();    
    return GetOvalArr()->GetValSerrElm(ibin);
}


double HistDataTerr1d::GetOvalTerrPlusElm(long ibin) const
{
    IsOvalArrNotNull();    
    return GetOvalArr()->GetValTerrPlusElm(ibin);
}

double HistDataTerr1d::GetOvalTerrMinusElm(long ibin) const
{
    IsOvalArrNotNull();
    return GetOvalArr()->GetValTerrMinusElm(ibin);
}

double HistDataTerr1d::GetOvalSerrElmAtX(double xval) const
{
    long ibin = GetIbin(xval);
    return GetOvalSerrElm(ibin);
}



double HistDataTerr1d::GetOvalTerrPlusElmAtX(double xval) const
{
    long ibin = GetIbin(xval);
    return GetOvalTerrPlusElm(ibin);
}

double HistDataTerr1d::GetOvalTerrMinusElmAtX(double xval) const
{
    long ibin = GetIbin(xval);
    return GetOvalTerrMinusElm(ibin);
}

void HistDataTerr1d::PrintData(FILE* fp, string format,
                               double offset_xval,
                               double offset_oval) const
{
    long nbin_xval = GetNbinX();
    if("x,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            if(1 == MxcsMath::IsSame(GetOvalTerrPlusElm(ibin),
                                     -1 * GetOvalTerrMinusElm(ibin)) ){
                fprintf(fp, "%.15e  %.15e  %.15e\n",
                        GetBinCenter(ibin) - offset_xval,
                        GetOvalElm(ibin) - offset_oval,
                        GetOvalTerrPlusElm(ibin) );
            } else {
                abort();
            }
        }
    } else if ("x,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalTerrPlusElm(ibin),
                    GetOvalTerrMinusElm(ibin) );
        }
    } else if ("x,xe,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,xe,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            if(1 == MxcsMath::IsSame(GetOvalTerrPlusElm(ibin),
                                     -1 * GetOvalTerrMinusElm(ibin)) ){
                fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                        GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                        GetOvalElm(ibin) - offset_oval,
                        GetOvalTerrPlusElm(ibin) );
            } else {
                abort();
            }
        }
    } else if ("x,xe,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalTerrPlusElm(ibin),
                    GetOvalTerrMinusElm(ibin) );
        }
    } else if ("x,xe+,xe-,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,xe+,xe-,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            if(1 == MxcsMath::IsSame(GetOvalTerrPlusElm(ibin),
                                     -1 * GetOvalTerrMinusElm(ibin)) ){
                fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                        GetBinCenter(ibin) - offset_xval,
                        GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
                        GetOvalElm(ibin) - offset_oval,
                        GetOvalTerrPlusElm(ibin) );
            } else {
                abort();
            }
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalTerrPlusElm(ibin),
                    GetOvalTerrMinusElm(ibin) );
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MxcsPrintErrClass(msg);
        abort();
    }
}

HistDataTerr1d* const HistDataTerr1d::GenHd1MaxInBin(long nbin_new) const
{
    if(nbin_new > GetNbinX()){
        MxcsPrintErrClass("bad nbin_new");
        abort();
    }
    if(nbin_new < 1){
        MxcsPrintErrClass("bad nbin_new");
        abort();
    }
    if(0 != GetNbinX() % nbin_new){
        MxcsPrintErrClass("bad nbin_new");
        abort();
    }

    HistDataTerr1d* h1d_new = new HistDataTerr1d;
    h1d_new->Init(nbin_new, GetXvalLo(), GetXvalUp());
  
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        h1d_new->FillByLarger(GetBinCenter(ibin),
                              GetOvalElm(ibin),
                              GetOvalTerrPlusElm(ibin),
                              GetOvalTerrMinusElm(ibin));
    }
    return h1d_new;
}


HistDataTerr1d* HistDataTerr1d::GenSubHist(long ibinx_st, long ibinx_ed) const
{
    HistDataTerr1d* hd1d_sub = new HistDataTerr1d;
    long nbinx_sub = ibinx_ed - ibinx_st + 1;
    hd1d_sub->Init(nbinx_sub, GetBinLo(ibinx_st), GetBinUp(ibinx_ed));
    for(long ibinx = 0; ibinx < nbinx_sub; ibinx ++){
        hd1d_sub->SetOvalElm(ibinx, GetOvalElm(ibinx_st + ibinx));
        hd1d_sub->SetOvalTerrPlusElm(ibinx,
                                     GetOvalTerrPlusElm(ibinx_st + ibinx));
        hd1d_sub->SetOvalTerrMinusElm(ibinx,
                                      GetOvalTerrMinusElm(ibinx_st + ibinx));
    }
    return hd1d_sub;
}

