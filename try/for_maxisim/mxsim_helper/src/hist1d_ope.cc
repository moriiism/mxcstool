#include "mxcs_data1d_ope.h"
#include "mxcs_hist1d_ope.h"

DataArray1d** const HistData1dOpe::GenDa1dArrNerr(
    const HistData1d* const* const hd1d_arr,
    int narr)
{
    DataArray1d** da1d_arr = new DataArray1d* [narr];
    for(int iarr = 0; iarr < narr; iarr ++){
        da1d_arr[iarr] = new DataArrayNerr1d;
        da1d_arr[iarr]->Copy(hd1d_arr[iarr]->GetOvalArr());
    }
    return da1d_arr;
}

DataArray1d** const HistData1dOpe::GenDa1dArrSerr(
    const HistData1d* const* const hd1d_arr,
    int narr)
{
    DataArray1d** da1d_arr = new DataArray1d* [narr];
    for(int iarr = 0; iarr < narr; iarr ++){
        da1d_arr[iarr] = new DataArraySerr1d;
        da1d_arr[iarr]->Copy(hd1d_arr[iarr]->GetOvalArr());
    }
    return da1d_arr;
}

//DataArray1d** const HistData1dOpe::GenDa1dArrTerr(
//    const HistData1d* const* const hd1d_arr,
//    int narr)
//{
//    DataArray1d** da1d_arr = new DataArray1d* [narr];
//    for(int iarr = 0; iarr < narr; iarr ++){
//        da1d_arr[iarr] = new DataArrayTerr1d;
//        da1d_arr[iarr]->Copy(hd1d_arr[iarr]->GetOvalArr());
//    }
//    return da1d_arr;
//}

void HistData1dOpe::DelHd1dArr(HistData1d** const hd1d_arr, int narr)
{
    for(int iarr = 0; iarr < narr; iarr ++){
        delete hd1d_arr[iarr];
    }
    delete [] hd1d_arr;
}

int HistData1dOpe::IsFormatSame(const HistData1d* const data1,
                                const HistData1d* const data2)
{
    if(data1->GetNbinX() != data2->GetNbinX() ||
       fabs(data1->GetXvalLo() - data2->GetXvalLo()) > DBL_EPSILON ||
       fabs(data1->GetXvalUp() - data2->GetXvalUp()) > DBL_EPSILON ){
        MxcsPrintErr("format of data1 and data2 are diffenret.");
        char msg[kLineSize];
        sprintf(msg, "data1: (GetNbinX(), GetXvalLo(), GetXvalUp())"
                "= (%ld, %e, %e)",
                data1->GetNbinX(),
                data1->GetXvalLo(),
                data1->GetXvalUp());
        MxcsPrintErr(msg);
        sprintf(msg, "data2: (GetNbinX(), GetXvalLo(), GetXvalUp())"
                "= (%ld, %e, %e)",
                data2->GetNbinX(),
                data2->GetXvalLo(),
                data2->GetXvalUp());
        MxcsPrintErr(msg);
        abort();
    }
    return 1;
}

int HistData1dOpe::IsFormatSame(const HistData1d* const* const data_arr,
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
           fabs(data_arr[0]->GetXvalLo() - data_arr[ihist]->GetXvalLo())
           > DBL_EPSILON ||
           fabs(data_arr[0]->GetXvalUp() - data_arr[ihist]->GetXvalUp())
           > DBL_EPSILON ){
            char msg[kLineSize];
            sprintf(msg, "format of data_arr[0] and data_arr[%d] are diffenret",
                    ihist);
            MxcsPrintErr(msg);
            sprintf(msg, "data_arr[0]: (GetNbinX(), GetXvalLo(), GetXvalUp())"
                    "= (%ld, %e, %e)",
                    data_arr[0]->GetNbinX(),
                    data_arr[0]->GetXvalLo(),
                    data_arr[0]->GetXvalUp());
            MxcsPrintErr(msg);            
            sprintf(msg, "data_arr[%d]: (GetNbinX(), GetXvalLo(), GetXvalUp())"
                    "= (%ld, %e, %e)",
                    ihist,
                    data_arr[ihist]->GetNbinX(),
                    data_arr[ihist]->GetXvalLo(),
                    data_arr[ihist]->GetXvalUp());
            MxcsPrintErr(msg);            
            sprintf(
                msg,
                "data_arr[0]->GetXvalLo() - data_arr[%d]->GetXvalLo() = %e\n",
                ihist,
                fabs(data_arr[0]->GetXvalLo()
                     - data_arr[ihist]->GetXvalLo()));
            MxcsPrintErr(msg);            
            sprintf(
                msg,
                "data_arr[0]->GetXvalUp() - data_arr[%d]->GetXvalUp() = %e\n",
                ihist,
                fabs(data_arr[0]->GetXvalUp() - data_arr[ihist]->GetXvalUp()));
            abort();
        }
    }
    return 1;
}

// For one HistData1d
void HistData1dOpe::GetNot(const HistData1d* const in,
                           HistDataNerr1d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetNot(in->GetOvalArr(),
                           da1d);
    out->Init(in->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}

void HistData1dOpe::GetNot(const HistData1d* const in,
                           HistDataSerr1d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetNot(in->GetOvalArr(),
                           da1d);
    out->Init(in->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}

void HistData1dOpe::GetScale(const HistData1d* const in,
                             double scale, double offset,
                             HistDataNerr1d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetScale(in->GetOvalArr(),
                             scale, offset,
                             da1d);
    out->Init(in->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}

   
void HistData1dOpe::GetScale(const HistData1d* const in,
                             double scale, double offset,
                             HistDataSerr1d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetScale(in->GetOvalArr(),
                             scale, offset,
                             da1d);
    out->Init(in->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}

    
// For two HistData1d
void HistData1dOpe::GetMin(const HistData1d* const in1,
                           const HistData1d* const in2,
                           HistDataNerr1d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMin(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData1dOpe::GetMin(const HistData1d* const in1,
                           const HistData1d* const in2,
                           HistDataSerr1d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMin(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData1dOpe::GetMax(const HistData1d* const in1,
                           const HistData1d* const in2,
                           HistDataNerr1d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMax(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData1dOpe::GetMax(const HistData1d* const in1,
                           const HistData1d* const in2,
                           HistDataSerr1d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMax(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
   
void HistData1dOpe::GetAdd(const HistData1d* const in1,
                           const HistData1d* const in2,
                           HistDataNerr1d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetAdd(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData1dOpe::GetAdd(const HistData1d* const in1,
                           const HistData1d* const in2,
                           HistDataSerr1d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetAdd(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
void HistData1dOpe::GetSub(const HistData1d* const in1,
                           const HistData1d* const in2,
                           HistDataNerr1d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetSub(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData1dOpe::GetSub(const HistData1d* const in1,
                           const HistData1d* const in2,
                           HistDataSerr1d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetSub(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
void HistData1dOpe::GetMul(const HistData1d* const in1,
                           const HistData1d* const in2,
                           HistDataNerr1d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMul(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    

void HistData1dOpe::GetMul(const HistData1d* const in1,
                           const HistData1d* const in2,
                           HistDataSerr1d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMul(in1->GetOvalArr(),
                           in2->GetOvalArr(),
                           da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
int HistData1dOpe::GetDiv(const HistData1d* const num,
                          const HistData1d* const den,
                          HistDataNerr1d* const mask_sel_out,
                          HistDataNerr1d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetDiv(num->GetOvalArr(),
                                     den->GetOvalArr(),
                                     da1d_mask,
                                     da1d);
    out->Init(num->GetHi1d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(num->GetHi1d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    
int HistData1dOpe::GetDiv(const HistData1d* const num,
                          const HistData1d* const den,
                          HistDataNerr1d* const mask_sel_out,
                          HistDataSerr1d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetDiv(num->GetOvalArr(),
                                     den->GetOvalArr(),
                                     da1d_mask,
                                     da1d);
    out->Init(num->GetHi1d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(num->GetHi1d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    
    
void HistData1dOpe::GetAMean(const HistData1d* const in1,
                             const HistData1d* const in2,
                             HistDataNerr1d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetAMean(in1->GetOvalArr(),
                             in2->GetOvalArr(),
                             da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
void HistData1dOpe::GetAMean(const HistData1d* const in1,
                             const HistData1d* const in2,
                             HistDataSerr1d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetAMean(in1->GetOvalArr(),
                             in2->GetOvalArr(),
                             da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    delete da1d;
}
    
    
int HistData1dOpe::GetWMean(const HistData1d* const in1,
                            const HistData1d* const in2,
                            HistDataNerr1d* const mask_sel_out,
                            HistDataSerr1d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetWMean(in1->GetOvalArr(),
                                       in2->GetOvalArr(),
                                       da1d_mask,
                                       da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in1->GetHi1d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    

int HistData1dOpe::GetSubAddRatio(const HistData1d* const in1,
                                  const HistData1d* const in2,
                                  HistDataNerr1d* const mask_sel_out,
                                  HistDataNerr1d* const out)
{
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetSubAddRatio(in1->GetOvalArr(),
                                             in2->GetOvalArr(),
                                             da1d_mask,
                                             da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in1->GetHi1d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    

int HistData1dOpe::GetSubAddRatio(const HistData1d* const in1,
                                  const HistData1d* const in2,
                                  HistDataNerr1d* const mask_sel_out,
                                  HistDataSerr1d* const out)
{
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetSubAddRatio(in1->GetOvalArr(),
                                             in2->GetOvalArr(),
                                             da1d_mask,
                                             da1d);
    out->Init(in1->GetHi1d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in1->GetHi1d());
    mask_sel_out->SetOvalArr(da1d_mask);
    delete da1d;
    delete da1d_mask;
    return ret;
}
    

// For N HistData1d
void HistData1dOpe::GetMin(const HistData1d* const* const in_arr,
                           int narr,
                           HistDataNerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMin(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData1dOpe::GetMin(const HistData1d* const* const in_arr,
                           int narr,
                           HistDataSerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMin(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}

   
void HistData1dOpe::GetMax(const HistData1d* const* const in_arr,
                           int narr,
                           HistDataNerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMax(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData1dOpe::GetMax(const HistData1d* const* const in_arr,
                           int narr,
                           HistDataSerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetMax(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}

void HistData1dOpe::GetSum(const HistData1d* const* const in_arr,
                           int narr,
                           HistDataNerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetSum(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData1dOpe::GetSum(const HistData1d* const* const in_arr,
                           int narr,
                           HistDataSerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetSum(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
    
void HistData1dOpe::GetAMean(const HistData1d* const* const in_arr,
                             int narr,
                             HistDataNerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetAMean(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData1dOpe::GetAMean(const HistData1d* const* const in_arr,
                             int narr,
                             HistDataSerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetAMean(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);

    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
    
int HistData1dOpe::GetWMean(const HistData1d* const* const in_arr,
                            int narr,
                            HistDataNerr1d* const mask_sel_out,
                            HistDataSerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask_sel = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetWMean(da1d_arr, narr, da1d_mask_sel, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in_arr[0]->GetHi1d());
    mask_sel_out->SetOvalArr(da1d_mask_sel);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
    delete da1d_mask_sel;
    return ret;
}
    
    
void HistData1dOpe::GetVariance(const HistData1d* const* const in_arr,
                                int narr,
                                HistDataNerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetVariance(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData1dOpe::GetStddev(const HistData1d* const* const in_arr,
                              int narr,
                              HistDataNerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetStddev(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData1dOpe::GetUnbiasedVariance(const HistData1d* const* const in_arr,
                                        int narr,
                                        HistDataNerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetUnbiasedVariance(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData1dOpe::GetSqrtOfUnbiasedVariance(
    const HistData1d* const* const in_arr,
    int narr,
    HistDataNerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetSqrtOfUnbiasedVariance(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData1dOpe::GetRMS(const HistData1d* const* const in_arr,
                           int narr,
                           HistDataNerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetRMS(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
void HistData1dOpe::GetMedian(const HistData1d* const* const in_arr,
                              int narr,
                              HistDataNerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetMedian(da1d_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    delete da1d;
}
    
                   
void HistData1dOpe::GetSumWithMask(const HistData1d* const* const in_arr,
                                   const HistData1d* const* const mask_arr,
                                   int narr,
                                   HistDataNerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetSumWithMask(da1d_arr, da1d_mask_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
}
    
void HistData1dOpe::GetSumWithMask(const HistData1d* const* const in_arr,
                                   const HistData1d* const* const mask_arr,
                                   int narr,
                                   HistDataSerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetSumWithMask(da1d_arr, da1d_mask_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
}
    
    
void HistData1dOpe::GetAMeanWithMask(const HistData1d* const* const in_arr,
                                     const HistData1d* const* const mask_arr,
                                     int narr,
                                     HistDataNerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrNerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);
    DataArrayNerr1d* da1d = new DataArrayNerr1d;
    DataArray1dOpe::GetAMeanWithMask(da1d_arr, da1d_mask_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
}
    
void HistData1dOpe::GetAMeanWithMask(const HistData1d* const* const in_arr,
                                     const HistData1d* const* const mask_arr,
                                     int narr,
                                     HistDataSerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArray1dOpe::GetAMeanWithMask(da1d_arr, da1d_mask_arr, narr, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
}
    
    
int HistData1dOpe::GetWMeanWithMask(const HistData1d* const* const in_arr,
                                    const HistData1d* const* const mask_arr,
                                    int narr,
                                    HistDataNerr1d* const mask_sel_out,
                                    HistDataSerr1d* const out)
{
    DataArray1d** da1d_arr = GenDa1dArrSerr(in_arr, narr);
    DataArray1d** da1d_mask_arr = GenDa1dArrNerr(mask_arr, narr);    
    DataArraySerr1d* da1d = new DataArraySerr1d;
    DataArrayNerr1d* da1d_mask_sel = new DataArrayNerr1d;
    int ret = DataArray1dOpe::GetWMeanWithMask(da1d_arr, da1d_mask_arr,
                                               narr, da1d_mask_sel, da1d);
    out->Init(in_arr[0]->GetHi1d());
    out->SetOvalArr(da1d);
    mask_sel_out->Init(in_arr[0]->GetHi1d());
    mask_sel_out->SetOvalArr(da1d_mask_sel);
    DataArray1dOpe::DelDa1dArr(da1d_arr, narr);
    DataArray1dOpe::DelDa1dArr(da1d_mask_arr, narr);
    delete da1d;
    delete da1d_mask_sel;
    return ret;
}


void HistData1dOpe::GetResValHd1d(const HistData1d* const data,
                                  const MxcsFunc* const func,
                                  const double* const par,
                                  HistDataNerr1d* const out)
{
    long nbin = data->GetNbinX();
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval[1];
        xval[0] = data->GetBinCenter(ibin);
        oval_res[ibin] = data->GetOvalElm(ibin) - func->Eval(xval, par);
    }
    out->Init(nbin, data->GetXvalLo(), data->GetXvalUp());
    out->SetOvalArr(nbin, oval_res);
    delete [] oval_res;
}


void HistData1dOpe::GetResValHd1d(const HistData1d* const data,
                                  const MxcsFunc* const func,
                                  const double* const par,
                                  HistDataSerr1d* const out)
{
    long nbin = data->GetNbinX();
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval[1];
        xval[0] = data->GetBinCenter(ibin);
        oval_res[ibin] = data->GetOvalElm(ibin) - func->Eval(xval, par);
        oval_res_serr[ibin] = data->GetOvalSerrElm(ibin);
    }
    out->Init(nbin, data->GetXvalLo(), data->GetXvalUp());
    out->SetOvalArr(nbin, oval_res);
    out->SetOvalSerrArr(nbin, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}


void HistData1dOpe::GetResValHd1d(const HistData1d* const data,
                                  const HistDataNerr1d* const func,
                                  HistDataNerr1d* const out)
{
    long nbin = data->GetNbinX();
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        oval_res[ibin] = data->GetOvalElm(ibin) - func->GetOvalElm(ibin);
    }
    out->Init(nbin, data->GetXvalLo(), data->GetXvalUp());
    out->SetOvalArr(nbin, oval_res);
    delete [] oval_res;
}


void HistData1dOpe::GetResValHd1d(const HistData1d* const data,
                                  const HistDataNerr1d* const func,
                                  HistDataSerr1d* const out)
{
    long nbin = data->GetNbinX();
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval = data->GetBinCenter(ibin);
        long ibin_func = func->GetIbin(xval);
        oval_res[ibin] = data->GetOvalElm(ibin) - func->GetOvalElm(ibin_func);
        oval_res_serr[ibin] = data->GetOvalSerrElm(ibin);
    }
    out->Init(nbin, data->GetXvalLo(), data->GetXvalUp());
    out->SetOvalArr(nbin, oval_res);
    out->SetOvalSerrArr(nbin, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}

void HistData1dOpe::GetResRatioHd1d(const HistData1d* const data,
                                    const MxcsFunc* const func,
                                    const double* const par,
                                    HistDataNerr1d* const out)
{
    long nbin = data->GetNbinX();
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval[1];
        xval[0] = data->GetBinCenter(ibin);
        if( fabs(func->Eval(xval, par)) > DBL_EPSILON){
            oval_res[ibin] = (data->GetOvalElm(ibin) - func->Eval(xval, par))
                / func->Eval(xval, par);
        } else {
            oval_res[ibin] = 0.0;
        }
    }
    out->Init(nbin, data->GetXvalLo(), data->GetXvalUp());
    out->SetOvalArr(nbin, oval_res);
    delete [] oval_res;
}


void HistData1dOpe::GetResRatioHd1d(const HistData1d* const data,
                                    const MxcsFunc* const func,
                                    const double* const par,
                                    HistDataSerr1d* const out)
{
    long nbin = data->GetNbinX();
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval[1];
        xval[0] = data->GetBinCenter(ibin);
        if( fabs(func->Eval(xval, par)) > DBL_EPSILON){
            oval_res[ibin] = (data->GetOvalElm(ibin) - func->Eval(xval, par))
                / func->Eval(xval, par);
            oval_res_serr[ibin] = fabs(data->GetOvalSerrElm(ibin)
                                       / func->Eval(xval, par));
        } else {
            oval_res[ibin] = 0.0;
            oval_res_serr[ibin] = 0.0;
        }
    }

    out->Init(nbin, data->GetXvalLo(), data->GetXvalUp());
    out->SetOvalArr(nbin, oval_res);
    out->SetOvalSerrArr(nbin, oval_res_serr);
    
    delete [] oval_res;
    delete [] oval_res_serr;
}



void HistData1dOpe::GetResRatioHd1d(const HistData1d* const data,
                                    const HistDataNerr1d* const func,
                                    HistDataNerr1d* const out)
{
    long nbin = data->GetNbinX();
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        if( fabs(func->GetOvalElm(ibin)) > DBL_EPSILON){
            oval_res[ibin] = (data->GetOvalElm(ibin) - func->GetOvalElm(ibin))
                / func->GetOvalElm(ibin);
        } else {
            oval_res[ibin] = 0.0;
        }
    }
    out->Init(nbin, data->GetXvalLo(), data->GetXvalUp());
    out->SetOvalArr(nbin, oval_res);
    delete [] oval_res;
}

void HistData1dOpe::GetResRatioHd1d(const HistData1d* const data,
                                    const HistDataNerr1d* const func,
                                    HistDataSerr1d* const out)
{
    long nbin = data->GetNbinX();
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval = data->GetBinCenter(ibin);
        long ibin_func = func->GetIbin(xval);
        if( fabs(func->GetOvalElm(ibin_func)) > DBL_EPSILON){
            oval_res[ibin]
                = (data->GetOvalElm(ibin) - func->GetOvalElm(ibin_func))
                / func->GetOvalElm(ibin_func);
            oval_res_serr[ibin] = fabs(data->GetOvalSerrElm(ibin)
                                       / func->GetOvalElm(ibin_func));
        } else {
            oval_res[ibin] = 0.0;
            oval_res_serr[ibin] = 0.0;
        }
    }
    out->Init(nbin, data->GetXvalLo(), data->GetXvalUp());
    out->SetOvalArr(nbin, oval_res);
    out->SetOvalSerrArr(nbin, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}

void HistData1dOpe::GetResChiHd1d(const HistData1d* const data,
                                  const MxcsFunc* const func,
                                  const double* const par,
                                  HistDataSerr1d* const out)
{
    long nbin = data->GetNbinX();
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval[1];
        xval[0] = data->GetBinCenter(ibin);
        if( fabs( data->GetOvalSerrElm(ibin) ) > DBL_EPSILON){
            oval_res[ibin] = ( data->GetOvalElm(ibin) - func->Eval(xval, par) )
                / data->GetOvalSerrElm(ibin);
            oval_res_serr[ibin] = 1.0;
        } else {
            oval_res[ibin] = 0.0;
            oval_res_serr[ibin] = 0.0;
        }
    }
    out->Init(nbin, data->GetXvalLo(), data->GetXvalUp());
    out->SetOvalArr(nbin, oval_res);
    out->SetOvalSerrArr(nbin, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}

void HistData1dOpe::GetResChiHd1d(const HistData1d* const data,
                                  const HistDataNerr1d* const func,
                                  HistDataSerr1d* const out)
{
    long nbin = data->GetNbinX();
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval = data->GetBinCenter(ibin);
        long ibin_func = func->GetIbin(xval);
        if( fabs( data->GetOvalSerrElm(ibin) ) > DBL_EPSILON){
            oval_res[ibin]
                = (data->GetOvalElm(ibin) - func->GetOvalElm(ibin_func))
                / data->GetOvalSerrElm(ibin);
            oval_res_serr[ibin] = 1.0;
        } else {
            oval_res[ibin] = 0.0;
            oval_res_serr[ibin] = 0.0;
        }
    }
    out->Init(nbin, data->GetXvalLo(), data->GetXvalUp());
    out->SetOvalArr(nbin, oval_res);
    out->SetOvalSerrArr(nbin, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}

// power spec

void HistData1dOpe::GetPowSpecNonfft(const HistData1d* const in,
                                     HistDataNerr1d* const out)
{
    long nbin = in->GetNbinX();
    double tbinfwidth = in->GetXvalBinWidth();
  
    double* out_real = new double [nbin];
    double* out_imag = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        out_real[ibin] = 0.0;
        out_imag[ibin] = 0.0;
        for(long jbin = 0; jbin < nbin; jbin++){
            out_real[ibin] += cos(2 * M_PI * jbin * ibin /(nbin))
                * in->GetOvalElm(jbin);
            out_imag[ibin] += sin(2 * M_PI * jbin * ibin /(nbin))
                * in->GetOvalElm(jbin);
        }
    }

    // calculate Power Spectrum
    double* freq  = new double [nbin + 1];
    double* power = new double [nbin + 1];
    double nbin_pow2 = pow(nbin, 2);
    freq[0] = 0.0;
    power[0] = (pow(out_real[0], 2) + pow(out_imag[0], 2)) / nbin_pow2;
    for(long itime = 1; itime < nbin; itime++){
        freq[itime]  = itime / (nbin * tbinfwidth);
        power[itime] = 2.0 * (pow(out_real[itime], 2) + pow(out_imag[itime], 2))
            / nbin_pow2;
    }
    freq[nbin] = 1.0 / (2.0 * tbinfwidth);
    power[nbin] = (pow(out_real[nbin], 2) + pow(out_imag[nbin], 2)) / nbin_pow2;

    double xval_lo = -0.5 / (nbin * tbinfwidth);
    double xval_up = (nbin + 0.5) / (nbin * tbinfwidth);
    out->Init(nbin + 1, xval_lo, xval_up);
    out->SetOvalArr(nbin + 1, power);

    delete [] out_real;
    delete [] out_imag;
    delete [] freq;
    delete [] power;
}

