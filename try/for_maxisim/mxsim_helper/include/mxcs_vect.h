#ifndef MXCSTOOL_MXCSANALIB_VECT_H_
#define MXCSTOOL_MXCSANALIB_VECT_H_

#include "mxcs_base.h"

class Vect2d : public MxcsObject{
public:
    explicit Vect2d(string title = "") :
        MxcsObject("Vect2d", title),
        pos_x_(0.0),
        pos_y_(0.0) {}
    ~Vect2d() {
        Null();
    }
    void Init(double pos_x, double pos_y);
    void Copy(const Vect2d* const org);
    Vect2d* const Clone() const;

    double GetPosX() const {return pos_x_;};
    double GetPosY() const {return pos_y_;};
    double GetLength() const;
    Vect2d* const GenVectUnit() const;
    Vect2d* const GenVectWithLength(double length) const;

    void Print(FILE* fp) const;
    
private:
    double pos_x_;
    double pos_y_;
    void Null();
};

#endif // MXCSTOOL_MXCSANALIB_VECT_H_
