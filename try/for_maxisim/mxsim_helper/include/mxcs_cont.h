#ifndef MXCSTOOL_MXCSANALIB_CONT_H_
#define MXCSTOOL_MXCSANALIB_CONT_H_

#include "mxcs_graph2d_nerr.h"

//
// to hold contour
//

class MxcsCont : public MxcsObject{
public:
    explicit MxcsCont(string title = "") :
        MxcsObject("MxcsCont", title),
        ngraph_(0),
        gd2d_arr_(NULL) {}
    ~MxcsCont() {
        Null();
    }
    void Init(int ngraph);
    void SetGd2dArr(int ngraph,
                    const GraphDataNerr2d* const* const gd2d_arr);
    void AddPolygon(int npoint,
                    const double* const xval_arr,
                    const double* const yval_arr);

    void Copy(const MxcsCont* const org);
    MxcsCont* const Clone() const;
    
    int GetNgraph() const {return ngraph_;};
    const GraphDataNerr2d* const* const GetGd2dArr() const {return gd2d_arr_;};
    const GraphDataNerr2d* const GetGd2dArrElm(int igraph) const
        {return gd2d_arr_[igraph];};

    string GetPolygonStr(int igraph) const;
    MxcsCont* const GenShift(double delta_xval, double delta_yval) const;

private:
    // fill in counter-clockwise
    // each graph is closed polygon.
    int ngraph_;
    GraphDataNerr2d** gd2d_arr_;

    void Null();
};


class MxcsContWithBest : public MxcsObject{
public:
    explicit MxcsContWithBest(string title = "") :
        MxcsObject("MxcsContWithBest", title),
        xval_best_(0.0),
        yval_best_(0.0),
        cont_(NULL) {}
    ~MxcsContWithBest() {
        Null();
    }
    void Init();
    void SetBest(double xval_best, double yval_best);
    void SetCont(const MxcsCont* const cont);

    void Copy(const MxcsContWithBest* const org);
    MxcsContWithBest* const Clone() const;
    
    double GetXvalBest() const {return xval_best_;};
    double GetYvalBest() const {return yval_best_;};
    const MxcsCont* const GetCont() const {return cont_;};

    MxcsContWithBest* const GenShift(double delta_xval, double delta_yval) const;
    
private:
    double xval_best_;
    double yval_best_;
    MxcsCont* cont_;
    void Null();
};

#endif // MXCSTOOL_MXCSANALIB_CONT_H_
