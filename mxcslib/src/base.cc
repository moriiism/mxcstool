#include "mxcs_base.h"

//
// MxcsObject
//

// protected

void MxcsObject::CopyTitle(const MxcsObject* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}

    title_      = org->title_;
}

// private

void MxcsObject::NullMxcsObject()
{
    class_name_ = "";
    title_      = "";
}

//
// MxcsBase
//

void MxcsBase::IsValidArray(long narr, const int* const val_arr)
{
    if(narr < 1){
        char msg[kLineSize];
        sprintf(msg, "narr (=%ld) < 1", narr);
        MxcsPrintErr(msg);
        abort();
    }
    if(NULL == val_arr){
        char msg[kLineSize];
        sprintf(msg, "val_arr == NULL");
        MxcsPrintErr(msg);
        abort();
    }
}

void MxcsBase::IsValidArray(long narr, const double* const val_arr)
{
    if(narr < 1){
        char msg[kLineSize];
        sprintf(msg, "narr (=%ld) < 1", narr);
        MxcsPrintErr(msg);
        abort();
    }
    if(NULL == val_arr){
        char msg[kLineSize];
        sprintf(msg, "val_arr == NULL");
        MxcsPrintErr(msg);
        abort();
    }
}

void MxcsBase::GenArray(vector<double> vec,
                        long* narr_ptr,
                        double** val_arr_ptr)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    *narr_ptr = narr;
    *val_arr_ptr = val_arr;
}

double* MxcsBase::GenArray(vector<double> vec)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    return val_arr;
}

void MxcsBase::DelArray(double* val_arr)
{
    delete [] val_arr; val_arr = NULL;
}
