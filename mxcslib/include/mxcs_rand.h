#ifndef MXCSTOOL_MXCSLIB_RAND_H_
#define MXCSTOOL_MXCSLIB_RAND_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <random>
#include "mxcs_base.h"

class MxcsRand: private Uncopyable{
public:
    MxcsRand(){}
    ~MxcsRand(){}

    void Init(int seed);
    double Uniform(void);
    double Normal(double mu, double sigma);
    int Poisson(double mean);
private:
    std::mt19937 mt_;
};

#endif // MXCSTOOL_MXCSLIB_RAND_H_
