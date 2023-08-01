#ifndef MXCSTOOL_MXCSANALIB_FUNC_H_
#define MXCSTOOL_MXCSANALIB_FUNC_H_

#include "mxcs_base.h"

class MxcsFunc : public MxcsObject{
public:
    MxcsFunc(string class_name, string title) :
        MxcsObject(class_name, title),
        npar_(0), ndim_(0) {}
    virtual ~MxcsFunc(){}
    void SetNpar(int npar) {npar_ = npar;};
    void SetNdim(int ndim) {ndim_ = ndim;};
   
    //
    // const functions
    //
    
    int GetNpar() const {return npar_;};
    int GetNdim() const {return ndim_;};

    virtual double Eval(const double* const xval,
                        const double* const par) const = 0;
    double operator()(const double* const xval,
                      const double* const par) const
        {return Eval(xval, par);};
    
    double Eval1d(double xval,
                  const double* const par) const;
    double Eval2d(double xval, double yval,
                  const double* const par) const;

protected:
    void NullMxcsFunc();
    void CopyMxcsFunc(const MxcsFunc* const org);
private:
    int npar_;
    int ndim_;
};

#endif // MXCSTOOL_MXCSANALIB_FUNC_H_
