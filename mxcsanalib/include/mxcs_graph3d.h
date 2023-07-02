#ifndef MXCSTOOL_MXCSANALIB_GRAPH3D_H_
#define MXCSTOOL_MXCSANALIB_GRAPH3D_H_

#include "mxcs_interval.h"
#include "mxcs_data1d_nerr.h"
#include "mxcs_data1d_serr.h"
#include "mxcs_data1d_terr.h"
#include "mxcs_func.h"
#include "mxcs_hist_info.h"

class GraphDataNerr3d;
class GraphDataSerr3d;
class GraphDataTerr3d;

class GraphData3d : public MxcsObject{
public:
    GraphData3d(string class_name, string title) :
        MxcsObject(class_name, title),
        xval_arr_(NULL),
        yval_arr_(NULL),
        oval_arr_(NULL) {}
    virtual ~GraphData3d() {}

    // Init
    virtual void Init(long ndata) = 0;
    void SetXvalArr(const DataArray1d* const val_arr);
    void SetYvalArr(const DataArray1d* const val_arr);
    void SetOvalArr(const DataArray1d* const val_arr);

    void SetXvalArr(long ndata, const double* const val);
    void SetXvalArr(vector<double> val);
    void SetYvalArr(long ndata, const double* const val);
    void SetYvalArr(vector<double> val);
    void SetOvalArr(long ndata, const double* const val);
    void SetOvalArr(vector<double> val);

    virtual void SetXvalSerrArr(long ndata, const double* const val_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetXvalSerrArr(vector<double> val_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetYvalSerrArr(long ndata, const double* const val_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetYvalSerrArr(vector<double> val_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetOvalSerrArr(long ndata, const double* const val_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetOvalSerrArr(vector<double> val_serr)
        {MxcsPrintErrVFunc; abort();};

    virtual void SetXvalTerrArr(long ndata, const double* const val_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetXvalTerrArr(vector<double> val_serr)
        {MxcsPrintErrVFunc; abort();};    
    virtual void SetXvalTerrArr(long ndata,
                                const double* const val_terr_plus,
                                const double* const val_terr_minus)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetXvalTerrArr(vector<double> val_terr_plus,
                                vector<double> val_terr_minus)
        {MxcsPrintErrVFunc; abort();};    
    virtual void SetYvalTerrArr(long ndata, const double* const val_serr)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetYvalTerrArr(vector<double> val_serr)
        {MxcsPrintErrVFunc; abort();};    
    virtual void SetYvalTerrArr(long ndata,
                                const double* const val_terr_plus,
                                const double* const val_terr_minus)
        {MxcsPrintErrVFunc; abort();};
    virtual void SetYvalTerrArr(vector<double> val_terr_plus,
                                vector<double> val_terr_minus)
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

    void SetPoint(long idata, double xval, double yval, double oval);
    virtual void SetPoint(long idata,
                          double xval, double xval_serr,
                          double yval, double yval_serr,
                          double oval, double oval_serr)
        {MxcsPrintErrVFunc; abort();};    
    virtual void SetPoint(long idata,
                          double xval,
                          double xval_terr_plus,
                          double xval_terr_minus,
                          double yval,
                          double yval_terr_plus,
                          double yval_terr_minus,
                          double oval,
                          double oval_terr_plus,
                          double oval_terr_minus)
        {MxcsPrintErrVFunc; abort();};

    virtual void SetOvalErrArrByPoissonErr()
        {MxcsPrintErrVFunc; abort();};

    // Init & Set by Func
    void InitSetByFunc(const MxcsFunc* const func, const double* const par,
                       long nbin_xval, double xval_lo, double xval_up,
                       long nbin_yval, double yval_lo, double yval_up,
                       string scale_xval, string scale_yval);
    
    void Copy(const GraphData3d* const org);
    
    virtual void Load(string file) = 0;
    virtual void Load(string file, string format) = 0;

    //
    // const functions
    //
    
    // get
    virtual const DataArray1d* const GetXvalArr() const = 0;
    virtual const DataArray1d* const GetYvalArr() const = 0;
    virtual const DataArray1d* const GetOvalArr() const = 0;

    long GetNdata() const;
    double GetXvalElm(long idata) const
        {return GetXvalArr()->GetValElm(idata);};
    virtual double GetXvalSerrElm(long idata) const
        {MxcsPrintErrVFunc; abort();};
    virtual double GetXvalTerrPlusElm(long idata) const
        {MxcsPrintErrVFunc; abort();};
    virtual double GetXvalTerrMinusElm(long idata) const
        {MxcsPrintErrVFunc; abort();};
    double GetYvalElm(long idata) const
        {return GetYvalArr()->GetValElm(idata);};
    virtual double GetYvalSerrElm(long idata) const
        {MxcsPrintErrVFunc; abort();};
    virtual double GetYvalTerrPlusElm(long idata) const
        {MxcsPrintErrVFunc; abort();};
    virtual double GetYvalTerrMinusElm(long idata) const
        {MxcsPrintErrVFunc; abort();};
    double GetOvalElm(long idata) const
        {return GetOvalArr()->GetValElm(idata);};
    virtual double GetOvalSerrElm(long idata) const
        {MxcsPrintErrVFunc; abort();};
    virtual double GetOvalTerrPlusElm(long idata) const
        {MxcsPrintErrVFunc; abort();};
    virtual double GetOvalTerrMinusElm(long idata) const
        {MxcsPrintErrVFunc; abort();};
    
    // stat
    double GetYvalAtXvalMin() const;
    double GetYvalAtXvalMax() const;
    double GetOvalAtXvalMin() const;
    double GetOvalAtXvalMax() const;
    
    double GetXvalAtYvalMin() const;
    double GetXvalAtYvalMax() const;
    double GetOvalAtYvalMin() const;
    double GetOvalAtYvalMax() const;

    double GetXvalAtOvalMin() const;
    double GetXvalAtOvalMax() const;
    double GetYvalAtOvalMin() const;
    double GetYvalAtOvalMax() const;
  

    // output
    void Save(string outfile, string format,
              double offset_xval = 0.0,
              double offset_yval = 0.0,
              double offset_oval = 0.0) const;
    void SaveData(string outfile, string format,
                  double offset_xval = 0.0,
                  double offset_yval = 0.0,
                  double offset_oval = 0.0) const;
    void PrintInfo(FILE* fp) const;
    virtual void PrintData(FILE* fp, string format,
                           double offset_xval,
                           double offset_yval,
                           double offset_oval) const = 0;

    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetYFromTag(string offset_tag) const;
    double GetOffsetOFromTag(string offset_tag) const;

protected:
    void NullGraphData3d();
    void NewXvalArrAsDataArrayNerr1d();
    void NewXvalArrAsDataArraySerr1d();
    void NewXvalArrAsDataArrayTerr1d();
    DataArray1d* GetXvalArrNonConst() const {return xval_arr_;};
    void NewYvalArrAsDataArrayNerr1d();
    void NewYvalArrAsDataArraySerr1d();
    void NewYvalArrAsDataArrayTerr1d();
    DataArray1d* GetYvalArrNonConst() const {return yval_arr_;};
    void NewOvalArrAsDataArrayNerr1d();
    void NewOvalArrAsDataArraySerr1d();
    void NewOvalArrAsDataArrayTerr1d();
    DataArray1d* GetOvalArrNonConst() const {return oval_arr_;};

private:    
    DataArray1d* xval_arr_;
    DataArray1d* yval_arr_;
    DataArray1d* oval_arr_;
};

#endif // MXCSTOOL_MXCSANALIB_GRAPH3D_H_
