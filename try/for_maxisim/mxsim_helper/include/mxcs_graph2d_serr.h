#ifndef MXCSTOOL_MXCSANALIB_GRAPH2D_SERR_H_
#define MXCSTOOL_MXCSANALIB_GRAPH2D_SERR_H_

#include "mxcs_graph2d.h"

class GraphDataSerr2d : public GraphData2d{
public:
    explicit GraphDataSerr2d(string title = "") :
        GraphData2d("GraphDataSerr2d", title) {}
    ~GraphDataSerr2d() {
        NullGraphData2d();
    }
    
    void Init(long ndata);
    void SetXvalSerrArr(long ndata, const double* const val_serr);
    void SetXvalSerrArr(vector<double> val_serr);
    void SetOvalSerrArr(long ndata, const double* const val_serr);
    void SetOvalSerrArr(vector<double> val_serr);
    
    using GraphData2d::SetPoint;
    void SetPoint(long idata,
                  double xval, double xval_serr,
                  double oval, double oval_serr);
    void SetOvalErrArrByPoissonErr();
    GraphDataSerr2d* const Clone() const;
    void Load(string file);
    void Load(string file, string format);
    void Sort();

    const DataArraySerr1d* const GetXvalArr() const;
    const DataArraySerr1d* const GetOvalArr() const;
    double GetXvalSerrElm(long idata) const;
    double GetOvalSerrElm(long idata) const;  
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_oval) const;
    Interval* const GenInterval() const;
    Interval* const GenIntervalAboveThreshold(double threshold) const;
    Interval* const GenIntervalBelowThreshold(double threshold) const;
};

#endif // MXCSTOOL_MXCSANALIB_GRAPH2D_SERR_H_
