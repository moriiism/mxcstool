#ifndef MXCSTOOL_MXCSANALIB_HIST1D_TERR_H_
#define MXCSTOOL_MXCSANALIB_HIST1D_TERR_H_

#include "mxcs_hist1d.h"


class HistDataTerr1d : public HistData1d{
public:
    HistDataTerr1d(string title = "") :
        HistData1d("HistDataTerr1d", title) {}
    ~HistDataTerr1d() {
        NullHistData1d();
    }

    void Init(long nbin_xval,
              double xval_lo,
              double xval_up);
    void Init(const HistInfo1d* const hist_info);
    void SetOvalTerrArr(long ndata, const double* const val_serr);
    void SetOvalTerrArr(vector<double> val_serr);
    void SetOvalTerrArr(long ndata,
                        const double* const val_terr_plus,
                        const double* const val_terr_minus);
    void SetOvalTerrArr(vector<double> val_terr_plus,
                        vector<double> val_terr_minus);
    
    void SetOvalTerrElm(long ibin, double oval_serr);
    void SetOvalTerrPlusElm(long ibin, double oval_terr_plus);
    void SetOvalTerrMinusElm(long ibin, double oval_terr_minus);
    void FillByLarger(double xval,
                      double oval,
                      double oval_terr_plus,
                      double oval_terr_minus);
    void FillBySmaller(double xval,
                       double oval,
                       double oval_terr_plus,
                       double oval_terr_minus);
    void SetOvalErrArrByPoissonErr();
    HistDataTerr1d* const Clone() const;
    void Load(string file);

    const DataArrayTerr1d* const GetOvalArr() const;
    double GetOvalSerrElm(long ibin) const;
    double GetOvalTerrPlusElm(long ibin) const;
    double GetOvalTerrMinusElm(long ibin) const;
    double GetOvalSerrElmAtX(double xval) const;
    double GetOvalTerrPlusElmAtX(double xval) const;    
    double GetOvalTerrMinusElmAtX(double xval) const;

    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_oval) const;

    HistDataTerr1d* const GenHd1MaxInBin(long nbin_new) const;
    HistDataTerr1d* GenSubHist(long ibinx_st, long ibinx_ed) const;
};

#endif // MXCSTOOL_MXCSANALIB_HIST1D_TERR_H_

