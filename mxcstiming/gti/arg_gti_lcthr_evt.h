#ifndef MXCSTOOL_MXCSTIMING_GTI_ARG_GTI_LCTHR_EVT_H_
#define MXCSTOOL_MXCSTIMING_GTI_ARG_GTI_LCTHR_EVT_H_

#include "mxcs_base.h"

class ArgValLcthrEvt : public MxcsArgBase{
public:
    ArgValLcthrEvt() :
        MxcsArgBase(),
        progname_(""),
        file_(""),
        bin_width_(0.0),
        threshold_(0.0),
        gtiout_(""),
        outdir_(""),
        outfile_head_(""),
        offset_tag_("") {}
    ~ArgValLcthrEvt(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetFile() const {return file_;};
    double GetBinWidth() const {return bin_width_;};
    double GetThreshold() const {return threshold_;};
    string GetGtiOut() const {return gtiout_;};
    string GetOutdir() const {return outdir_;};
    string GetOutfileHead() const {return outfile_head_;};
    string GetOffsetTag() const {return offset_tag_;};
  
private:
    string progname_;
    string file_;
    double bin_width_;
    double threshold_;
    string gtiout_;
    string outdir_;
    string outfile_head_;
    string offset_tag_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXCSTOOL_MXCSTIMING_GTI_ARG_GTI_LCTHR_EVT_H_

