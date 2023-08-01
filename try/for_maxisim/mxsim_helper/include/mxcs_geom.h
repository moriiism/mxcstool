#ifndef MXCSTOOL_MXCSANALIB_GEOM_H_
#define MXCSTOOL_MXCSANALIB_GEOM_H_

#include "mxcs_vect.h"

// function of conversion is for coordinate.

namespace MxcsGeom
{
    // flag: -1: coordinate
    //        1: object
    Vect2d* GenShift(const Vect2d* const vect,
                     double shiftx, double shifty, int flag);
    Vect2d* GenRot(const Vect2d* const vect,
                   double angle, int flag);
    Vect2d* GenMotion(const Vect2d* const vect,
                      double shiftx, double shifty,
                      double angle, int flag);
}

#endif // MXCSTOOL_MXCSANALIB_GEOM_H_
