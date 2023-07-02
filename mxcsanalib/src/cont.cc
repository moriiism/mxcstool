#include "mxcs_cont.h"

//
// MxcsCont
//

// public

void MxcsCont::Init(int ngraph)
{
    Null();

    ngraph_ = ngraph;
    gd2d_arr_ = new GraphDataNerr2d* [ngraph_];
    for(int igraph = 0; igraph < ngraph_; igraph ++){
        gd2d_arr_[igraph] = new GraphDataNerr2d;
    }
}

void MxcsCont::SetGd2dArr(int ngraph,
                          const GraphDataNerr2d* const* const gd2d_arr)
{
    if(ngraph != GetNgraph()){
        char msg[kLineSize];
        sprintf(msg, "ngraph (=%d) != ngraph_ (=%d).",
                ngraph, GetNgraph());
        MxcsPrintErrClass(msg);
        abort();
    }
    for(int igraph = 0; igraph < GetNgraph(); igraph ++){
        gd2d_arr_[igraph]->Copy(gd2d_arr[igraph]);
    }
}

void MxcsCont::AddPolygon(int npoint,
                          const double* const xval_arr,
                          const double* const yval_arr)
{
    GraphDataNerr2d* gd2d_this = new GraphDataNerr2d;
    gd2d_this->Init(npoint);
    gd2d_this->SetXvalArr(npoint, xval_arr);
    gd2d_this->SetOvalArr(npoint, yval_arr);
    
    if(0 != GetNgraph()){

        // make temporary graph_array to save original contour
        int ngraph_org = GetNgraph();
        GraphDataNerr2d** gd2d_arr_tmp = new GraphDataNerr2d* [ngraph_org];
        for(int igraph = 0; igraph < ngraph_org; igraph ++){
            gd2d_arr_tmp[igraph] = new GraphDataNerr2d;
            gd2d_arr_tmp[igraph]->Copy(  GetGd2dArrElm(igraph) );
        }

        // allocate new graph_array
        int ngraph_new = ngraph_org + 1;
        Init(ngraph_new);
        for(int igraph = 0; igraph < ngraph_org; igraph ++){
            gd2d_arr_[igraph]->Copy(gd2d_arr_tmp[igraph]);
        }
        gd2d_arr_[ngraph_new - 1]->Copy(gd2d_this);

        // delete temporary graph_array
        for(int igraph = 0; igraph < ngraph_org; igraph ++){
            delete gd2d_arr_tmp[igraph]; gd2d_arr_tmp[igraph] = NULL;
        }
        delete [] gd2d_arr_tmp; gd2d_arr_tmp = NULL;

    } else {
        Init(1);
        gd2d_arr_[0]->Copy(gd2d_this);
    }
    delete gd2d_this;
}

void MxcsCont::Copy(const MxcsCont* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);

    int ngraph_org = org->GetNgraph();
    Init(ngraph_org);
    SetGd2dArr(ngraph_org, org->GetGd2dArr());
}

MxcsCont* const MxcsCont::Clone() const
{
    MxcsCont* obj_new = new MxcsCont;
    obj_new->Copy(this);
    return obj_new;
}

string MxcsCont::GetPolygonStr(int igraph) const
{
    string format = string() + "polygon(";

    int npoint = GetGd2dArrElm(igraph)->GetNdata();
    for(int ipoint = 0; ipoint < npoint; ipoint ++){
        char buf[kLineSize];
        if(ipoint < npoint - 1){
            sprintf(buf, "%e,%e,  ",
                    GetGd2dArrElm(igraph)->GetXvalElm(ipoint),
                    GetGd2dArrElm(igraph)->GetOvalElm(ipoint));
        } else {
            sprintf(buf, "%e,%e)",
                    GetGd2dArrElm(igraph)->GetXvalElm(ipoint),
                    GetGd2dArrElm(igraph)->GetOvalElm(ipoint));
        }
        format += buf;
    }
    return format;
}

MxcsCont* const MxcsCont::GenShift(double delta_xval, double delta_yval) const
{
    int ngraph = GetNgraph();
    GraphDataNerr2d** gd2d_arr_shifted = new GraphDataNerr2d* [ngraph];
    for(int igraph = 0; igraph < ngraph; igraph++){
        gd2d_arr_shifted[igraph] = new GraphDataNerr2d;

        int npoint = GetGd2dArrElm(igraph)->GetNdata();
        double* xval_arr_shift = new double [npoint];
        double* yval_arr_shift = new double [npoint];
        for(int ipoint = 0; ipoint < npoint; ipoint++){
            xval_arr_shift[ipoint] = GetGd2dArrElm(igraph)->GetXvalElm(ipoint)
                + delta_xval;
            yval_arr_shift[ipoint] = GetGd2dArrElm(igraph)->GetOvalElm(ipoint)
                + delta_yval;
        }
        int flag_xval_sorted = GetGd2dArrElm(igraph)->GetFlagXvalSorted();

        gd2d_arr_shifted[igraph]->Init(npoint);
        gd2d_arr_shifted[igraph]->SetXvalArr(npoint, xval_arr_shift);
        gd2d_arr_shifted[igraph]->SetOvalArr(npoint, yval_arr_shift);
        gd2d_arr_shifted[igraph]->SetFlagXvalSorted(flag_xval_sorted);
        delete [] xval_arr_shift;
        delete [] yval_arr_shift;
    }

    MxcsCont* shifted = new MxcsCont;
    shifted->Init(ngraph);
    shifted->SetGd2dArr(ngraph, gd2d_arr_shifted);

    for(int igraph = 0; igraph < ngraph; igraph++){
        delete gd2d_arr_shifted[igraph]; gd2d_arr_shifted[igraph] = NULL;
    }
    delete [] gd2d_arr_shifted; gd2d_arr_shifted = NULL;
    return shifted;
}

// private

void MxcsCont::Null()
{
    if(NULL != gd2d_arr_){
        for(int igraph = 0; igraph < ngraph_; igraph++){
            delete gd2d_arr_[igraph]; gd2d_arr_[igraph] = NULL;
        }
        delete [] gd2d_arr_; gd2d_arr_ = NULL;
    }
    ngraph_ = 0;
}


//
// MxcsContWithBest
//

// public
 
void MxcsContWithBest::Init()
{
    Null();

    xval_best_ = 0.0;
    yval_best_ = 0.0;
    cont_ = new MxcsCont;
}

void MxcsContWithBest::SetBest(double xval_best, double yval_best)
{
    xval_best_ = xval_best;
    yval_best_ = yval_best;
}

void MxcsContWithBest::SetCont(const MxcsCont* const cont)
{
    cont_->Copy(cont);
}

void MxcsContWithBest::Copy(const MxcsContWithBest* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);

    Init();
    SetBest(org->GetXvalBest(),
            org->GetYvalBest());
    SetCont(org->GetCont());
}

MxcsContWithBest* const MxcsContWithBest::Clone() const
{
    MxcsContWithBest* obj_new = new MxcsContWithBest;
    obj_new->Copy(this);
    return obj_new;
}

MxcsContWithBest* const MxcsContWithBest::GenShift(double delta_xval,
                                                   double delta_yval) const
{
    MxcsCont* cont_shift = GetCont()->GenShift(delta_xval, delta_yval);
    
    MxcsContWithBest* cont_with_best = new MxcsContWithBest;
    cont_with_best->Init();
    cont_with_best->SetBest(GetXvalBest() + delta_xval,
                            GetYvalBest() + delta_yval);
    cont_with_best->SetCont(cont_shift);
    delete cont_shift;
    
    return cont_with_best;
}

// private

void MxcsContWithBest::Null()
{
    xval_best_ = 0.0;
    yval_best_ = 0.0;    
    if(NULL != cont_){delete cont_; cont_ = NULL;}
}
