#include "mxcs_math.h"

// For a value

int MxcsMath::IsZero(double val)
{
    if(-DBL_EPSILON < val && val < DBL_EPSILON){
        return 1;
    } else {
        return 0;
    }
}

int MxcsMath::IsOne(double val)
{
    if( fabs(val - 1) < DBL_EPSILON){
        return 1;
    } else {
        return 0;
    }
}

int MxcsMath::IsOneOrZero(double val)
{
    int ans = 0;
    int one_or_zero = IsOne(val) + IsZero(val);
    if (one_or_zero > 0){
        ans = 1;
    } else {
        ans = 0;
    }
    return ans;
}

int MxcsMath::IsPlus(double val)
{
    if (val > 0) {
        return 1;
    } else {
        return 0;
    }
}

int MxcsMath::IsMinus(double val)
{
    if (val < 0) {
        return 1;
    } else {
        return 0;
    }
}

int MxcsMath::Sign(double val)
{
    if (val > 0) {
        return 1;
    } else if (val < 0) {
        return -1;
    } else {
        return 0;
    }
}

double MxcsMath::FilterPlus(double val)
{
    if (val > 0) {
        return val;
    } else {
        return 0.0;
    }
}

double MxcsMath::FilterMinus(double val)
{
    if (val < 0) {
        return val;
    } else {
        return 0.0;
    }
}

// 0 --> 1
// 1 --> 0
// others --> abort
int MxcsMath::Not(double val)
{
    if(1 != IsOneOrZero(val)){
        char msg[kLineSize];
        sprintf(msg, "bad input val (=%e)", val);
        MxcsPrintErr(msg);
        abort();
    }
    int val_int = IsOne(val);
    int ans = Not(val_int);
    return ans;
}

// 0 --> 1
// 1 --> 0
// others --> abort
int MxcsMath::Not(int val)
{
    int ans = 0;
    if(0 == val){
        ans = 1;
    } else if(1 == val){
        ans = 0;
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad input val (=%d)", val);
        MxcsPrintErr(msg);
        abort();
    }
    return ans;
}


// For a value with a gaussian error

void MxcsMath::GetScaled(double val, double val_err, double scale, double offset,
                         double* const ans_ptr, double* const ans_err_ptr)
{
    double ans     = scale * val + offset;
    double ans_err = fabs(scale) * val_err;
    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
}


// For two values without errors

int MxcsMath::IsSame(double aval, double bval)
{
    int retval = 0;
    if( fabs(aval - bval) < DBL_EPSILON ) {
        // same
        retval = 1;
    } else {
        // not same
        retval = 0;
    }
    return retval;
}

double MxcsMath::GetMin(double aval, double bval)
{
    double val = 0.0;
    if(aval <= bval){
        val = aval;
    } else {
        val = bval;
    }
    return val;
}

double MxcsMath::GetMax(double aval, double bval)
{
    double val = 0.0;
    if(aval >= bval){
        val = aval;
    } else {
        val = bval;
    }
    return val;
}

int MxcsMath::GetLocMin(double aval, double bval)
{
    if(aval <= bval){
        return 0;
    } else {
        return 1;
    }
}

int MxcsMath::GetLocMax(double aval, double bval)
{
    if(aval >= bval){
        return 0;
    } else {
        return 1;
    }
}


double MxcsMath::GetAMean(double aval, double bval)
{
    double ans = (aval + bval) / 2.;
    return ans;
}

// For two values with gaussian errors

void MxcsMath::GetAdd(double val1, double val1_err, double val2, double val2_err,
                      double* const ans_ptr, double* const ans_err_ptr)
{
    double ans     = val1 + val2;
    double ans_err = sqrt( pow(val1_err, 2) + pow(val2_err, 2) );
    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
}

void MxcsMath::GetSub(double val1, double val1_err, double val2, double val2_err,
                      double* const ans_ptr, double* const ans_err_ptr)
{
    double ans     = val1 - val2;
    double ans_err = sqrt( pow(val1_err, 2) + pow(val2_err, 2) );
    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
}

void MxcsMath::GetMul(double val1, double val1_err, double val2, double val2_err,
                      double* const ans_ptr, double* const ans_err_ptr)
{
    double ans     = val1 * val2;
    double ans_err = sqrt( pow( val1_err * val2, 2) +
                           pow( val2_err * val1, 2) );
    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
}

int MxcsMath::GetDiv(double val_num, double val_num_err,
                     double val_den, double val_den_err,
                     double* const ans_ptr, double* const ans_err_ptr)
{
    int status = kRetNormal;
  
    double ans     = 0.0;
    double ans_err = 0.0;
    if( fabs(val_den) > DBL_EPSILON) {
        ans     = val_num / val_den;
        ans_err = sqrt( pow( val_num_err * val_den, 2) +
                        pow( val_den_err * val_num, 2) ) / pow( val_den, 2);
        status = kRetNormal;
    } else {
        status = kRetError;
    }

    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
    return status;
}


void MxcsMath::GetAMean(double val1, double val1_err,
                        double val2, double val2_err,
                        double* const amean_ptr, double* const amean_err_ptr)
{
    double amean = (val1 + val2) / 2.;
    double amean_err = sqrt(pow(val1_err, 2) + pow(val2_err, 2)) / 2.;
    
    *amean_ptr = amean;
    *amean_err_ptr = amean_err;
}


int MxcsMath::GetWMean(double val1, double val1_err,
                       double val2, double val2_err,
                       double* const wmean_ptr, double* const wmean_err_ptr)
{
    int status = kRetNormal;
    double wmean     = 0.0;
    double wmean_err = 0.0;
    if(val1_err < DBL_EPSILON || val2_err < DBL_EPSILON) {
        status = kRetError;
    } else {
        double num = val1 / pow(val1_err, 2) + val2 / pow(val2_err, 2);
        double den = 1.0 / pow(val1_err, 2) + 1.0 / pow(val2_err, 2);
        if(den < DBL_EPSILON) {
            status = kRetError;
        } else {
            wmean     = num / den;
            wmean_err = sqrt( 1. / den);
        }
    }
    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    return status;
}


// sub_add_ratio = (val1 - val2) / (val1 + val2)
int MxcsMath::GetSubAddRatio(double val1, double val1_err,
                             double val2, double val2_err,
                             double* const ans_ptr, double* const ans_err_ptr)
{
    int status = kRetNormal;
  
    double ans     = 0.0;
    double ans_err = 0.0;
    if( fabs(val1 + val2) > DBL_EPSILON) {
        ans     = (val1 - val2) / (val1 + val2);
        ans_err = 2 * sqrt( pow(val2 * val1_err, 2) +  pow(val1 * val2_err, 2) )
            / pow(val1 + val2, 2);
        status = kRetNormal;
    } else {
        status = kRetError;
    }

    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
    return status;
}


// For N values without errors
//  for array

double MxcsMath::GetMin(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);
    double min = val_arr[0];
    for(long iarr = 1; iarr < narr; iarr ++){
        if(min > val_arr[iarr]){
            min = val_arr[iarr];
        }
    }
    return min;
}

double MxcsMath::GetMax(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);    
    double max = val_arr[0];
    for(long iarr = 1; iarr < narr; iarr ++){
        if(max < val_arr[iarr]){
            max = val_arr[iarr];
        }
    }
    return max;
}

long MxcsMath::GetLocMin(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);
    double min = val_arr[0];
    long imin = 0;
    for(long iarr = 1; iarr < narr; iarr ++){
        if(min > val_arr[iarr]){
            min = val_arr[iarr];
            imin = iarr;
        }
    }
    return imin;
}

long MxcsMath::GetLocMax(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);    
    double max = val_arr[0];
    long imax = 0;
    for(long iarr = 1; iarr < narr; iarr ++){
        if(max < val_arr[iarr]){
            max = val_arr[iarr];
            imax = iarr;
        }
    }
    return imax;
}

double MxcsMath::GetSum(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);
    double ans = 0.0;
    for(long idata = 0; idata < narr; idata++){
        ans += val_arr[idata];
    }
    return ans;
}

double MxcsMath::GetAMean(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);    
    double sum = 0.0;
    for (long index = 0; index < narr; index++){
        sum += val_arr[index];
    }
    double ave = sum / narr;
    return ave;
}

double MxcsMath::GetVariance(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);    
    double sum = 0;
    double sum2 = 0;
    for (long index = 0; index < narr; index++){
        sum  += val_arr[index];
        sum2 += val_arr[index] * val_arr[index];
    }
    double variance = ( sum2 - pow(sum, 2) / narr ) / narr;
    return variance;
}

double MxcsMath::GetStddev(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);    
    double stddev = sqrt( GetVariance(narr, val_arr) );
    return stddev;
}

double MxcsMath::GetUnbiasedVariance(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);    
    if(narr < 2){
        char msg[kLineSize];
        sprintf(msg, "narr (=%ld) < 2", narr);
        MxcsPrintErr(msg);
        abort();
    }
    double sum = 0;
    double sum2 = 0;
    for (long index = 0; index < narr; index++){
        sum  += val_arr[index];
        sum2 += val_arr[index] * val_arr[index];
    }
    double unbiased_variance = ( sum2 - pow(sum, 2) / narr ) / (narr - 1);
    return unbiased_variance;
}

double MxcsMath::GetSqrtOfUnbiasedVariance(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);
    double sqrt_of_unbiased_variance = sqrt( GetUnbiasedVariance(narr, val_arr) );
    return sqrt_of_unbiased_variance;
}


double MxcsMath::GetRMS(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);    
    double sum2 = 0;
    for (long index = 0; index < narr; index++){
        sum2 += val_arr[index] * val_arr[index];
    }
    double rms = sqrt(sum2 / narr);
    return rms;
}

double MxcsMath::GetMedian(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);

    long* index_arr = new long[narr];
    bool down = false;
    MxcsSort::Sort(narr, val_arr, index_arr, down);

    // 0, 1, 2, 3, 4 : narr = 5
    // narr / 2 = 2

    // 0, 1, 2, 3, 4, 5 : narr = 6
    // narr / 2 = 3
    
    double median = 0.0;
    if (1 == narr % 2){
        // odd
        median = val_arr[index_arr[narr/2]];
    } else {
        // even
        median = (val_arr[index_arr[narr/2 - 1]] + val_arr[index_arr[narr/2]])
            / 2.0;
    }
    delete [] index_arr;
    return median;
}





// For N values without errors
//  for vector

double MxcsMath::GetMin(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MxcsBase::GenArray(vec, &narr, &val_arr);
    double ans = GetMin(narr, val_arr);
    MxcsBase::DelArray(val_arr);
    return ans;
}

double MxcsMath::GetMax(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MxcsBase::GenArray(vec, &narr, &val_arr);
    double ans = GetMax(narr, val_arr);
    MxcsBase::DelArray(val_arr);
    return ans;
}

long MxcsMath::GetLocMin(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MxcsBase::GenArray(vec, &narr, &val_arr);
    long ans = GetLocMin(narr, val_arr);
    MxcsBase::DelArray(val_arr);
    return ans;
}

long MxcsMath::GetLocMax(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MxcsBase::GenArray(vec, &narr, &val_arr);
    long ans = GetLocMax(narr, val_arr);
    MxcsBase::DelArray(val_arr);
    return ans;
}

double MxcsMath::GetSum(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MxcsBase::GenArray(vec, &narr, &val_arr);
    double ans = GetSum(narr, val_arr);
    MxcsBase::DelArray(val_arr);
    return ans;
}

double MxcsMath::GetAMean(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MxcsBase::GenArray(vec, &narr, &val_arr);
    double ans = GetAMean(narr, val_arr);
    MxcsBase::DelArray(val_arr);
    return ans;
}

double MxcsMath::GetVariance(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MxcsBase::GenArray(vec, &narr, &val_arr);
    double ans = GetVariance(narr, val_arr);
    MxcsBase::DelArray(val_arr);
    return ans;
}

double MxcsMath::GetStddev(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MxcsBase::GenArray(vec, &narr, &val_arr);
    double ans = GetStddev(narr, val_arr);
    MxcsBase::DelArray(val_arr);
    return ans;
}

double MxcsMath::GetUnbiasedVariance(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MxcsBase::GenArray(vec, &narr, &val_arr);
    double ans = GetUnbiasedVariance(narr, val_arr);
    MxcsBase::DelArray(val_arr);
    return ans;
}

double MxcsMath::GetSqrtOfUnbiasedVariance(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MxcsBase::GenArray(vec, &narr, &val_arr);
    double ans = GetSqrtOfUnbiasedVariance(narr, val_arr);
    MxcsBase::DelArray(val_arr);
    return ans;
}

double MxcsMath::GetRMS(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MxcsBase::GenArray(vec, &narr, &val_arr);
    double ans = GetRMS(narr, val_arr);
    MxcsBase::DelArray(val_arr);
    return ans;
}

double MxcsMath::GetMedian(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MxcsBase::GenArray(vec, &narr, &val_arr);
    double ans = GetMedian(narr, val_arr);
    MxcsBase::DelArray(val_arr);
    return ans;
}

// For N values with gaussian errors

void MxcsMath::GetSum(long narr, const double* const val_arr,
                      const double* const val_err_arr,
                      double* const sum_ptr, double* const sum_err_ptr)
{
    MxcsBase::IsValidArray(narr, val_arr);
    MxcsBase::IsValidArray(narr, val_err_arr);
    double sum      = 0.0;
    double sum_err2 = 0.0;
    for(long index = 0; index < narr; index++){    
        sum += val_arr[index];
        sum_err2 += pow(val_err_arr[index], 2);
    }
    double sum_err = sqrt(sum_err2);
    
    *sum_ptr     = sum;
    *sum_err_ptr = sum_err;
}

void MxcsMath::GetAMean(long narr, const double* const val_arr,
                        const double* const val_err_arr,
                        double* const amean_ptr, double* const amean_err_ptr)
{
    MxcsBase::IsValidArray(narr, val_arr);
    MxcsBase::IsValidArray(narr, val_err_arr);
    double sum = 0.0;
    double sum_err2 = 0.0;
    for(long index = 0; index < narr; index++){
        sum += val_arr[index];
        sum_err2 += pow(val_err_arr[index], 2);
    }
    double amean = sum / narr;
    double amean_err = sqrt(sum_err2) / narr;

    *amean_ptr = amean;
    *amean_err_ptr = amean_err;
}

int MxcsMath::GenWMean(long narr, const double* const val_arr,
                       const double* const val_err_arr,
                       double* const wmean_ptr, double* const wmean_err_ptr,
                       long* const nsel_ptr, int** const mask_sel_arr_ptr)
{
    int status = kRetNormal;
    MxcsBase::IsValidArray(narr, val_arr);
    MxcsBase::IsValidArray(narr, val_err_arr);
    long num_bad = 0;
    double num = 0.0;
    double den = 0.0;
    long nsel = 0;
    int* mask_sel_arr = new int [narr];
    for(long index = 0; index < narr; index++){
        mask_sel_arr[index] = 0;
    }
    for(long index = 0; index < narr; index++){
        if( pow(val_err_arr[index], 2) < DBL_EPSILON ){
            num_bad ++;
        } else {
            nsel ++;
            num += val_arr[index] / pow(val_err_arr[index], 2);
            den += 1. / pow(val_err_arr[index], 2);
            mask_sel_arr[index] = 1;
        }
    }
    double wmean     = num / den;
    double wmean_err = sqrt( 1. / den);
    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *nsel_ptr = nsel;
    *mask_sel_arr_ptr = mask_sel_arr;

    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}




void MxcsMath::GetSumWithMask(long narr, const double* const val_arr,
                              const double* const val_err_arr,
                              const int* const mask_arr,
                              double* const sum_ptr, double* const sum_err_ptr)
{
    MxcsBase::IsValidArray(narr, val_arr);
    MxcsBase::IsValidArray(narr, val_err_arr);
    MxcsBase::IsValidArray(narr, mask_arr);
    double sum      = 0.0;
    double sum_err2 = 0.0;
    for(long index = 0; index < narr; index++){
        if(1 == mask_arr[index]){
            sum += val_arr[index];
            sum_err2 += pow(val_err_arr[index], 2);
        }
    }
    double sum_err = sqrt(sum_err2);
    
    *sum_ptr     = sum;
    *sum_err_ptr = sum_err;
}


void MxcsMath::GetAMeanWithMask(long narr, const double* const val_arr,
                                const double* const val_err_arr,
                                const int* const mask_arr,
                                double* const amean_ptr,
                                double* const amean_err_ptr)
{
    MxcsBase::IsValidArray(narr, val_arr);
    MxcsBase::IsValidArray(narr, val_err_arr);
    MxcsBase::IsValidArray(narr, mask_arr);
    double sum = 0.0;
    double sum_err2 = 0.0;
    long nsel = 0;
    for(long index = 0; index < narr; index++){
        if(1 == mask_arr[index]){
            nsel ++;
            sum += val_arr[index];
            sum_err2 += pow(val_err_arr[index], 2);
        }
    }
    double amean = 0.0;
    double amean_err = 0.0;
    if(nsel > 0){
        amean = sum / nsel;
        amean_err = sqrt(sum_err2) / nsel;
    }
    *amean_ptr     = amean;
    *amean_err_ptr = amean_err;
}


int MxcsMath::GenWMeanWithMask(long narr, const double* const val_arr,
                               const double* const val_err_arr,
                               const int* const mask_arr,
                               double* const wmean_ptr,
                               double* const wmean_err_ptr,
                               long* const nsel_ptr,
                               int** const mask_sel_arr_ptr)
{
    int status = kRetNormal;
    MxcsBase::IsValidArray(narr, val_arr);
    MxcsBase::IsValidArray(narr, val_err_arr);
    MxcsBase::IsValidArray(narr, mask_arr);
    long num_bad = 0;
    double num = 0.0;
    double den = 0.0;
    long nsel = 0;
    int* mask_sel_arr = new int [narr];
    for(long index = 0; index < narr; index++){
        mask_sel_arr[index] = 0;
    }
    for(long index = 0; index < narr; index++){
        if(fabs(mask_arr[index] - 1.0) < DBL_EPSILON){
            if( pow(val_err_arr[index], 2) < DBL_EPSILON ){
                num_bad ++;
            } else {
                nsel ++;
                num += val_arr[index] / pow(val_err_arr[index], 2);
                den += 1. / pow(val_err_arr[index], 2);
                mask_sel_arr[index] = 1;
            }
        }
    }
    double wmean     = 0.0;
    double wmean_err = 0.0;
    if( fabs(den) < DBL_EPSILON ){
        num_bad ++;
    } else {
        wmean     = num / den;
        wmean_err = sqrt( 1. / den);
    }

    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *nsel_ptr = nsel;
    *mask_sel_arr_ptr = mask_sel_arr;    

    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}

int MxcsMath::GenChi2byConst(long narr,
                             const double* const val_arr,
                             const double* const val_err_arr,
                             double* const wmean_ptr,
                             double* const wmean_err_ptr,
                             long* const nsel_ptr,
                             int** const mask_sel_arr_ptr,
                             double* const chi2_ptr,
                             long* const dof_ptr,
                             double* const chi2_red_ptr,
                             double* const prob_ptr)
{
    int status = kRetNormal;
    double wmean = 0.0;
    double wmean_err = 0.0;
    long nsel = 0;
    int* mask_sel_arr = NULL;
    int status_getwmean = GenWMean(narr, val_arr, val_err_arr,
                                   &wmean, &wmean_err,
                                   &nsel, &mask_sel_arr);
    double chi2 = 0.0;
    for(long index = 0; index < narr; index ++){
        if(1 == mask_sel_arr[index]){
            if( pow(val_err_arr[index], 2) > DBL_EPSILON ){
                chi2 += pow(val_arr[index] - wmean, 2) / pow(val_err_arr[index], 2);
            }
        }
    }
    long dof = nsel - 1;
    if(dof < 1){
        printf("Error: dof(=%ld) < 1.", dof);
        abort();
    }
    double chi2_red = chi2 / dof;

    // the probability that an observed Chi-squared exceeds
    // the value chi2 by chance, even for a correct model.
    double prob = PvalChi2(chi2, dof);

    // See Numerical Recipes, Section 6.2
    // prob = Q(chi2, dof) = gammq(dof/2, chi2/2) = 1 - gammp(dof/2, chi2/2)
    //                     = 1 - TMath::Gamma(dof/2, chi2/2)
    // double prob = 1. - TMath::Gamma(dof/2., chi2/2.));
    //

    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *nsel_ptr = nsel;
    *mask_sel_arr_ptr = mask_sel_arr;
    *chi2_ptr = chi2;
    *dof_ptr = dof;
    *chi2_red_ptr = chi2_red;
    *prob_ptr = prob;

    status = status_getwmean;
    return status;
}

int MxcsMath::GenChi2byConst(long narr,
                            const double* const val_arr,
                            const double* const val_err_arr,
                            const int* const mask_arr,
                            double* const wmean_ptr,
                            double* const wmean_err_ptr,
                            long* const nsel_ptr,
                            int** const mask_sel_arr_ptr,
                            double* const chi2_ptr,
                            long* const dof_ptr,
                            double* const chi2_red_ptr,
                            double* const prob_ptr)
{
    int status = kRetNormal;
    double wmean = 0.0;
    double wmean_err = 0.0;
    long nsel = 0;
    int* mask_sel_arr = NULL;
    int status_getwmean = GenWMeanWithMask(narr, val_arr, val_err_arr,
                                           mask_arr,
                                           &wmean, &wmean_err,
                                           &nsel, &mask_sel_arr);
    double chi2 = 0.0;
    for(long index = 0; index < narr; index ++){
        if(1 == mask_sel_arr[index]){
            if( pow(val_err_arr[index], 2) > DBL_EPSILON ){
                chi2 += pow(val_arr[index] - wmean, 2) / pow(val_err_arr[index], 2);
            }
        }
    }
    long dof = nsel - 1;
    if(dof < 1){
        printf("Error: dof(=%ld) < 1.", dof);
        abort();
    }
    double chi2_red = chi2 / dof;

    // the probability that an observed Chi-squared exceeds
    // the value chi2 by chance, even for a correct model.
    double prob = PvalChi2(chi2, dof);

    // See Numerical Recipes, Section 6.2
    // prob = Q(chi2, dof) = gammq(dof/2, chi2/2) = 1 - gammp(dof/2, chi2/2)
    //                     = 1 - TMath::Gamma(dof/2, chi2/2)
    // double prob = 1. - TMath::Gamma(dof/2., chi2/2.));
    //

    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *nsel_ptr = nsel;
    *mask_sel_arr_ptr = mask_sel_arr;
    *chi2_ptr = chi2;
    *dof_ptr = dof;
    *chi2_red_ptr = chi2_red;
    *prob_ptr = prob;

    status = status_getwmean;
    return status;
}


// ichiji-hokan
double MxcsMath::IntPolLin(double xval,
                           double xval_lo, double xval_up,
                           double yval_lo, double yval_up){
    double yval = 0.0;
    if( fabs(xval_up - xval_lo) < DBL_EPSILON ) {
        yval = (yval_up + yval_lo) / 2.;
    } else {
        yval = yval_lo +
            (xval - xval_lo) * (yval_up - yval_lo) / (xval_up - xval_lo);
    }
    return yval;
}



double MxcsMath::IntPolLin(double xval, double yval,
                           double xval0, double xval1,
                           double yval0, double yval1,
                           double oval_x0y0, double oval_x1y0,
                           double oval_x1y1, double oval_x0y1)
//
// Ichiji-hokan in two demension.
//  
// see Numerical Recipe "Interpolation in Two or More Dimensions"
// y
// ^
// |    (x0,y1):3      (x1,y1):2
// |          (x,y)
// |
// |    (x0,y0):0      (x1,y0):1
// +--------------------------------> x
//
  
{
    double ratio_x = (xval - xval0) / (xval1 - xval0);
    double ratio_y = (yval - yval0) / (yval1 - yval0);

    double oval =
        (1 - ratio_x) * (1 - ratio_y) * oval_x0y0 +
        ratio_x       * (1 - ratio_y) * oval_x1y0 +
        ratio_x       * ratio_y       * oval_x1y1 +
        (1 - ratio_x) * ratio_y       * oval_x0y1;

    return oval;
}

//
// statistics
//

// PDF: probability density function
double MxcsMath::GaussianPDF(double xval, double mu, double sigma)
{
    double ans = 1.0 / (sigma * sqrt(2.0*M_PI))
        * exp( (-1.0)*(xval - mu)*(xval - mu)/2.0/sigma/sigma );
    return ans;
}

// CDF: cumulative distribution function
double MxcsMath::GaussianCDF(double xval, double mu, double sigma)
{
    double cdf = (1.0 + std::erf(
                      (xval - mu)
                      / sqrt(2.0 * sigma * sigma) ) ) / 2.0;
    return cdf;
}

// P-value
double MxcsMath::PvalGaussian(double xval, double mu, double sigma,
                              string side)
{
    double pval = 0.0;
    if("both" == side){
        double diff = fabs(xval - mu);
        pval = 1.0
            - (GaussianCDF(xval + diff, mu, sigma)
               - GaussianCDF(xval - diff, mu, sigma));
    } else if("upper" == side){
        pval = 1.0 - GaussianCDF(xval, mu, sigma);
    } else if("lower" == side){
        pval = GaussianCDF(xval, mu, sigma);
    } else{
        printf("bad side (=%s)\n", side.c_str());
        abort();
    }
    return pval;
}


double MxcsMath::GaussianAsymPDF(double xval, double mu,
                                 double sigma_plus,
                                 double sigma_minus)
{
    double sigma_mean = (sigma_plus + sigma_minus) / 2.0;
    double ans = 0.0;
    if (xval < mu){
        ans = sigma_minus / sigma_mean
            * GaussianPDF(xval, mu, sigma_minus);
    } else {
        ans = sigma_plus  / sigma_mean
            * GaussianPDF(xval, mu, sigma_plus);
    }
    return ans;
}

// gamma distribution
double MxcsMath::GammaPDF(double xval, double alpha, double beta)
{
    double pdf = ( pow(beta, alpha) * pow(xval, (alpha - 1.0))
                   * exp(-1.0 * beta * xval) ) / std::tgamma(alpha);
    return pdf;
}

double MxcsMath::GammaCDF(double xval, double alpha, double beta)
{
    // cdf = P(alpha, beta * xval),
    // where P() is the imcomplete gamma function.
    // See Numerical Recipes, (6.14.43)
    
    double cdf = gsl_sf_gamma_inc_P(alpha, beta * xval);
    return cdf;
}

double MxcsMath::PvalGamma(double xval, double alpha, double beta)
{
    double pval = 1.0 - GammaCDF(xval, alpha, beta);
    return pval;
}


// chi2 distribution
double MxcsMath::Chi2PDF(double xval, int dof)
{
    double pdf = pow(xval, dof / 2.0 - 1.0) * exp(-xval/2.0)
        / (pow(2.0, dof/2.0) * std::tgamma(dof/2.0));
    return pdf;
}

double MxcsMath::Chi2CDF(double xval, int dof)
{
    // See Numerical Recipes, (6.14.38)
    double cdf = gsl_sf_gamma_inc_P(dof/2.0, xval/2.0);
    return cdf;
}

double MxcsMath::PvalChi2(double xval, int dof)
{
    double pval = 1.0 - Chi2CDF(xval, dof);
    return pval;
}

double MxcsMath::Sigma2CL(double s_sigma_level)
{
    // s_sigma level --> confidence level
    
    double mu = 0.0;
    double sigma = 1.0;
    double cl = GaussianCDF(s_sigma_level, mu, sigma)
        - GaussianCDF(-s_sigma_level, mu, sigma);
    return cl;
}


// for binning
long MxcsMath::GetNbin(double val_lo, double val_up,
                       double delta_val, string mode)
{
    if(val_up <= val_lo){
        printf("ERROR: %s: %u: %s(): val_up <= val_lo.\n",
               __FILE__, __LINE__, __func__);
        abort();
    }
    if(delta_val <= 0){
        printf("ERROR: %s: %u: %s(): delta_val <= 0.\n",
               __FILE__, __LINE__, __func__);
        abort();
    }
    
    double gphase = (val_up - val_lo) / delta_val;
    double phase = gphase - floor(gphase);

    long nbin = 0;
    if(phase < DBL_EPSILON || 1 - phase < DBL_EPSILON){
        double gphase_plus_epsilon = gphase + DBL_EPSILON;
        nbin = (long) floor(gphase_plus_epsilon);
    } else {
        if("err" == mode){
            printf("ERROR: %s: %u: %s(): val_up - val_lo "
                   "is not an interger of delta_val\n",
                   __FILE__, __LINE__, __func__);
            abort();
        } else if ("floor" == mode){
            nbin = (long) floor(gphase);
        } else if ("ceil" == mode){
            nbin = (long) ceil(gphase);
        } else {
            printf("ERROR: %s: %u: %s(): bad mode (=%s)\n",
                   __FILE__, __LINE__, __func__, mode.c_str());
            abort();
        }
    }
    return nbin;
}

// useful when you want to obtain even number of bin.
long MxcsMath::GetNbinEven(double val_lo, double val_up, double delta_val)
{
    long nbin_floor = GetNbin(val_lo, val_up, delta_val, "floor");
    if(0 == nbin_floor % 2){
        return nbin_floor;
    } else {
        return nbin_floor + 1;
    }
}

int MxcsMath::IsSorted(long narr, const double* const val_arr)
{
    MxcsBase::IsValidArray(narr, val_arr);    
    int ans = 1;
    double val_pre = val_arr[0];
    for (long index = 1; index < narr; index++){
        if(val_pre > val_arr[index]){
            ans = 0;
            break;
        }
        val_pre = val_arr[index];
    }
    return ans;
}

// inner product
double MxcsMath::GetInProd(double vec0_xval, double vec0_yval,
                           double vec1_xval, double vec1_yval)
{
    double ans = 0.0;
    ans = vec0_xval * vec1_xval + vec0_yval * vec1_yval;
    return ans;
}

