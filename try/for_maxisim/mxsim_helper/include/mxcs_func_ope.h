#ifndef MXCSTOOL_MXCSANALIB_FUNC_OPE_H_
#define MXCSTOOL_MXCSANALIB_FUNC_OPE_H_

#include "mxcs_func_par.h"
#include "mxcs_func.h"

namespace MxcsFuncOpe{
    void DrawFunc(const MxcsFunc* const func,
                  const MxcsFuncPar* const func_par,
                  MxcsRootTool* const root_tool,
                  double x_low, double x_up,
                  string outfig);
    void DrawFunc(const MxcsFunc* const func,
                  const MxcsFuncPar* const func_par,
                  MxcsRootTool* const root_tool,
                  double x_low, double x_up,
                  double y_low, double y_up,
                  string outfig);
    double GetRandom(const MxcsFunc* const func,
                     const MxcsFuncPar* const func_par,
                     double x_low, double x_up,
                     int rand_seed);
    double GetRandom(const MxcsFunc* const func,
                     const MxcsFuncPar* const func_par,
                     double x_low, double x_up,
                     double y_low, double y_up,
                     int rand_seed);
    // If rand_seed is 0, the seed is automatically
    // computed via a TUUID object.
    // In this case the seed is guaranteed
    // to be unique in space and time.
}

#endif // MXCSTOOL_MXCSANALIB_FUNC_OPE_H_
