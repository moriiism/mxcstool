include ../../Makefile.in
include ../../mxcslib/Makefile.in
include ../../mxcsanalib/Makefile.in

INCLUDE := $(MXCSANALIB_INC) $(MXCSLIB_INC) $(GSL_INC) 
LDLIBS  := $(MXCSANALIB_LIB) $(MXCSLIB_LIB) $(GSL_LIB) $(LIB)

TARGET =  plot_lc_da1d  plot_lc_hd1d  plot_lc_gd2d  \
        select_da1d_by_gti  binning

all: $(TARGET) 

select_da1d_by_gti: select_da1d_by_gti.o  arg_select_da1d_by_gti.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

select_hd1d_by_gti: select_hd1d_by_gti.o  arg_select_hd1d_by_gti.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

select_gd2d_by_gti: select_gd2d_by_gti.o  arg_select_gd2d_by_gti.o
	$(CXXN) $@.o arg_$@.o ${LDLIBS} -o $@

binning: binning.o  arg_binning.o
	$(CXXN) $@.o  arg_$@.o  ${LDLIBS} -o $@

plot_lc_da1d: plot_lc_da1d.o  arg_plot_lc_da1d.o
	$(CXXN) $@.o  arg_$@.o  ${LDLIBS} -o $@

plot_lc_hd1d: plot_lc_hd1d.o  arg_plot_lc_hd1d.o
	$(CXXN) $@.o  arg_$@.o  ${LDLIBS} -o $@

plot_lc_gd2d: plot_lc_gd2d.o  arg_plot_lc_gd2d.o
	$(CXXN) $@.o  arg_$@.o  ${LDLIBS} -o $@

.SUFFIXES:
.SUFFIXES: .o .c .f .F .cc

.c.o:
	$(CCN) -c $<

.F.o : 
	$(FCN) -c $<

.f.o:
	$(FCN) -c $<

.cc.o:
	${CXXN} -c $<

clean:
	-rm -f *.o

cleaner: clean
	-rm -f ${TARGET} *% *~ core
