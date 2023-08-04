#ifndef MXCSTOOL_MXCSANALIB_HIST1D_OPE_H_
#define MXCSTOOL_MXCSANALIB_HIST1D_OPE_H_

#include "mxcs_data1d_ope.h"
#include "mxcs_hist1d_nerr.h"
#include "mxcs_hist1d_serr.h"

namespace HistData1dOpe
{
    HistData1d* const GenHd1dByLoad(string file);

    DataArray1d** const GenDa1dArrNerr(const HistData1d* const* const hd1d_arr,
                                       int narr);
    DataArray1d** const GenDa1dArrSerr(const HistData1d* const* const hd1d_arr,
                                       int narr);
    void DelHd1dArr(HistData1d** const hd1d_arr, int narr);

    int IsFormatSame(const HistData1d* const data1,
                     const HistData1d* const data2);
    int IsFormatSame(const HistData1d* const* const data_arr,
                     int nhist);
    
    // For one HistData1d
    void GetNot(const HistData1d* const in,
                HistDataNerr1d* const out);
    void GetNot(const HistData1d* const in,
                HistDataSerr1d* const out);
    
    void GetScale(const HistData1d* const in,
                  double scale, double offset,
                  HistDataNerr1d* const out);
    void GetScale(const HistData1d* const in,
                  double scale, double offset,
                  HistDataSerr1d* const out);

    // For two HistData1d
    void GetMin(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataNerr1d* const out);
    void GetMin(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataSerr1d* const out);
    
    void GetMax(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataNerr1d* const out);
    void GetMax(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataSerr1d* const out);
    
    void GetAdd(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataNerr1d* const out);
    void GetAdd(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataSerr1d* const out);
    
    void GetSub(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataNerr1d* const out);
    void GetSub(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataSerr1d* const out);
    
    void GetMul(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataNerr1d* const out);
    void GetMul(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataSerr1d* const out);
    
    int GetDiv(const HistData1d* const num,
               const HistData1d* const den,
               HistDataNerr1d* const mask_sel_out,
               HistDataNerr1d* const out);
    int GetDiv(const HistData1d* const num,
               const HistData1d* const den,
               HistDataNerr1d* const mask_sel_out,
               HistDataSerr1d* const out);
    
    void GetAMean(const HistData1d* const in1,
                  const HistData1d* const in2,
                  HistDataNerr1d* const out);
    void GetAMean(const HistData1d* const in1,
                  const HistData1d* const in2,
                  HistDataSerr1d* const out);
    
    int GetWMean(const HistData1d* const in1,
                 const HistData1d* const in2,
                 HistDataNerr1d* const mask_sel_out,
                 HistDataSerr1d* const out);

    int GetSubAddRatio(const HistData1d* const in1,
                       const HistData1d* const in2,
                       HistDataNerr1d* const mask_sel_out,
                       HistDataNerr1d* const out);

    int GetSubAddRatio(const HistData1d* const in1,
                       const HistData1d* const in2,
                       HistDataNerr1d* const mask_sel_out,
                       HistDataSerr1d* const out);
    
    // For N HistData1d
    void GetMin(const HistData1d* const* const in_arr,
                int narr,
                HistDataNerr1d* const out);
    void GetMin(const HistData1d* const* const in_arr,
                int narr,
                HistDataSerr1d* const out);
    
    void GetMax(const HistData1d* const* const in_arr,
                int narr,
                HistDataNerr1d* const out);
    void GetMax(const HistData1d* const* const in_arr,
                int narr,
                HistDataSerr1d* const out);
    
    void GetSum(const HistData1d* const* const in_arr,
                int narr,
                HistDataNerr1d* const out);
    void GetSum(const HistData1d* const* const in_arr,
                int narr,
                HistDataSerr1d* const out);
    
    void GetAMean(const HistData1d* const* const in_arr,
                  int narr,
                  HistDataNerr1d* const out);
    void GetAMean(const HistData1d* const* const in_arr,
                  int narr,
                  HistDataSerr1d* const out);
    
    int GetWMean(const HistData1d* const* const in_arr,
                 int narr,
                 HistDataNerr1d* const mask_sel_out,
                 HistDataSerr1d* const out);
    
    void GetVariance(const HistData1d* const* const in_arr,
                     int narr,
                     HistDataNerr1d* const out);
    void GetStddev(const HistData1d* const* const in_arr,
                   int narr,
                   HistDataNerr1d* const out);
    void GetUnbiasedVariance(const HistData1d* const* const in_arr,
                             int narr,
                             HistDataNerr1d* const out);
    void GetSqrtOfUnbiasedVariance(const HistData1d* const* const in_arr,
                                   int narr,
                                   HistDataNerr1d* const out);
    void GetRMS(const HistData1d* const* const in_arr,
                int narr,
                HistDataNerr1d* const out);
    void GetMedian(const HistData1d* const* const in_arr,
                   int narr,
                   HistDataNerr1d* const out);
                   
    void GetSumWithMask(const HistData1d* const* const in_arr,
                        const HistData1d* const* const mask_arr,
                        int narr,
                        HistDataNerr1d* const out);
    void GetSumWithMask(const HistData1d* const* const in_arr,
                        const HistData1d* const* const mask_arr,
                        int narr,
                        HistDataSerr1d* const out);
    
    void GetAMeanWithMask(const HistData1d* const* const in_arr,
                          const HistData1d* const* const mask_arr,
                          int narr,
                          HistDataNerr1d* const out);
    void GetAMeanWithMask(const HistData1d* const* const in_arr,
                          const HistData1d* const* const mask_arr,
                          int narr,
                          HistDataSerr1d* const out);
    
    int GetWMeanWithMask(const HistData1d* const* const in_arr,
                         const HistData1d* const* const mask_arr,
                         int narr,
                         HistDataNerr1d* const mask_sel_out,
                         HistDataSerr1d* const out);
  
    // residual
    void GetResValHd1d(const HistData1d* const data,
                       const MxcsFunc* const func,
                       const double* const par,
                       HistDataNerr1d* const out);
    void GetResValHd1d(const HistData1d* const data,
                       const MxcsFunc* const func,
                       const double* const par,
                       HistDataSerr1d* const out);
    
    void GetResValHd1d(const HistData1d* const data,
                       const HistDataNerr1d* const func,
                       HistDataNerr1d* const out);
    void GetResValHd1d(const HistData1d* const data,
                       const HistDataNerr1d* const func,
                       HistDataSerr1d* const out);

    void GetResRatioHd1d(const HistData1d* const data,
                         const MxcsFunc* const func,
                         const double* const par,
                         HistDataNerr1d* const out);
    void GetResRatioHd1d(const HistData1d* const data,
                         const MxcsFunc* const func,
                         const double* const par,
                         HistDataSerr1d* const out);
    
    void GetResRatioHd1d(const HistData1d* const data,
                         const HistDataNerr1d* const func,
                         HistDataNerr1d* const out);
    void GetResRatioHd1d(const HistData1d* const data,
                         const HistDataNerr1d* const func,
                         HistDataSerr1d* const out);

    void GetResChiHd1d(const HistData1d* const data,
                       const MxcsFunc* const func,
                       const double* const par,
                       HistDataSerr1d* const out);
    void GetResChiHd1d(const HistData1d* const data,
                       const HistDataNerr1d* const func,
                       HistDataSerr1d* const out);

   
    // power spectrum
    void GetPowSpec(const HistData1d* const in,
                    HistDataNerr1d* const out);
    void GetPowSpecLeahyNorm(const HistData1d* const in,
                             HistDataNerr1d* const out);
    void GetPowSpecNonfft(const HistData1d* const in,
                          HistDataNerr1d* const out);
    
    void GetPowSpecDecomp(long mbin, const HistData1d* const in,
                          HistDataNerr1d* const out);
    void GetPowSpecDecompNonfft(long mbin, const HistData1d* const in,
                                HistDataNerr1d* const out);
    void GetAutoCorr(const HistData1d* const in,
                     HistDataNerr1d* out);
    void GetCrossCorr(const HistData1d* const in1,
                      const HistData1d* const in2,
                      HistDataNerr1d* const out);
    
} // namespace HistData1dOpe

#endif // MXCSTOOL_MXCSANALIB_HIST1D_OPE_H_
