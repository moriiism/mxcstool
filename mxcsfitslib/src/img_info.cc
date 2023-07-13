#include "mxcs_img_info.h"

void MxcsImgInfo::InitSetImg(long fpixel0, long fpixel1,
                            long lpixel0, long lpixel1)
{
    Init(2);
    SetFpixelArrElm(0, fpixel0);
    SetFpixelArrElm(1, fpixel1);
    SetLpixelArrElm(0, lpixel0);
    SetLpixelArrElm(1, lpixel1);
    SetNaxesArr();
}

void MxcsImgInfo::InitSetCube(long fpixel0, long fpixel1, long fpixel2,
                             long lpixel0, long lpixel1, long lpixel2)
{
    Init(3);
    SetFpixelArrElm(0, fpixel0);
    SetFpixelArrElm(1, fpixel1);
    SetFpixelArrElm(2, fpixel2);
    SetLpixelArrElm(0, lpixel0);
    SetLpixelArrElm(1, lpixel1);
    SetLpixelArrElm(2, lpixel2);
    SetNaxesArr();
}

void MxcsImgInfo::InitSet4dim(long fpixel0, long fpixel1, long fpixel2, long fpixel3,
                             long lpixel0, long lpixel1, long lpixel2, long lpixel3)
{
    Init(4);
    SetFpixelArrElm(0, fpixel0);
    SetFpixelArrElm(1, fpixel1);
    SetFpixelArrElm(2, fpixel2);
    SetFpixelArrElm(3, fpixel3);
    SetLpixelArrElm(0, lpixel0);
    SetLpixelArrElm(1, lpixel1);
    SetLpixelArrElm(2, lpixel2);
    SetLpixelArrElm(3, lpixel3);
    SetNaxesArr();
}


void MxcsImgInfo::Load(string file)
{
    string* line_arr = NULL;
    long nline = 0;
    MxcsIolib::GenReadFileSkipComment(file, &line_arr, &nline);
    if(2 != nline){
        printf("bad nline of subcube data: %ld\n", nline);
        abort();
    }
    // read the first line
    int nsplit = 0;
    string* split_arr = NULL;
    MxcsStr::GenSplit(line_arr[0], &nsplit, &split_arr);
    if( ! ( 2 == nsplit || 3 == nsplit || 4 == nsplit) ){
        printf("bad ncolumb of data: %d\n", nsplit);
        abort();
    }
    fpixel_arr_ = new long [nsplit];
    for(int isplit = 0; isplit < nsplit; isplit ++){
        fpixel_arr_[isplit] = atoi(split_arr[isplit].c_str());
    }
    delete [] split_arr;

    // read the second line
    nsplit = 0;
    MxcsStr::GenSplit(line_arr[1], &nsplit, &split_arr);
    if( ! ( 2 == nsplit || 3 == nsplit || 4 == nsplit) ){
        printf("bad ncolumb of data: %d\n", nsplit);
        abort();
    }
    lpixel_arr_ = new long [nsplit];
    for(int isplit = 0; isplit < nsplit; isplit ++){
        lpixel_arr_[isplit] = atoi(split_arr[isplit].c_str());
    }
    delete [] split_arr;

    delete [] line_arr;

    naxis_ = nsplit;
    naxes_arr_ = new long [naxis_];
    for(int iaxis = 0; iaxis < naxis_; iaxis ++){
        naxes_arr_[iaxis] = GetLpixelArrElm(iaxis) - GetFpixelArrElm(iaxis) + 1;
    }
}


void MxcsImgInfo::Copy(const MxcsImgInfo* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    Init(org->GetNaxis());
    for(int iaxis = 0; iaxis < naxis_; iaxis ++){
        fpixel_arr_[iaxis] = org->fpixel_arr_[iaxis];
        lpixel_arr_[iaxis] = org->lpixel_arr_[iaxis];
        naxes_arr_[iaxis] = org->naxes_arr_[iaxis];
    }
}

MxcsImgInfo* const MxcsImgInfo::Clone() const
{
    MxcsImgInfo* obj_new = new MxcsImgInfo;
    obj_new->Copy(this);
    return obj_new;
}

long MxcsImgInfo::GetNpixelImg() const
{
    long npixel = GetNaxesArrElm(0) * GetNaxesArrElm(1);
    return npixel;
}

long MxcsImgInfo::GetNframe() const
{
    long nframe = 0;
    if(2 == naxis_){
        nframe = 1;
    } else if(3 == naxis_){
        nframe = GetNaxesArrElm(2);
    } else {
        printf("error\n");
        abort();
    }
    return nframe;
}

long MxcsImgInfo::GetNpixelTotal() const
{
    long npixel_total = 0;
    if(2 == naxis_){
        npixel_total = GetNaxesArrElm(0) * GetNaxesArrElm(1);
    } else if(3 == naxis_){
        npixel_total = GetNaxesArrElm(0) * GetNaxesArrElm(1)
            * GetNaxesArrElm(2);
    } else if(4 == naxis_){
        npixel_total = GetNaxesArrElm(0) * GetNaxesArrElm(1)
            * GetNaxesArrElm(2) * GetNaxesArrElm(3);
    } else {
        printf("error\n");
        abort();
    }
    return npixel_total;
}


void MxcsImgInfo::PrintInfo() const
{
    printf("naxis_ = %d\n", GetNaxis());
    for(int iaxis = 0; iaxis < GetNaxis(); iaxis ++){
        printf("naxes[%d] = %ld\n", iaxis, GetNaxesArrElm(iaxis));
    }
}


void MxcsImgInfo::Null()
{
    naxis_ = 0;
    if(NULL != fpixel_arr_){
        delete [] fpixel_arr_; fpixel_arr_ = NULL;
    }
    if(NULL != lpixel_arr_){
        delete [] lpixel_arr_; lpixel_arr_ = NULL;
    }
    if(NULL != naxes_arr_){
        delete [] naxes_arr_; naxes_arr_ = NULL;
    }
}

void MxcsImgInfo::Init(int naxis)
{
    Null();
    naxis_ = naxis;
    fpixel_arr_ = new long [naxis_];
    lpixel_arr_ = new long [naxis_];
    naxes_arr_  = new long [naxis_];
}

void MxcsImgInfo::SetFpixelArrElm(int iaxis, long fpixel)
{
    fpixel_arr_[iaxis] = fpixel;
}

void MxcsImgInfo::SetLpixelArrElm(int iaxis, long lpixel)
{
    lpixel_arr_[iaxis] = lpixel;
}

void MxcsImgInfo::SetNaxesArrElm(int iaxis, long naxes)
{
    naxes_arr_[iaxis] = naxes;
}

void MxcsImgInfo::SetNaxesArr()
{
    for(int iaxis = 0; iaxis < GetNaxis(); iaxis ++){
        long naxes = GetLpixelArrElm(iaxis) - GetFpixelArrElm(iaxis) + 1;
        SetNaxesArrElm(iaxis, naxes);
    }
}
