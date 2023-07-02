#ifndef MXCSTOOL_MXCSANALIB_GRAPH3D_SERR_H_
#define MXCSTOOL_MXCSANALIB_GRAPH3D_SERR_H_

#include "mxcs_graph3d.h"

class GraphDataSerr3d : public GraphData3d{
public:
    explicit GraphDataSerr3d(string title = "") :
        GraphData3d("GraphDataSerr3d", title) {}
    ~GraphDataSerr3d() {
        NullGraphData3d();
    }

    void Init(long ndata);
    void SetXvalSerrArr(long ndata, const double* const val_serr);
    void SetXvalSerrArr(vector<double> val_serr);
    void SetYvalSerrArr(long ndata, const double* const val_serr);
    void SetYvalSerrArr(vector<double> val_serr);
    void SetOvalSerrArr(long ndata, const double* const val_serr);
    void SetOvalSerrArr(vector<double> val_serr);
    
    using GraphData3d::SetPoint;
    void SetPoint(long idata,
                  double xval, double xval_serr,
                  double yval, double yval_serr,
                  double oval, double oval_serr);
    void SetOvalErrArrByPoissonErr();
    GraphDataSerr3d* const Clone() const;
    void Load(string file);
    void Load(string file, string format);

    const DataArraySerr1d* const GetXvalArr() const;
    const DataArraySerr1d* const GetYvalArr() const;
    const DataArraySerr1d* const GetOvalArr() const;
    double GetXvalSerrElm(long idata) const;
    double GetYvalSerrElm(long idata) const;
    double GetOvalSerrElm(long idata) const;
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_yval,
                   double offset_oval) const;
};

#endif // MXCSTOOL_MXCSANALIB_GRAPH3D_SERR_H_
