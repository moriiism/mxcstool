#include "mxcs_data1d_ope.h"

DataArray1d* const DataArray1dOpe::GenDa1dByLoad(string file, string format)
{
    DataArray1d* da1d = NULL;
    if("x" == format){
        da1d = new DataArrayNerr1d;
    } else if("x,xe" == format){
        da1d = new DataArraySerr1d;
    } else {
        MxcsPrintErr("bad format");
        abort();
    }
    da1d->Load(file);
    return da1d;
}

void DataArray1dOpe::DelDa1dArr(DataArray1d** const da1d_arr, int narr)
{
    for(int iarr = 0; iarr < narr; iarr ++){
        delete da1d_arr[iarr];
    }
    delete [] da1d_arr;
}

// For one DataArray1d
void DataArray1dOpe::GetNot(const DataArray1d* const data_array,
                            DataArray1d* const data_array_out)
{
    long ndata = data_array->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double ans = MxcsMath::Not( data_array->GetValElm(idata) );
        data_array_out->SetValElm(idata, ans);
    }
}

void DataArray1dOpe::GetScale(const DataArray1d* const data_array,
                              double scale, double offset,
                              DataArrayNerr1d* const data_array_out)
{
    long ndata = data_array->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = scale * data_array->GetValElm(idata) + offset;
        data_array_out->SetValElm(idata, val);
    }
}

void DataArray1dOpe::GetScale(const DataArray1d* const data_array,
                              double scale, double offset,
                              DataArraySerr1d* const data_array_out)
{
    long ndata = data_array->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = 0.0;
        double val_serr = 0.0;
        MxcsMath::GetScaled(data_array->GetValElm(idata),
                            data_array->GetValSerrElm(idata),
                            scale, offset,
                            &val, &val_serr);
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);
    }
}

// For two DataArray1d

void DataArray1dOpe::GetMin(const DataArray1d* const data_array1,
                            const DataArray1d* const data_array2,
                            DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = MxcsMath::GetMin(data_array1->GetValElm(idata),
                                      data_array2->GetValElm(idata));
        data_array_out->SetValElm(idata, val);
    }
}

void DataArray1dOpe::GetMin(const DataArray1d* const data_array1,
                            const DataArray1d* const data_array2,
                            DataArraySerr1d* const data_array_out)
{
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        int index  = MxcsMath::GetLocMin(data_array1->GetValElm(idata),
                                         data_array2->GetValElm(idata));
        double val = 0.0;
        double val_serr = 0.0;
        if(0 == index){
            val      = data_array1->GetValElm(idata);
            val_serr = data_array1->GetValSerrElm(idata);
        } else if (1 == index){
            val      = data_array2->GetValElm(idata);
            val_serr = data_array2->GetValSerrElm(idata);
        } else {
            abort();
        }
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);
    }
}

void DataArray1dOpe::GetMax(const DataArray1d* const data_array1,
                            const DataArray1d* const data_array2,
                            DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = MxcsMath::GetMax(data_array1->GetValElm(idata),
                                      data_array2->GetValElm(idata));
        data_array_out->SetValElm(idata, val);
    }
}

void DataArray1dOpe::GetMax(const DataArray1d* const data_array1,
                            const DataArray1d* const data_array2,
                            DataArraySerr1d* const data_array_out)
{
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        int index  = MxcsMath::GetLocMax(data_array1->GetValElm(idata),
                                         data_array2->GetValElm(idata));
        double val = 0.0;
        double val_serr = 0.0;
        if(0 == index){
            val      = data_array1->GetValElm(idata);
            val_serr = data_array1->GetValSerrElm(idata);
        } else if (1 == index){
            val      = data_array2->GetValElm(idata);
            val_serr = data_array2->GetValSerrElm(idata);
        } else {
            abort();
        }
        data_array_out->SetValElm(idata, val);        
        data_array_out->SetValSerrElm(idata, val_serr);
    }
}

void DataArray1dOpe::GetAdd(const DataArray1d* const data_array1,
                            const DataArray1d* const data_array2,
                            DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = data_array1->GetValElm(idata)
            + data_array2->GetValElm(idata);
        data_array_out->SetValElm(idata, val);
    }
}

void DataArray1dOpe::GetAdd(const DataArray1d* const data_array1,
                            const DataArray1d* const data_array2,
                            DataArraySerr1d* const data_array_out)
{
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = 0.0;
        double val_serr = 0.0;
        MxcsMath::GetAdd(data_array1->GetValElm(idata),
                         data_array1->GetValSerrElm(idata),
                         data_array2->GetValElm(idata),
                         data_array2->GetValSerrElm(idata),
                         &val, &val_serr);
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);
    }
}

void DataArray1dOpe::GetSub(const DataArray1d* const data_array1,
                            const DataArray1d* const data_array2,
                            DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = data_array1->GetValElm(idata)
            - data_array2->GetValElm(idata);
        data_array_out->SetValElm(idata, val);
    }
}


void DataArray1dOpe::GetSub(const DataArray1d* const data_array1,
                            const DataArray1d* const data_array2,
                            DataArraySerr1d* const data_array_out)
{
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = 0.0;
        double val_serr = 0.0;
        MxcsMath::GetSub(data_array1->GetValElm(idata),
                         data_array1->GetValSerrElm(idata),
                         data_array2->GetValElm(idata),
                         data_array2->GetValSerrElm(idata),
                         &val, &val_serr);
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);
    }
}

void DataArray1dOpe::GetMul(const DataArray1d* const data_array1,
                            const DataArray1d* const data_array2,
                            DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = data_array1->GetValElm(idata)
            * data_array2->GetValElm(idata);
        data_array_out->SetValElm(idata, val);
    }
}

void DataArray1dOpe::GetMul(const DataArray1d* const data_array1,
                            const DataArray1d* const data_array2,
                            DataArraySerr1d* const data_array_out)
{
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = 0.0;
        double val_serr = 0.0;
        MxcsMath::GetMul(data_array1->GetValElm(idata),
                         data_array1->GetValSerrElm(idata),
                         data_array2->GetValElm(idata),
                         data_array2->GetValSerrElm(idata),
                         &val, &val_serr);
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);
    }
}

int DataArray1dOpe::GetDiv(const DataArray1d* const data_array_num,
                           const DataArray1d* const data_array_den,
                           DataArrayNerr1d* const mask_sel_array_out,
                           DataArrayNerr1d* const data_array_out)
{
    int status = kRetNormal;
    IsFormatSame(data_array_num, data_array_den);
    long ndata = data_array_num->GetNdata();
    mask_sel_array_out->Init(ndata);
    data_array_out->Init(ndata);
    long num_bad = 0;
    for(long idata = 0; idata < ndata; idata++){
        double val = 0.0;
        if ( fabs( data_array_den->GetValElm(idata) ) > DBL_EPSILON ){
            mask_sel_array_out->SetValElm(idata, 1);
            val = data_array_num->GetValElm(idata)
                / data_array_den->GetValElm(idata);
        } else {
            num_bad ++;
            val = 0.0;
        }
        data_array_out->SetValElm(idata, val);
    }

    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}


int DataArray1dOpe::GetDiv(const DataArray1d* const data_array_num,
                           const DataArray1d* const data_array_den,
                           DataArrayNerr1d* const mask_sel_array_out,
                           DataArraySerr1d* const data_array_out)
{
    int status = kRetNormal;    
    IsFormatSame(data_array_num, data_array_den);
    long ndata = data_array_num->GetNdata();
    mask_sel_array_out->Init(ndata);    
    data_array_out->Init(ndata);
    long num_bad = 0;
    for(long idata = 0; idata < ndata; idata++){
        double val = 0.0;
        double val_serr = 0.0;
        int ret = MxcsMath::GetDiv(data_array_num->GetValElm(idata),
                                   data_array_num->GetValSerrElm(idata),
                                   data_array_den->GetValElm(idata),
                                   data_array_den->GetValSerrElm(idata),
                                   &val, &val_serr);
        if(kRetNormal == ret){
            mask_sel_array_out->SetValElm(idata, 1);
        } else {
            num_bad ++;
            mask_sel_array_out->SetValElm(idata, 0);
        }
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);
    }

    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}

void DataArray1dOpe::GetAMean(const DataArray1d* const data_array1,
                              const DataArray1d* const data_array2,
                              DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = MxcsMath::GetAMean(data_array1->GetValElm(idata),
                                        data_array2->GetValElm(idata));
        data_array_out->SetValElm(idata, val);
    }
}

void DataArray1dOpe::GetAMean(const DataArray1d* const data_array1,
                              const DataArray1d* const data_array2,
                              DataArraySerr1d* const data_array_out)
{
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double amean = 0.0;
        double amean_err = 0.0;
        MxcsMath::GetAMean(data_array1->GetValElm(idata),
                           data_array1->GetValSerrElm(idata),
                           data_array2->GetValElm(idata),
                           data_array2->GetValSerrElm(idata),
                           &amean, &amean_err);
        data_array_out->SetValElm(idata, amean);
        data_array_out->SetValSerrElm(idata, amean_err);
    }
}


int DataArray1dOpe::GetWMean(const DataArray1d* const data_array1,
                             const DataArray1d* const data_array2,
                             DataArrayNerr1d* const mask_sel_array_out,
                             DataArraySerr1d* const data_array_out)
{
    int status = kRetNormal;    
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    mask_sel_array_out->Init(ndata);
    data_array_out->Init(ndata);
    long num_bad = 0;
    for(long idata = 0; idata < ndata; idata++){
        double val = 0.0;
        double val_serr = 0.0;
        int ret = MxcsMath::GetWMean(data_array1->GetValElm(idata),
                                     data_array1->GetValSerrElm(idata),
                                     data_array2->GetValElm(idata),
                                     data_array2->GetValSerrElm(idata),
                                     &val, &val_serr);
        if(kRetNormal == ret){
            mask_sel_array_out->SetValElm(idata, 1);
        } else {
            num_bad ++;
            mask_sel_array_out->SetValElm(idata, 0);
        }
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);
    }

    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}


int DataArray1dOpe::GetSubAddRatio(const DataArray1d* const data_array1,
                                   const DataArray1d* const data_array2,
                                   DataArrayNerr1d* const mask_sel_array_out,
                                   DataArrayNerr1d* const data_array_out)
{
    int status = kRetNormal;    
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    mask_sel_array_out->Init(ndata);
    data_array_out->Init(ndata);
    long num_bad = 0;
    for(long idata = 0; idata < ndata; idata++){
        double val1 = data_array1->GetValElm(idata);
        double val2 = data_array2->GetValElm(idata);
        double ans = 0.0;
        if ( fabs( val1 + val2 ) > DBL_EPSILON ){
            ans = (val1 - val2) / (val1 + val2);
            mask_sel_array_out->SetValElm(idata, 1);            
        } else {
            num_bad ++;
            ans = 0.0;
            mask_sel_array_out->SetValElm(idata, 0);
        }
        data_array_out->SetValElm(idata, ans);
    }
    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}

int DataArray1dOpe::GetSubAddRatio(const DataArray1d* const data_array1,
                                   const DataArray1d* const data_array2,
                                   DataArrayNerr1d* const mask_sel_array_out,
                                   DataArraySerr1d* const data_array_out)
{
    int status = kRetNormal;
    IsFormatSame(data_array1, data_array2);
    long ndata = data_array1->GetNdata();
    mask_sel_array_out->Init(ndata);    
    data_array_out->Init(ndata);
    long num_bad = 0;
    for(long idata = 0; idata < ndata; idata++){
        double val1     = data_array1->GetValElm(idata);
        double val1_err = data_array1->GetValSerrElm(idata);
        double val2     = data_array2->GetValElm(idata);
        double val2_err = data_array2->GetValSerrElm(idata);
        double ans = 0.0;
        double ans_err = 0.0;
        int ret = MxcsMath::GetSubAddRatio(val1, val1_err, val2, val2_err,
                                           &ans, &ans_err);
        if(kRetNormal == ret){
            mask_sel_array_out->SetValElm(idata, 1);
        } else {
            num_bad ++;
            mask_sel_array_out->SetValElm(idata, 0);
        }
        data_array_out->SetValElm(idata, ans);
        data_array_out->SetValSerrElm(idata, ans_err);
    }
    
    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}


//// For N DataArray1d

void DataArray1dOpe::GetMin(const DataArray1d* const* const data_array_arr,
                            int ndata_array,
                            DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp = new double [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
        }
        double val = MxcsMath::GetMin(ndata_array, val_arr_tmp);
        data_array_out->SetValElm(idata, val);
        delete [] val_arr_tmp;
    }
}

void DataArray1dOpe::GetMin(const DataArray1d* const* const data_array_arr,
                            int ndata_array,
                            DataArraySerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp = new double [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
        }
        int index = MxcsMath::GetLocMin(ndata_array, val_arr_tmp);
        double val      = data_array_arr[index]->GetValElm(idata);
        double val_serr = data_array_arr[index]->GetValSerrElm(idata);
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);
        delete [] val_arr_tmp;
    }
}

void DataArray1dOpe::GetMax(const DataArray1d* const* const data_array_arr,
                            int ndata_array,
                            DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp = new double [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
        }
        double val = MxcsMath::GetMax(ndata_array, val_arr_tmp);
        data_array_out->SetValElm(idata, val);
        delete [] val_arr_tmp;
    }
}


void DataArray1dOpe::GetMax(const DataArray1d* const* const data_array_arr,
                            int ndata_array,
                            DataArraySerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp = new double [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
        }
        int index = MxcsMath::GetLocMax(ndata_array, val_arr_tmp);
        double val      = data_array_arr[index]->GetValElm(idata);
        double val_serr = data_array_arr[index]->GetValSerrElm(idata);
        data_array_out->SetValElm(idata, val);        
        data_array_out->SetValSerrElm(idata, val_serr);
        delete [] val_arr_tmp;
    }
}

void DataArray1dOpe::GetSum(const DataArray1d* const* const data_array_arr,
                            int ndata_array,
                            DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp = new double [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
        }
        double val = MxcsMath::GetSum(ndata_array, val_arr_tmp);
        data_array_out->SetValElm(idata, val);
        delete [] val_arr_tmp;
    }
}


void DataArray1dOpe::GetSum(const DataArray1d* const* const data_array_arr,
                            int ndata_array,
                            DataArraySerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp  = new double [ndata_array];
        double* val_err_arr_tmp  = new double [ndata_array];  
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
            val_err_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValSerrElm(idata);
        }
        double val = 0.0;
        double val_serr = 0.0;
        MxcsMath::GetSum(ndata_array,
                         val_arr_tmp,
                         val_err_arr_tmp,
                         &val,
                         &val_serr);
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);
        delete [] val_arr_tmp;
        delete [] val_err_arr_tmp;
    }
}

void DataArray1dOpe::GetAMean(const DataArray1d* const* const data_array_arr,
                              int ndata_array,
                              DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp = new double [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
        }
        double val = MxcsMath::GetAMean(ndata_array, val_arr_tmp);
        data_array_out->SetValElm(idata, val);
        delete [] val_arr_tmp;
    }
}

void DataArray1dOpe::GetAMean(const DataArray1d* const* const data_array_arr,
                              int ndata_array,
                              DataArraySerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp     = new double [ndata_array];
        double* val_err_arr_tmp = new double [ndata_array];        
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
            val_err_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValSerrElm(idata);
        }
        double amean = 0.0;
        double amean_err = 0.0;
        MxcsMath::GetAMean(ndata_array, val_arr_tmp, val_err_arr_tmp,
                           &amean, &amean_err);
        data_array_out->SetValElm(idata, amean);
        data_array_out->SetValSerrElm(idata, amean_err);
        delete [] val_arr_tmp;
        delete [] val_err_arr_tmp;
    }
}

int DataArray1dOpe::GetWMean(const DataArray1d* const* const data_array_arr,
                             int ndata_array,
                             DataArrayNerr1d* const mask_sel_array_out,
                             DataArraySerr1d* const data_array_out)
{
    int status = kRetNormal;
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    mask_sel_array_out->Init(ndata);
    data_array_out->Init(ndata);
    long num_bad = 0;
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp  = new double [ndata_array];
        double* val_err_arr_tmp  = new double [ndata_array];  
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
            val_err_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValSerrElm(idata);
        }
        double val = 0.0;
        double val_serr = 0.0;
        long nsel = 0;
        int* mask_sel_arr = NULL;
        int ret = MxcsMath::GenWMean(ndata_array,
                                     val_arr_tmp,
                                     val_err_arr_tmp,
                                     &val,
                                     &val_serr,
                                     &nsel, &mask_sel_arr);
        if(kRetNormal == ret){
            mask_sel_array_out->SetValElm(idata, 1);
        } else {
            num_bad ++;
            mask_sel_array_out->SetValElm(idata, 0);
        }
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);

        delete [] val_arr_tmp;
        delete [] val_err_arr_tmp;
        delete [] mask_sel_arr;
    }

    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}


void DataArray1dOpe::GetVariance(const DataArray1d* const* const data_array_arr,
                                 int ndata_array,
                                 DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp = new double [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
        }
        double val = MxcsMath::GetVariance(ndata_array, val_arr_tmp);
        data_array_out->SetValElm(idata, val);
        delete [] val_arr_tmp;
    }
}


void DataArray1dOpe::GetStddev(const DataArray1d* const* const data_array_arr,
                               int ndata_array,
                               DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp = new double [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
        }
        double val = MxcsMath::GetStddev(ndata_array, val_arr_tmp);
        data_array_out->SetValElm(idata, val);
        delete [] val_arr_tmp;
    }
}


void DataArray1dOpe::GetUnbiasedVariance(
    const DataArray1d* const* const data_array_arr,
    int ndata_array,
    DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp = new double [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
        }
        double val = MxcsMath::GetUnbiasedVariance(ndata_array, val_arr_tmp);
        data_array_out->SetValElm(idata, val);
        delete [] val_arr_tmp;
    }
}

void DataArray1dOpe::GetSqrtOfUnbiasedVariance(
    const DataArray1d* const* const data_array_arr,
    int ndata_array,
    DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);    
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp = new double [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
        }
        double val = MxcsMath::GetSqrtOfUnbiasedVariance(ndata_array,
                                                         val_arr_tmp);
        data_array_out->SetValElm(idata, val);
        delete [] val_arr_tmp;
    }
}


void DataArray1dOpe::GetRMS(const DataArray1d* const* const data_array_arr,
                            int ndata_array,
                            DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp = new double [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
        }
        double val = MxcsMath::GetRMS(ndata_array, val_arr_tmp);
        data_array_out->SetValElm(idata, val);
        delete [] val_arr_tmp;
    }
}

void DataArray1dOpe::GetMedian(const DataArray1d* const* const data_array_arr,
                               int ndata_array,
                               DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp = new double [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array ++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
        }
        double val = MxcsMath::GetMedian(ndata_array, val_arr_tmp);
        data_array_out->SetValElm(idata, val);
        delete [] val_arr_tmp;
    }
}


void DataArray1dOpe::GetSumWithMask(
    const DataArray1d* const* const data_array_arr,
    const DataArray1d* const* const mask_array_arr,
    int ndata_array,
    DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    IsFormatSame(mask_array_arr, ndata_array);
    IsFormatSame(data_array_arr[0], mask_array_arr[0]);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = 0.0;
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val += data_array_arr[idata_array]->GetValElm(idata) *
                mask_array_arr[idata_array]->GetValElm(idata);
        }
        data_array_out->SetValElm(idata, val);
    }
}

void DataArray1dOpe::GetSumWithMask(
    const DataArray1d* const* const data_array_arr,
    const DataArray1d* const* const mask_array_arr,
    int ndata_array,
    DataArraySerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    IsFormatSame(mask_array_arr, ndata_array);
    IsFormatSame(data_array_arr[0], mask_array_arr[0]);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp      = new double [ndata_array];
        double* val_err_arr_tmp  = new double [ndata_array];
        int* mask_arr_tmp        = new int [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
            val_err_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValSerrElm(idata);
            mask_arr_tmp[idata_array]
                = static_cast<int>(mask_array_arr[idata_array]->GetValElm(idata));
        }
        double val = 0.0;
        double val_serr = 0.0;
        MxcsMath::GetSumWithMask(ndata_array,
                                 val_arr_tmp,
                                 val_err_arr_tmp,
                                 mask_arr_tmp,
                                 &val,
                                 &val_serr);
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);
        delete [] val_arr_tmp;
        delete [] val_err_arr_tmp;
        delete [] mask_arr_tmp;
    }
}

void DataArray1dOpe::GetAMeanWithMask(
    const DataArray1d* const* const data_array_arr,
    const DataArray1d* const* const mask_array_arr,
    int ndata_array,
    DataArrayNerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    IsFormatSame(mask_array_arr, ndata_array);
    IsFormatSame(data_array_arr[0], mask_array_arr[0]);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double val = 0.0;
        int nsel = 0;
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            if(1 == mask_array_arr[idata_array]->GetValElm(idata)){
                val += data_array_arr[idata_array]->GetValElm(idata);
                nsel ++;
            }
        }
        if(nsel > 0){
            val /= nsel;
        }
        data_array_out->SetValElm(idata, val);
    }
}

void DataArray1dOpe::GetAMeanWithMask(
    const DataArray1d* const* const data_array_arr,
    const DataArray1d* const* const mask_array_arr,
    int ndata_array,
    DataArraySerr1d* const data_array_out)
{
    IsFormatSame(data_array_arr, ndata_array);
    IsFormatSame(mask_array_arr, ndata_array);
    IsFormatSame(data_array_arr[0], mask_array_arr[0]);
    long ndata = data_array_arr[0]->GetNdata();
    data_array_out->Init(ndata);
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp      = new double [ndata_array];
        double* val_err_arr_tmp  = new double [ndata_array];
        int* mask_arr_tmp        = new int [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
            val_err_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValSerrElm(idata);
            mask_arr_tmp[idata_array]
                = static_cast<int>(mask_array_arr[idata_array]->GetValElm(idata));
        }
        double val = 0.0;
        double val_serr = 0.0;
        MxcsMath::GetAMeanWithMask(ndata_array, val_arr_tmp, val_err_arr_tmp,
                                   mask_arr_tmp,
                                   &val, &val_serr);
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);

        delete [] val_arr_tmp;
        delete [] val_err_arr_tmp;
        delete [] mask_arr_tmp;
    }
}

int DataArray1dOpe::GetWMeanWithMask(
    const DataArray1d* const* const data_array_arr,
    const DataArray1d* const* const mask_array_arr,
    int ndata_array,
    DataArrayNerr1d* const mask_sel_array_out,
    DataArraySerr1d* const data_array_out)
{
    int status = kRetNormal;    
    IsFormatSame(data_array_arr, ndata_array);
    IsFormatSame(mask_array_arr, ndata_array);
    IsFormatSame(data_array_arr[0], mask_array_arr[0]);
    long ndata = data_array_arr[0]->GetNdata();
    mask_sel_array_out->Init(ndata);    
    data_array_out->Init(ndata);
    long num_bad = 0;
    for(long idata = 0; idata < ndata; idata++){
        double* val_arr_tmp      = new double [ndata_array];
        double* val_err_arr_tmp  = new double [ndata_array];
        int* mask_arr_tmp        = new int [ndata_array];
        for(int idata_array = 0; idata_array < ndata_array; idata_array++){
            val_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValElm(idata);
            val_err_arr_tmp[idata_array]
                = data_array_arr[idata_array]->GetValSerrElm(idata);
            mask_arr_tmp[idata_array]
                = static_cast<int>(mask_array_arr[idata_array]->GetValElm(idata));
        }
        double val = 0.0;
        double val_serr = 0.0;
        long nsel = 0;
        int* mask_sel_arr_tmp = NULL;
        int ret = MxcsMath::GenWMeanWithMask(ndata_array,
                                             val_arr_tmp,
                                             val_err_arr_tmp,
                                             mask_arr_tmp,
                                             &val, &val_serr,
                                             &nsel, &mask_sel_arr_tmp);
        if(kRetNormal == ret){
            mask_sel_array_out->SetValElm(idata, 1);
        } else {
            num_bad ++;
            mask_sel_array_out->SetValElm(idata, 0);
        }
        data_array_out->SetValElm(idata, val);
        data_array_out->SetValSerrElm(idata, val_serr);

        delete [] val_arr_tmp;
        delete [] val_err_arr_tmp;
        delete [] mask_arr_tmp;
        delete [] mask_sel_arr_tmp;
    }

    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}

int DataArray1dOpe::IsFormatSame(const DataArray1d* const data_array1,
                                 const DataArray1d* const data_array2)
{
    if(data_array1->GetNdata() != data_array2->GetNdata()){
        char msg[kLineSize];
        sprintf(msg, "ndata of data1 and data2 are different: %ld, %ld",
                data_array1->GetNdata(), data_array2->GetNdata());
        MxcsPrintErr(msg);
        abort();
    }
    return 1;
}


int DataArray1dOpe::IsFormatSame(const DataArray1d* const* const data_array_arr,
                                 int ndata_array)
{
    if(ndata_array < 2){
        char msg[kLineSize];
        sprintf(msg, "nata_array(=%d) < 2", ndata_array);
        MxcsPrintWarn(msg);
        MxcsPrintWarn("skip check.");
        return 1;
    }
    for(int idata_array = 1; idata_array < ndata_array; idata_array ++){
        if(data_array_arr[idata_array]->GetNdata()
           != data_array_arr[0]->GetNdata()){
            char msg[kLineSize];
            sprintf(msg, "ndata of data[%d] and data[0] are different: %ld, %ld",
                    idata_array,
                    data_array_arr[idata_array]->GetNdata(),
                    data_array_arr[0]->GetNdata());
            MxcsPrintErr(msg);
            abort();
        }
    }
    return 1;
}
