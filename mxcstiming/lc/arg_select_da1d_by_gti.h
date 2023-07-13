#ifndef MXCSTOOL_MXCSTIMING_LC_ARG_SELECT_DA1D_BY_GTI_H_
#define MXCSTOOL_MXCSTIMING_LC_ARG_SELECT_DA1D_BY_GTI_H_

#include "mxcs_base.h"

class ArgValSelectDa1dByGti : public MxcsArgBase{
public:
    ArgValSelectDa1dByGti() :
        MxcsArgBase(),
        progname_(""),
        lc_file_(""),
        gti_file_(""),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValSelectDa1dByGti(){}
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetLcFile() const {return lc_file_;};
    string GetGtiFile() const {return gti_file_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string lc_file_;
    string gti_file_;
    string outdir_;
    string outfile_head_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXCSTOOL_MXCSTIMING_LC_ARG_SELECT_DA1D_BY_GTI_H_
