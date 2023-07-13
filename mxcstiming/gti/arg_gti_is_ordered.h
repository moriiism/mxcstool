#ifndef MXCSTOOL_MXCSTIMING_GTI_ARG_GTI_IS_ORDERED_H_
#define MXCSTOOL_MXCSTIMING_GTI_ARG_GTI_IS_ORDERED_H_

#include "mxcs_base.h"

class ArgValGtiIsOrdered : public MxcsArgBase{
public:
    ArgValGtiIsOrdered() :
        MxcsArgBase(),
        progname_(""),
        gti_("") {}
    ~ArgValGtiIsOrdered(){
        Null();
    }
    void Init(int argc, char* argv[]);
    void Print(FILE* fp) const;

    string GetProgname() const {return progname_;};
    string GetGti() const {return gti_;};

private:
    string progname_;
    string gti_;

    void Null();
    void Usage(FILE* fp) const;
    void SetOption(int argc, char* argv[], option* long_options);
};

#endif // MXCSTOOL_MXCSTIMING_GTI_ARG_GTI_IS_ORDERED_H_
