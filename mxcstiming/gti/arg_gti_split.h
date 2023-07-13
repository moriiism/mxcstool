#ifndef MXCSTOOL_MXCSTIMING_GTI_ARG_GTI_SPLIT_H_
#define MXCSTOOL_MXCSTIMING_GTI_ARG_GTI_SPLIT_H_

#include "mxcs_base.h"

class ArgValGtiSplit : public MxcsArgBase{
public:
    ArgValGtiSplit() :
        MxcsArgBase(),
        progname_(""),
        tstart_(0.0),
        tstop_(0.0),
        nsplit_(0),
        gti_out_("") {}
    ~ArgValGtiSplit(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    double GetTstart() const {return tstart_;};
    double GetTstop() const {return tstop_;};
    long   GetNsplit() const {return nsplit_;};
    string GetGtiOut() const {return gti_out_;};

private:
    string progname_;
    double tstart_;
    double tstop_;
    long   nsplit_;
    string gti_out_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXCSTOOL_MXCSTIMING_GTI_ARG_GTI_SPLIT_H_
