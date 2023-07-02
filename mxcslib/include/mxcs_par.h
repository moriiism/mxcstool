#ifndef MXCSTOOL_MXCSLIB_PAR_H_
#define MXCSTOOL_MXCSLIB_PAR_H_

#include <limits>
#include <cfloat>
#include <string>
using std::string;

const int kRetNormal = 0;
const int kRetError = -1;
const int kLineSize = 10000;

// global variable 
extern int g_flag_debug; 
extern int g_flag_help;
extern int g_flag_verbose;

#endif // MXCSTOOL_MXCSLIB_PAR_H_
