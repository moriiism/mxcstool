#ifndef MXCSTOOL_MXCSLIB_BASE_H_
#define MXCSTOOL_MXCSLIB_BASE_H_

#include "mxcs_par.h"

#define MxcsPrintErr(msg)       (printf("ERROR: %s: %u: %s(): %s\n", \
                             __FILE__, __LINE__, __func__, msg))
#define MxcsPrintWarn(msg)      (printf("WARNING: %s: %u: %s(): %s\n", \
                             __FILE__, __LINE__, __func__, msg))
#define MxcsPrintInfo(msg)      (printf("INFO: %s: %u: %s(): %s\n", \
                             __FILE__, __LINE__, __func__, msg))
#define MxcsPrintErrClass(msg)  (printf("ERROR: %s: %u: %s::%s():%s: %s\n", \
                             __FILE__, __LINE__, GetClassName().c_str(), \
                             __func__, GetTitle().c_str(), msg))
#define MxcsPrintWarnClass(msg) (printf("WARNING: %s: %u: %s::%s():%s: %s\n", \
                             __FILE__, __LINE__, GetClassName().c_str(), \
                             __func__, GetTitle().c_str(), msg))
#define MxcsPrintInfoClass(msg) (printf("INFO: %s: %u: %s::%s():%s: %s\n", \
                             __FILE__, __LINE__, GetClassName().c_str(), \
                             __func__, GetTitle().c_str(), msg))
#define MxcsPrintErrVFunc       (MxcsPrintErr("Wrong virtual function call."))

#include <string.h>
#include <typeinfo>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

using std::vector;
using std::map;
using std::multimap;
using std::make_pair;
using std::pair;
using std::type_info;
using std::istringstream;
using std::stringstream;

#include <getopt.h>

// see effective C++ section 6
class Uncopyable{
protected:
    Uncopyable(){}
    ~Uncopyable(){}
private:
    Uncopyable(const Uncopyable &);
    Uncopyable& operator=(const Uncopyable &);
};

class MxcsObject: private Uncopyable{
public:
    MxcsObject(string class_name, string title) :
        class_name_(class_name),
        title_(title) {}
    virtual ~MxcsObject() {
        NullMxcsObject();
    }

    virtual MxcsObject* const Clone() const = 0;
    
    string GetClassName() const {return class_name_;};
    string GetTitle() const {return title_;};

    void SetTitle(string title) {title_ = title;};
    // There is no SetClassName function, because
    // class_name_ should be set at the initialization.

protected:
    void CopyTitle(const MxcsObject* const org);
    
private:
    string class_name_;  
    string title_;

    void NullMxcsObject();
};

class MxcsArgBase: private Uncopyable{
public:
    MxcsArgBase() {}
    virtual ~MxcsArgBase() {}
    
    virtual void Init(int argc, char* argv[]) = 0;
    virtual void Print(FILE* fp) const = 0;

private:
    virtual void Null() = 0;
    virtual void SetOption(int argc, char* argv[],
			   option* long_options) = 0;
    virtual void Usage(FILE* fp) const = 0;
};

namespace MxcsBase
{
    void IsValidArray(long narr, const int* const val_arr);    
    void IsValidArray(long narr, const double* const val_arr);

    // vector --> arrray
    void GenArray(vector<double> vec,
                  long* narr_ptr,
                  double** val_arr_ptr);
    double* GenArray(vector<double> vec);
    void DelArray(double* val_arr);
}

#endif // MXCSTOOL_MXCSLIB_BASE_H_
