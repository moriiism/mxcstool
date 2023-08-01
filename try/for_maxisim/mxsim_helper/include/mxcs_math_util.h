#ifndef MXCSTOOL_MXCSANALIB_MATH_UTIL_H_
#define MXCSTOOL_MXCSANALIB_MATH_UTIL_H_

#include "mxcs_sort.h"
#include "mxcs_math.h"

namespace MxcsMathUtil
{
    // get mean and stddev by clipping
    void GetMeanStddevClip(long narr, const double* const val_arr,
                           int nclip, double significance,
                           double* const mean_ptr,
                           double* const stddev_ptr);

    void GetMarginLoUp(double min, double max,
                       double margin_ratio,
                       double* const lo_ptr,
                       double* const up_ptr);

    void Uniq(long narr, const double* const val_arr,
              long* const nuniq, double** const uniq_arr_ptr,
              double epsilon);

    void GetQuantile(long narr, const double* const val_arr,
                     long nquantile,
                     double** const quantile_arr_ptr);

    double GetAMeanLog10(double aval, double bval);
    double GetAMeanLog10(long narr, const double* const val_arr);
    double GetAMeanLog10(vector<double> vec);
    
} //  namespace MxcsMathUtil

#endif // MXCSTOOL_MXCSANALIB_MATH_UTIL_H_
