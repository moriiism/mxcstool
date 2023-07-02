#ifndef MXCSTOOL_MXCSLIB_RAND_H_
#define MXCSTOOL_MXCSLIB_RAND_H_

#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "random.h"

namespace MxcsRand
{
    void Init(long seed);
    double Uniform(void);
    double Normal(double mu, double sigma);
    
}  //  namespace MxcsRand

#endif // MXCSTOOL_MXCSLIB_RAND_H_
