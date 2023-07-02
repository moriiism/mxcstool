#ifndef MXCSTOOL_MXCSANALIB_BINNING_H_
#define MXCSTOOL_MXCSANALIB_BINNING_H_

#include "mxcs_math.h"

namespace MxcsBinning
{
    // bin edge
    void GetPoint(long npoint, double lo, double up,
                  string scale, double* const point_arr);
    void GetPointLin(long npoint, double lo, double up,
                     double* const point_arr);
    void GetPointLog(long npoint, double lo, double up,
                     double* const point_arr);

    // bin center
    void GetBin(long nbin, double lo, double up,
                string scale, double* const bin_arr);
    void GetBinLin(long nbin, double lo, double up,
                   double* const bin_arr);
    void GetBinLog(long nbin, double lo, double up,
                   double* const bin_arr);
    
} //  namespace MxcsBinning

#endif // MXCSTOOL_MXCSANALIB_BINNING_H_
