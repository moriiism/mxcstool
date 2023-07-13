#ifndef MXCSTOOL_MXCSTIMING_LC_ARG_PLOT_LC_DA1D_H_
#define MXCSTOOL_MXCSTIMING_LC_ARG_PLOT_LC_DA1D_H_

#include "mxcs_base.h"

class ArgValPlotLcDa1d : public MxcsArgBase{
public:
    ArgValPlotLcDa1d() :
        MxcsArgBase(),
        progname_(""),
        file_(""),
        hist_info_(""),
        outdir_(""),
        outfile_head_(""){}
    ~ArgValPlotLcDa1d(){}
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFile() const {return file_;};
    string GetHistInfo() const {return hist_info_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};

private:
    string progname_;
    string file_;
    string hist_info_;
    string outdir_;
    string outfile_head_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXCSTOOL_MXCSTIMING_LC_ARG_PLOT_LC_DA1D_H_
