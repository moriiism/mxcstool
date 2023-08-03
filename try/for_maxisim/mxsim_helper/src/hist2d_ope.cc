#include "mxcs_vect.h"
#include "mxcs_hist2d_ope.h"

DataArray1d** const HistData2dOpe::GenDa1dArrNerr(
    const HistData2d* const* const hd2d_arr,
    int narr)
{
    DataArray1d** da1d_arr = new DataArray1d* [narr];
    for(int iarr = 0; iarr < narr; iarr ++){
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Copy(hd2d_arr[iarr]->GetOvalArr());
    }
    return da1d_arr;
}

DataArray1d** const HistData2dOpe::GenDa1dArrSerr(
    const HistData2d* const* const hd2d_arr,
    int narr)
{
    DataArray1d** da1d_arr = new DataArray1d* [narr];
    for(int iarr = 0; iarr < narr; iarr ++){
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Copy(hd2d_arr[iarr]->GetOvalArr());
    }
    return da1d_arr;
}

void HistData2dOpe::DelHd2dArr(HistData2d** const hd2d_arr, int narr)
{
    for(int iarr = 0; iarr < narr; iarr ++){
        delete hd2d_arr[iarr];
    }
    delete [] hd2d_arr;
}

int HistData2dOpe::IsFormatSame(const HistData2d* const data1,
                                const HistData2d* const data2)
{
    if(data1->GetNbinX()  != data2->GetNbinX()  ||
       data1->GetXvalLo() != data2->GetXvalLo() ||
       data1->GetXvalUp() != data2->GetXvalUp() ||
       data1->GetNbinY()  != data2->GetNbinY()  ||
       data1->GetYvalLo() != data2->GetYvalLo() ||
       data1->GetYvalUp() != data2->GetYvalUp()   ){
        MxcsPrintErr("format of data1 and data2 are diffenret.");
        char msg[kLineSize];
        sprintf(msg, "data1: (GetNbinX(), GetXvalLo(), GetXvalUp()) "
                "= (%ld, %e, %e)\n",
                data1->GetNbinX(),
                data1->GetXvalLo(),
                data1->GetXvalUp());
        MxcsPrintErr(msg);
        sprintf(msg, "data1: (GetNbinY(), GetYvalLo(), GetYvalUp()) "
                "= (%ld, %e, %e)\n",
                data1->GetNbinY(),
                data1->GetYvalLo(),
                data1->GetYvalUp());
        MxcsPrintErr(msg);        
        sprintf(msg, "data2: (GetNbinX(), GetXvalLo(), GetXvalUp()) "
                "= (%ld, %e, %e)\n",
                data2->GetNbinX(),
                data2->GetXvalLo(),
                data2->GetXvalUp());
        MxcsPrintErr(msg);        
        sprintf(msg, "data2: (GetNbinY(), GetYvalLo(), GetYvalUp()) "
                "= (%ld, %e, %e)\n",
                data2->GetNbinY(),
                data2->GetYvalLo(),
                data2->GetYvalUp());
        MxcsPrintErr(msg);        
        abort();
    }
    return 1;
}

int HistData2dOpe::IsFormatSame(const HistData2d* const* const data_arr,
                                int nhist)
{
    if(nhist < 2){
        char msg[kLineSize];
        sprintf(msg, "nhist(=%d) < 2\n", nhist);
        MxcsPrintWarn(msg);
        MxcsPrintWarn("skip check");
        return 0;
    }
    for(int ihist = 1; ihist < nhist; ihist++){
        if(data_arr[0]->GetNbinX()  != data_arr[ihist]->GetNbinX()  ||
           data_arr[0]->GetXvalLo() != data_arr[ihist]->GetXvalLo() ||
           data_arr[0]->GetXvalUp() != data_arr[ihist]->GetXvalUp() ||
           data_arr[0]->GetNbinY()  != data_arr[ihist]->GetNbinY()  ||
           data_arr[0]->GetYvalLo() != data_arr[ihist]->GetYvalLo() ||
           data_arr[0]->GetYvalUp() != data_arr[ihist]->GetYvalUp()   ){
            char msg[kLineSize];
            sprintf(msg, "format of data_arr[0] and data_arr[%d] are different\n",
                    ihist);
            MxcsPrintErr(msg);
            sprintf(msg, "data_arr[0]: (GetNbinX(), GetXvalLo(), GetXvalUp()) "
                    "= (%ld, %e, %e)\n",
                    data_arr[0]->GetNbinX(),
                    data_arr[0]->GetXvalLo(),
                    data_arr[0]->GetXvalUp());
            MxcsPrintErr(msg);            
            sprintf(msg, "data_arr[0]: (GetNbinY(), GetYvalLo(), GetYvalUp()) "
                    "= (%ld, %e, %e)\n",
                    data_arr[0]->GetNbinY(),
                    data_arr[0]->GetYvalLo(),
                    data_arr[0]->GetYvalUp());
            MxcsPrintErr(msg);                        
            sprintf(msg, "data_arr[%d]: (GetNbinX(), GetXvalLo(), GetXvalUp()) "
                    "= (%ld, %e, %e)\n",
                    ihist,
                    data_arr[ihist]->GetNbinX(),
                    data_arr[ihist]->GetXvalLo(),
                    data_arr[ihist]->GetXvalUp());
            MxcsPrintErr(msg);                                    
            sprintf(msg, "data_arr[%d]: (GetNbinY(), GetYvalLo(), GetYvalUp()) "
                    "= (%ld, %e, %e)\n",
                    ihist,
                    data_arr[ihist]->GetNbinY(),
                    data_arr[ihist]->GetYvalLo(),
                    data_arr[ihist]->GetYvalUp());
            MxcsPrintErr(msg);                                    
            abort();
        }
    }
    return 1;
}


// For one HistData2d
void HistData2dOpe::GetNot(const HistData2d* const in,
                           HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetNot(in->GetOvalArr(),
                           da1d);
    out->Init(in->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}

void HistData2dOpe::GetNot(const HistData2d* const in,
                           HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetNot(in->GetOvalArr(),
                           da1d);
    out->Init(in->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}

void HistData2dOpe::GetScale(const HistData2d* const in,
                             double scale, double offset,
                             HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetScale(in->GetOvalArr(),
                             scale, offset,
                             da1d);
    out->Init(in->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
   
void HistData2dOpe::GetScale(const HistData2d* const in,
                             double scale, double offset,
                             HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetScale(in->GetOvalArr(),
                             scale, offset,
                             da1d);
    out->Init(in->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}

   
// For two HistData2d
void HistData2dOpe::GetMin(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMin(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetMin(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMin(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetMax(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMax(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetMax(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMax(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}

void HistData2dOpe::GetAdd(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetAdd(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetAdd(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetAdd(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
void HistData2dOpe::GetSub(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetSub(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetSub(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetSub(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
void HistData2dOpe::GetMul(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMul(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    

void HistData2dOpe::GetMul(const HistData2d* const in1,
                           const HistData2d* const in2,
                           HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMul(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
int HistData2dOpe::GetDiv(const HistData2d* const num,
                          const HistData2d* const den,
                          HistDataNerr2d* const mask_sel_out,
                          HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetDiv(num->GetOvalArr(),
                                     den->GetOvalArr(),
                                     da1d_mask,
                                     da1d);
    out->Init(num->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(num->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    
int HistData2dOpe::GetDiv(const HistData2d* const num,
                          const HistData2d* const den,
                          HistDataNerr2d* const mask_sel_out,
                          HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetDiv(num->GetOvalArr(),
                                     den->GetOvalArr(),
                                     da1d_mask,
                                     da1d);
    out->Init(num->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(num->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    
    
void HistData2dOpe::GetAMean(const HistData2d* const in1,
                             const HistData2d* const in2,
                             HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetAMean(in1->GetOvalArr(),
                             in2->GetOvalArr(),
                             da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData2dOpe::GetAMean(const HistData2d* const in1,
                             const HistData2d* const in2,
                             HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetAMean(in1->GetOvalArr(),
                             in2->GetOvalArr(),
                             da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
int HistData2dOpe::GetWMean(const HistData2d* const in1,
                            const HistData2d* const in2,
                            HistDataNerr2d* const mask_sel_out,
                            HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetWMean(in1->GetOvalArr(),
                                       in2->GetOvalArr(),
                                       da1d_mask,
                                       da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in1->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    

int HistData2dOpe::GetSubAddRatio(const HistData2d* const in1,
                                  const HistData2d* const in2,
                                  HistDataNerr2d* const mask_sel_out,
                                  HistDataNerr2d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetSubAddRatio(in1->GetOvalArr(),
                                             in2->GetOvalArr(),
                                             da1d_mask,
                                             da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in1->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    

int HistData2dOpe::GetSubAddRatio(const HistData2d* const in1,
                                  const HistData2d* const in2,
                                  HistDataNerr2d* const mask_sel_out,
                                  HistDataSerr2d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetSubAddRatio(in1->GetOvalArr(),
                                             in2->GetOvalArr(),
                                             da1d_mask,
                                             da1d);
    out->Init(in1->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in1->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    

// For N HistData1d
void HistData2dOpe::GetMin(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMin(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetMin(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMin(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetMax(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMax(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetMax(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMax(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetSum(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetSum(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetSum(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetSum(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
    
void HistData2dOpe::GetAMean(const HistData2d* const* const in_arr,
                             int narr,
                             HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetAMean(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetAMean(const HistData2d* const* const in_arr,
                             int narr,
                             HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetAMean(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
    
int HistData2dOpe::GetWMean(const HistData2d* const* const in_arr,
                            int narr,
                            HistDataNerr2d* const mask_sel_out,
                            HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask_sel = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetWMean(da1d_arr, narr, da1d_mask_sel, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in_arr[0]->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask_sel);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
    delete da1d_mask_sel;
    return ret;
}
    
    
void HistData2dOpe::GetVariance(const HistData2d* const* const in_arr,
                                int narr,
                                HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetVariance(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetStddev(const HistData2d* const* const in_arr,
                              int narr,
                              HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetStddev(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetUnbiasedVariance(const HistData2d* const* const in_arr,
                                        int narr,
                                        HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetUnbiasedVariance(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetSqrtOfUnbiasedVariance(
    const HistData2d* const* const in_arr,
    int narr,
    HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetSqrtOfUnbiasedVariance(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetRMS(const HistData2d* const* const in_arr,
                           int narr,
                           HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetRMS(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetMedian(const HistData2d* const* const in_arr,
                              int narr,
                              HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMedian(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
                   
void HistData2dOpe::GetSumWithMask(const HistData2d* const* const in_arr,
                                   const HistData2d* const* const mask_arr,
                                   int narr,
                                   HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetSumWithMask(da1d_arr, da1d_mask_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetSumWithMask(const HistData2d* const* const in_arr,
                                   const HistData2d* const* const mask_arr,
                                   int narr,
                                   HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetSumWithMask(da1d_arr, da1d_mask_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
}
    
    
void HistData2dOpe::GetAMeanWithMask(const HistData2d* const* const in_arr,
                                     const HistData2d* const* const mask_arr,
                                     int narr,
                                     HistDataNerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetAMeanWithMask(da1d_arr, da1d_mask_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
}
    
void HistData2dOpe::GetAMeanWithMask(const HistData2d* const* const in_arr,
                                     const HistData2d* const* const mask_arr,
                                     int narr,
                                     HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetAMeanWithMask(da1d_arr, da1d_mask_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
}
    
    
int HistData2dOpe::GetWMeanWithMask(const HistData2d* const* const in_arr,
                                    const HistData2d* const* const mask_arr,
                                    int narr,
                                    HistDataNerr2d* const mask_sel_out,
                                    HistDataSerr2d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);    
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask_sel = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetWMeanWithMask(da1d_arr, da1d_mask_arr,
                                               narr, da1d_mask_sel, da1d);
    out->Init(in_arr[0]->GetHi2d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in_arr[0]->GetHi2d());
    mask_sel_out->SetOvalArr(da1d_mask_sel);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
    delete da1d_mask_sel;
    return ret;
}

void HistData2dOpe::GetResValHd2d(const HistData2d* const data,
                                  const MxcsFunc* const func,
                                  const double* const par,
                                  HistDataNerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = data->GetOvalElm(ibin_x, ibin_y)
            - func->Eval(xval_arg, par);
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    delete [] oval_res;
}

void HistData2dOpe::GetResValHd2d(const HistData2d* const data,
                                  const MxcsFunc* const func,
                                  const double* const par,
                                  HistDataSerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = data->GetOvalElm(ibin_x, ibin_y)
            - func->Eval(xval_arg, par);
        oval_res_serr[ibin] = data->GetOvalSerrElm(ibin_x, ibin_y);
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    out->SetOvalSerrArr(nbinx * nbiny, oval_res_serr);    
    delete [] oval_res;
    delete [] oval_res_serr;
}

void HistData2dOpe::GetResRatioHd2d(const HistData2d* const data,
                                    const MxcsFunc* const func,
                                    const double* const par,
                                    HistDataNerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = (data->GetOvalElm(ibin_x, ibin_y)
                          - func->Eval(xval_arg, par))
            / func->Eval(xval_arg, par);
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    delete [] oval_res;
}

void HistData2dOpe::GetResRatioHd2d(const HistData2d* const data,
                                    const MxcsFunc* const func,
                                    const double* const par,
                                    HistDataSerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = (data->GetOvalElm(ibin_x, ibin_y)
                          - func->Eval(xval_arg, par))
            / func->Eval(xval_arg, par);
        oval_res_serr[ibin] = fabs( data->GetOvalSerrElm(ibin_x, ibin_y)
                                    / func->Eval(xval_arg, par) );
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    out->SetOvalSerrArr(nbinx * nbiny, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}

void HistData2dOpe::GetResChiHd2d(const HistData2d* const data,
                                  const MxcsFunc* const func,
                                  const double* const par,
                                  HistDataSerr2d* const out)
{
    long nbinx = data->GetNbinX();
    long nbiny = data->GetNbinY();
    long nbin = nbinx * nbiny;
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        long ibin_x = data->GetHi2d()->GetIbinX(ibin);
        long ibin_y = data->GetHi2d()->GetIbinY(ibin);
        double xval_arg[2];
        double xval_tmp, yval_tmp;
        data->GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_tmp, &yval_tmp);
        xval_arg[0] = xval_tmp;
        xval_arg[1] = yval_tmp;
        oval_res[ibin] = (data->GetOvalElm(ibin_x, ibin_y)
                          - func->Eval(xval_arg, par)) /
            data->GetOvalSerrElm(ibin_x, ibin_y);
        oval_res_serr[ibin] = 1.0;
    }
    out->Init(nbinx, data->GetXvalLo(), data->GetXvalUp(),
              nbiny, data->GetYvalLo(), data->GetYvalUp());
    out->SetOvalArr(nbinx * nbiny, oval_res);
    out->SetOvalSerrArr(nbinx * nbiny, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}

double HistData2dOpe::FindMdXbyEdge(const HistDataNerr2d* const hd2d)
{
    vector<double> md_vec;
    for(long ibiny = 0; ibiny < hd2d->GetNbinY(); ibiny ++){
        vector<double> on_vec;
        for(long ibinx = 0; ibinx < hd2d->GetNbinX(); ibinx ++){
            if( fabs(hd2d->GetOvalElm(ibinx, ibiny) - 1.0) < DBL_EPSILON){
                on_vec.push_back(ibinx);
            }
        }
        if(0 < on_vec.size()){
            double index_min = MxcsMath::GetMin(on_vec);
            double index_max = MxcsMath::GetMax(on_vec);
            double index_md = (index_min + index_max)/2.;
            md_vec.push_back(index_md);
        }
    }
    double md_index_amean = MxcsMath::GetAMean(md_vec);
    double xval_md = hd2d->GetXvalLo() + hd2d->GetBinWidthX() * md_index_amean;
    return xval_md;
}

double HistData2dOpe::FindMdYbyEdge(const HistDataNerr2d* const hd2d)
{
    vector<double> md_vec;
    for(long ibinx = 0; ibinx < hd2d->GetNbinX(); ibinx ++){    
        vector<double> on_vec;
        for(long ibiny = 0; ibiny < hd2d->GetNbinY(); ibiny ++){
            if( fabs(hd2d->GetOvalElm(ibinx, ibiny) - 1.0) < DBL_EPSILON){
                on_vec.push_back(ibiny);
            }
        }
        if(0 < on_vec.size()){
            double index_min = MxcsMath::GetMin(on_vec);
            double index_max = MxcsMath::GetMax(on_vec);
            double index_md = (index_min + index_max)/2.;
            md_vec.push_back(index_md);
        }
    }
    double md_index_amean = MxcsMath::GetAMean(md_vec);
    double yval_md = hd2d->GetYvalLo() + hd2d->GetBinWidthY() * md_index_amean;
    return yval_md;
}

void HistData2dOpe::GetProjectX(const HistData2d* const in,
                                long ibin_ylo, long ibin_yup,
                                string calc_mode,
                                HistDataNerr1d* const out)
{
    in->GetHi2d()->IsValidIbinY(ibin_ylo);
    in->GetHi2d()->IsValidIbinY(ibin_yup);
    
    out->Init(in->GetNbinX(),
              in->GetXvalLo(),
              in->GetXvalUp());
    for(long ibin_xval = 0; ibin_xval < in->GetNbinX(); ibin_xval++){
        long nbin_tmp = ibin_yup - ibin_ylo + 1;
        double* tmp_arr = new double [nbin_tmp];
        long ibin_tmp = 0;
        for(long ibin_yval = ibin_ylo; ibin_yval <= ibin_yup; ibin_yval++){
            tmp_arr[ibin_tmp] = in->GetOvalElm(ibin_xval, ibin_yval);
            ibin_tmp ++;
        }
        double val_proj = 0.0;
        GetProject(nbin_tmp, tmp_arr,
                   calc_mode, in->GetBinWidthY(),
                   &val_proj);
        delete [] tmp_arr;
        out->SetOvalElm(ibin_xval, val_proj);
    }
}

void HistData2dOpe::GetProjectX(const HistData2d* const in,
                                long ibin_ylo, long ibin_yup,
                                string calc_mode, string error_mode,
                                HistDataSerr1d* const out)
{
    in->GetHi2d()->IsValidIbinY(ibin_ylo);
    in->GetHi2d()->IsValidIbinY(ibin_yup);
    out->Init(in->GetNbinX(),
              in->GetXvalLo(),
              in->GetXvalUp());
    for(long ibin_xval = 0; ibin_xval < in->GetNbinX(); ibin_xval++){
        long nbin_tmp = ibin_yup - ibin_ylo + 1;
        double* tmp_arr = new double [nbin_tmp];
        double* tmp_err_arr = new double [nbin_tmp];
        long ibin_tmp = 0;
        for(long ibin_yval = ibin_ylo; ibin_yval <= ibin_yup; ibin_yval++){
            tmp_arr[ibin_tmp]     = in->GetOvalElm(ibin_xval, ibin_yval);
            tmp_err_arr[ibin_tmp] = in->GetOvalSerrElm(ibin_xval, ibin_yval);
            ibin_tmp ++;
        }
        double val_proj = 0.0;
        double val_proj_err = 0.0;
        GetProject(nbin_tmp,
                   tmp_arr, tmp_err_arr,
                   calc_mode, error_mode,
                   in->GetBinWidthY(),
                   &val_proj, &val_proj_err);
        delete [] tmp_arr;
        delete [] tmp_err_arr;
        out->SetOvalElm(ibin_xval, val_proj);
        out->SetOvalSerrElm(ibin_xval, val_proj_err);
    }
}

void HistData2dOpe::GetProjectY(const HistData2d* const in,
                                long ibin_xlo, long ibin_xup,
                                string calc_mode,
                                HistDataNerr1d* const out)
{
    in->GetHi2d()->IsValidIbinX(ibin_xlo);
    in->GetHi2d()->IsValidIbinX(ibin_xup);
    
    out->Init(in->GetNbinY(),
              in->GetYvalLo(),
              in->GetYvalUp());
    for(long ibin_yval = 0; ibin_yval < in->GetNbinY(); ibin_yval++){
        long nbin_tmp = ibin_xup - ibin_xlo + 1;
        double* tmp_arr = new double [nbin_tmp];
        long ibin_tmp = 0;
        for(long ibin_xval = ibin_xlo; ibin_xval <= ibin_xup; ibin_xval++){
            tmp_arr[ibin_tmp] = in->GetOvalElm(ibin_xval, ibin_yval);
            ibin_tmp ++;
        }
        double val_proj = 0.0;
        GetProject(nbin_tmp, tmp_arr,
                   calc_mode, in->GetBinWidthX(),
                   &val_proj);
        delete [] tmp_arr;
        out->SetOvalElm(ibin_yval, val_proj);
    }
}

void HistData2dOpe::GetProjectY(const HistData2d* const in,
                                long ibin_xlo, long ibin_xup,
                                string calc_mode, string error_mode,
                                HistDataSerr1d* const out)
{
    in->GetHi2d()->IsValidIbinX(ibin_xlo);
    in->GetHi2d()->IsValidIbinX(ibin_xup);
    out->Init(in->GetNbinY(),
              in->GetYvalLo(),
              in->GetYvalUp());
    for(long ibin_yval = 0; ibin_yval < in->GetNbinY(); ibin_yval++){
        long nbin_tmp = ibin_xup - ibin_xlo + 1;
        double* tmp_arr = new double [nbin_tmp];
        double* tmp_err_arr = new double [nbin_tmp];
        long ibin_tmp = 0;
        for(long ibin_xval = ibin_xlo; ibin_xval <= ibin_xup; ibin_xval++){
            tmp_arr[ibin_tmp]     = in->GetOvalElm(ibin_xval, ibin_yval);
            tmp_err_arr[ibin_tmp] = in->GetOvalSerrElm(ibin_xval, ibin_yval);
            ibin_tmp ++;
        }
        double val_proj = 0.0;
        double val_proj_err = 0.0;
        GetProject(nbin_tmp,
                   tmp_arr, tmp_err_arr,
                   calc_mode, error_mode,
                   in->GetBinWidthX(),
                   &val_proj, &val_proj_err);
        delete [] tmp_arr;
        delete [] tmp_err_arr;
        out->SetOvalElm(ibin_yval, val_proj);
        out->SetOvalSerrElm(ibin_yval, val_proj_err);
    }
}


void HistData2dOpe::GetProject(long ndata,
                               const double* const array,
                               string calc_mode, double bin_width,
                               double* const val_proj_ptr)
{
    double val_proj = 0.0;
    if("add" == calc_mode){
        val_proj = MxcsMath::GetSum(ndata, array);
    } else if ("integral" == calc_mode){
        val_proj = MxcsMath::GetSum(ndata, array) * bin_width;
    } else if ("amean" == calc_mode){
        val_proj = MxcsMath::GetAMean(ndata, array);
    } else if ("min" == calc_mode){
        val_proj = MxcsMath::GetMin(ndata, array);
    } else if ("max" == calc_mode){
        val_proj = MxcsMath::GetMax(ndata, array);
    } else if ("stddev" == calc_mode){
        val_proj = MxcsMath::GetStddev(ndata, array);
    } else {
        MxcsPrintErr("bad calc_mode");
        abort();
    }
    *val_proj_ptr = val_proj;
}

void HistData2dOpe::GetProject(long ndata,
                               const double* const array,
                               const double* const array_err,
                               string calc_mode, string error_mode,
                               double bin_width,
                               double* const val_proj_ptr,
                               double* const val_proj_err_ptr)
{
    double val_proj = 0.0;
    double val_proj_err = 0.0;
    if("add" == calc_mode || "integral" == calc_mode){
        if("gauss" == error_mode){
            MxcsMath::GetSum(ndata, array, array_err, &val_proj, &val_proj_err);
        } else if("poisson" == error_mode){
            val_proj = MxcsMath::GetSum(ndata, array);
            val_proj_err = sqrt(val_proj);
        } else if("zero" == error_mode){
            val_proj = MxcsMath::GetSum(ndata, array);
            val_proj_err = 0.0;
        } else {
            MxcsPrintErr("bad error_mode");
            abort();
        }
        if("integral" == calc_mode){
            val_proj *= bin_width;
            val_proj_err *= bin_width;
        }
    } else if ("amean" == calc_mode){
        if("gauss" == error_mode){
            MxcsMath::GetAMean(ndata, array, array_err, &val_proj, &val_proj_err);
        } else if("poisson" == error_mode){
            double val_add = MxcsMath::GetSum(ndata, array);
            val_proj = val_add / ndata;
            val_proj_err = sqrt(val_add) / ndata;
        } else if("zero" == error_mode){
            double val_add = MxcsMath::GetSum(ndata, array);
            val_proj = val_add / ndata;
            val_proj_err = 0.0;
        } else {
            MxcsPrintErr("bad error_mode");
            abort();
        }
    } else if ("wmean" == calc_mode){
        if("gauss" == error_mode || "zero" == error_mode){
            long nsel = 0;
            int* mask_sel_arr = NULL;
            MxcsMath::GenWMean(ndata, array, array_err,
                               &val_proj, &val_proj_err,
                               &nsel, &mask_sel_arr);
            delete [] mask_sel_arr;
            if("zero" == error_mode){
                val_proj_err = 0.0;
            }
        } else {
            MxcsPrintErr("bad error_mode");
            abort();
        }

    } else if ("min" == calc_mode){
        long index = MxcsMath::GetLocMin(ndata, array);
        val_proj = array[index];
        if("gauss" == error_mode || "poisson" == error_mode){
            val_proj_err = array_err[index];
        } else if("zero" == error_mode) {
            val_proj_err = 0.0;
        } else {
            MxcsPrintErr("bad error_mode");
            abort();
        }
    } else if ("max" == calc_mode){
        long index = MxcsMath::GetLocMax(ndata, array);
        val_proj = array[index];
        if("gauss" == error_mode || "poisson" == error_mode){
            val_proj_err = array_err[index];
        } else if("zero" == error_mode) {
            val_proj_err = 0.0;
        } else {
            MxcsPrintErr("bad error_mode");
            abort();
        }
    } else {
        MxcsPrintErr("bad calc_mode");
        abort();
    }

    *val_proj_ptr = val_proj;
    *val_proj_err_ptr = val_proj_err;
}



void HistData2dOpe::GetHd2dMaskWithMargin(const HistDataNerr2d* const hd2d_mask,
                                          double xval_margin, double yval_margin,
                                          HistData2d* const hd2d_with_margin_out)
{
    if(xval_margin < 0.0 || yval_margin < 0.0){
        abort();
    }
    long nbin_x = hd2d_mask->GetNbinX();
    long nbin_y = hd2d_mask->GetNbinY();
    for(long ibin_x = 0; ibin_x < nbin_x; ibin_x ++){
        for(long ibin_y = 0; ibin_y < nbin_y; ibin_y ++){
            if(0 < hd2d_mask->GetOvalElm(ibin_x, ibin_y)){
                double xval = hd2d_mask->GetHi2d()->GetBinCenterXFromIbinX(ibin_x);
                double yval = hd2d_mask->GetHi2d()->GetBinCenterYFromIbinY(ibin_y);

                long ibin_x_lo = hd2d_with_margin_out->GetHi2d()->GetIbinXFromX(
                    MxcsMath::GetMax(xval - xval_margin,
                                     hd2d_with_margin_out->GetXvalLo()) );
                long ibin_x_up = hd2d_with_margin_out->GetHi2d()->GetIbinXFromX(
                    MxcsMath::GetMin(xval + xval_margin,
                                     hd2d_with_margin_out->GetXvalUp()) );
                long ibin_y_lo = hd2d_with_margin_out->GetHi2d()->GetIbinYFromY(
                    MxcsMath::GetMax(yval - yval_margin,
                                     hd2d_with_margin_out->GetYvalLo()) );
                long ibin_y_up = hd2d_with_margin_out->GetHi2d()->GetIbinYFromY(
                    MxcsMath::GetMin(yval + yval_margin,
                                     hd2d_with_margin_out->GetYvalUp()) );

                for(long ifill_x = ibin_x_lo; ifill_x <= ibin_x_up; ifill_x ++){
                    for(long ifill_y = ibin_y_lo; ifill_y <= ibin_y_up;
                        ifill_y ++){
                        hd2d_with_margin_out->SetOvalElm(ifill_x, ifill_y, 1.0);
                    }
                }
            }
        }
    }
}
