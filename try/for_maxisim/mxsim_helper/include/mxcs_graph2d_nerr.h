#ifndef MXCSTOOL_MXCSANALIB_GRAPH2D_NERR_H_
#define MXCSTOOL_MXCSANALIB_GRAPH2D_NERR_H_

#include "mxcs_graph2d.h"

class GraphDataNerr2d : public GraphData2d{
public:
    explicit GraphDataNerr2d(string title = "") :
        GraphData2d("GraphDataNerr2d", title) {}
    ~GraphDataNerr2d() {
        NullGraphData2d();
    }

    void Init(long ndata);
    GraphDataNerr2d* const Clone() const;
    void Load(string file);
    void Load(string file, string format);
    void Sort();
    
    const DataArrayNerr1d* const GetXvalArr() const;
    const DataArrayNerr1d* const GetOvalArr() const;
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_oval) const;
};

#endif // MXCSTOOL_MXCSANALIB_GRAPH2D_NERR_H_
