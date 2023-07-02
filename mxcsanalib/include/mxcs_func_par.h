#ifndef MXCSTOOL_MXCSANALIB_FUNC_PAR_H_
#define MXCSTOOL_MXCSANALIB_FUNC_PAR_H_

#include "mxcs_iolib.h"

class MxcsFuncPar : public MxcsObject{
public:
    explicit MxcsFuncPar(string title = "") :
        MxcsObject("MxcsFuncPar", title),
        npar_(0),
        par_name_(NULL),
        par_(NULL) {}
    ~MxcsFuncPar() {
        Null();
    }
    void Init(int npar);
    void Set(int npar,
             const string* const par_name,
             const double* const par);
    void SetElm(int ipar,
                string par_name,
                double par);
    void InitSet(int npar,
                 const string* const par_name,
                 const double* const par);
    
    void Load(string file);

    void Copy(const MxcsFuncPar* const org);
    MxcsFuncPar* const Clone() const;

    void Print(FILE* fp) const;

    int GetNpar() const {return npar_;};
    const string* const GetParName() const {return par_name_;};
    const double* const GetPar() const     {return par_;};
    string GetParNameElm(int ipar) const {return par_name_[ipar];};
    double GetParElm(int ipar) const     {return par_[ipar];};
    
private:
    int npar_;
    string* par_name_;
    double* par_;

    void Null();
};

#endif // MXCSTOOL_MXCSANALIB_FUNC_PAR_H_
