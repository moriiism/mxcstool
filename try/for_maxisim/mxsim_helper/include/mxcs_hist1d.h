#ifndef MXCSTOOL_MXCSANALIB_HIST1D_H_
#define MXCSTOOL_MXCSANALIB_HIST1D_H_

#include "mxcs_rand.h"
#include "mxcs_data1d_nerr.h"
#include "mxcs_data1d_serr.h"
#include "mxcs_hist_info.h"
#include "mxcs_func.h"

class HistDataNerr1d;
class HistDataSerr1d;

class HistData1d : public MxcsObject{
public:
    HistData1d(string class_name, string title) :
        MxcsObject(class_name, title),
        hi1d_(NULL),
        oval_arr_(NULL) {}
    virtual ~HistData1d() {}
   
    virtual void Init(long nbin_xval,
                      double xval_lo,
                      double xval_up) = 0;
    virtual void Init(const HistInfo1d* const hist_info) = 0;
    void SetOvalArr(const DataArray1d* const oval_arr);
    void SetOvalArr(long ndata, const double* const val);
    void SetOvalArr(vector<double> val);    
    virtual void SetOvalSerrArr(long ndata, const double* const val_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetOvalSerrArr(vector<double> val_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetOvalTerrArr(long ndata, const double* const val_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetOvalTerrArr(vector<double> val_serr)
        {MxcsPrintErrVFunc; abort();};    
    virtual void SetOvalTerrArr(long ndata,
                                const double* const val_terr_plus,
                                const double* const val_terr_minus)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetOvalTerrArr(vector<double> val_terr_plus,
                                vector<double> val_terr_minus)
        {MxcsPrintErrVFunc; abort();};    
    
    void SetOvalElm(long ibin, double oval);
    virtual void SetOvalSerrElm(long ibin, double oval_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetOvalTerrElm(long ibin, double oval_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetOvalTerrPlusElm(long ibin, double oval_terr_plus)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetOvalTerrMinusElm(long ibin, double oval_terr_minus)
        {MxcsPrintErrVFunc; abort();};
    
    void Fill(double xval);
    void Fill(double xval, double weight);
    void FillByLarger(double xval, double oval);
    virtual void FillByLarger(double xval,
                              double oval,
                              double oval_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void FillByLarger(double xval,
                              double oval,
                              double oval_terr_plus,
                              double oval_terr_minus)
        {MxcsPrintErrVFunc; abort();};
    
    void FillBySmaller(double xval, double oval);
    virtual void FillBySmaller(double xval,
                               double oval,
                               double oval_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void FillBySmaller(double xval,
                               double oval,
                               double oval_terr_plus,
                               double oval_terr_minus)
        {MxcsPrintErrVFunc; abort();};
    
    void SetConst(double constant);

    virtual void SetOvalErrArrByPoissonErr()
        {MxcsPrintErrVFunc; abort();};
    
    void SetByFunc(const MxcsFunc* const func, const double* const par);

    void Copy(const HistData1d* const org);
    virtual void Load(string file) = 0;

    //
    // const functions
    //

    // get
    const HistInfo1d* const GetHi1d() const {return hi1d_;};
    virtual const DataArray1d* const GetOvalArr() const = 0;
    
    long GetNbinX() const {return GetHi1d()->GetNbin();};
    double GetXvalLo() const {return GetHi1d()->GetLo();};
    double GetXvalUp() const {return GetHi1d()->GetUp();};
    double GetXvalMd() const {return GetHi1d()->GetMd();};
    double GetXvalFullWidth() const {return GetHi1d()->GetFullWidth();};
    double GetXvalBinWidth() const {return GetHi1d()->GetBinWidth();};

    // get element
    double GetOvalElm(long ibin) const;
    double GetOvalElmAtX(double xval) const;
    virtual double GetOvalSerrElm(long ibin) const
        {MxcsPrintErrVFunc; abort();};
    virtual double GetOvalSerrElmAtX(double xval) const
        {MxcsPrintErrVFunc; abort();};
    virtual double GetOvalTerrPlusElm(long ibin) const
        {MxcsPrintErrVFunc; abort();};
    virtual double GetOvalTerrMinusElm(long ibin) const
        {MxcsPrintErrVFunc; abort();};
    virtual double GetOvalTerrPlusElmAtX(double xval) const
        {MxcsPrintErrVFunc; abort();};
    virtual double GetOvalTerrMinusElmAtX(double xval) const
        {MxcsPrintErrVFunc; abort();};
    
    double GetXvalAtOvalMin() const;
    double GetXvalAtOvalMax() const;

    void GenXvalArr(double** const xval_arr_ptr,
                    long* const nbin_ptr) const;
    void GenXvalSerrArr(double** const xval_serr_arr_ptr,
                        long* const nbin_ptr) const;
    void GenOvalArr(double** const oval_arr_ptr,
                    long* const nbin_ptr) const;
    virtual void GenOvalSerrArr(double** const oval_serr_arr_ptr,
                                long* const nbin_ptr) const
        {MxcsPrintErrVFunc; abort();};
    virtual void GenOvalTerrArr(double** const oval_terr_plus_arr_ptr,
                                double** const oval_terr_minus_arr_ptr,
                                long* const nbin_ptr) const
        {MxcsPrintErrVFunc; abort();};

    long GetIbin(double xval) const;
    double GetBinCenter(long ibin) const;
    double GetBinLo(long ibin) const;
    double GetBinUp(long ibin) const;
    long GetIbin_WithHalfBinShifted(double val) const;
    double GetOvalIntPolLin(double xval) const;
    double GetIntegral(double xval_lo, double xval_up) const;

    
    //
    // output
    //
    void Save(string outfile, string format,
              double offset_xval = 0.0,
              double offset_oval = 0.0) const;
    void SaveData(string outfile, string format,
                  double offset_xval = 0.0,
                  double offset_oval = 0.0) const;
    void PrintInfo(FILE* fp) const;
    virtual void PrintData(FILE* fp, string format,
                           double offset_xval,
                           double offset_oval) const = 0;
    void SaveRoot(string outfile,
                  double offset_xval = 0.0,
                  double offset_oval = 0.0) const;

    virtual HistData1d* const GenHd1MaxInBin(long nbin_new) const = 0;

    // poisson error
    virtual void FillRandom(const MxcsFunc* const func,
                            const double* const func_par,
                            int rand_seed)
        {MxcsPrintErrVFunc; abort();};

    // gaussian error
    virtual void FillRandom(const MxcsFunc* const func,
                            const double* const func_par,
                            const MxcsFunc* const func_sigma,
                            const double* const func_par_sigma,
                            int rand_seed)
        {MxcsPrintErrVFunc; abort();};    

    // poisson error
    virtual void FillRandom(const HistData1d* const hist_data,
                            int rand_seed)
        {MxcsPrintErrVFunc; abort();};
    

    // generate events from histogram with poisson statistic
    DataArrayNerr1d* const GenRandomEvt(int rand_seed) const;

    // generate events from a probability distribution
    void GenRandomEvtFromProbDist(int nevt,
                                  int rand_seed,
                                  double** xval_arr_ptr) const;
    
    virtual HistData1d* GenSubHist(long ibinx_st, long ibinx_ed) const = 0;

    // offset_tag = "st", "md", "ed", "no"
    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetOFromTag(string offset_tag) const;

    //
    // static 
    //
    static void ReadInfo(string file, 
                         long* nbin_xval_ptr,
                         double* xval_lo_ptr,
                         double* xval_up_ptr,
                         string* format_ptr);

protected:
    void NullHistData1d();
    void NewOvalArrAsDataArrayNerr1d();
    void NewOvalArrAsDataArraySerr1d();
    void NewHi1d();
    HistInfo1d* GetHi1dNonConst() const {return hi1d_;};
    DataArray1d* GetOvalArrNonConst() const {return oval_arr_;};
    void IsHi1dNotNull() const;
    void IsOvalArrNotNull() const;
    void IsValidIbin(long ibin) const;
    void IsValidRange(double val) const;
    
private:
    HistInfo1d* hi1d_;
    DataArray1d* oval_arr_;
};

#endif // MXCSTOOL_MXCSANALIB_HIST1D_H_
