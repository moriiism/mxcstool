#ifndef MXCSTOOL_MXCSANALIB_SOLVE_H_
#define MXCSTOOL_MXCSANALIB_SOLVE_H_

#include "mxcs_func.h"

namespace MxcsSolve
{
    double GetRootNewton(const MxcsFunc* const func,
                         const double* const par_func,
                         const MxcsFunc* const func_prime,
                         const double* const par_func_prime,
                         double root_init, double epsilon);

    // solve equation: f(x) = 0
    double GetRootSecant(const MxcsFunc* const func,
                         const double* const par_func,
                         double root_init0, double root_init1,
                         double epsilon);

    // solve equation: f(x) = constant
    double GetRootSecantEqC(const MxcsFunc* const func,
                            const double* const par_func,
                            double root_init0, double root_init1,
                            double constant, double epsilon);

    // solve equation: f(x) = 0
    double GetRootBisection(const MxcsFunc* const func,
                            const double* const par_func,
                            double root_init0, double root_init1,
                            double epsilon);

    // solve equation: f(x) = constant
    double GetRootBisectionEqC(const MxcsFunc* const func,
                               const double* const par_func,
                               double root_init0, double root_init1,
                               double constant, double epsilon);
    
} // namespace MxcsSolve

#endif // MXCSTOOL_MXCSANALIB_SOLVE_H_

