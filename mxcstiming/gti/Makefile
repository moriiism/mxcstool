include ../../Makefile.in
include ../../mxcslib/Makefile.in
include ../../mxcsanalib/Makefile.in

INCLUDE := $(MXCSANALIB_INC) $(MXCSLIB_INC) $(GSL_INC)
LDLIBS  := $(MXCSANALIB_LIB) $(MXCSLIB_LIB) $(GSL_LIB) $(LIB)

TARGET = gti_split  plot_gti  gti_rmgap  gti_andor2  \
        gti_andorn  gti_lcthr  gti_lcthr_hist  gti_lcthr_evt  \
	gti_index  \
        gti_index_list  gti_is_ordered  gti_length

# gti_margin 

all: $(TARGET) 

gti_length: gti_length.o  arg_gti_length.o
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

gti_tconv: gti_tconv.o  arg_gti_tconv.o
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

gti_split: gti_split.o  arg_gti_split.o 
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

gti_rmgap: gti_rmgap.o  arg_gti_rmgap.o 
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

gti_andor2: gti_andor2.o  arg_gti_andor2.o 
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

gti_andorn: gti_andorn.o  arg_gti_andorn.o 
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

gti_lcthr: gti_lcthr.o  arg_gti_lcthr.o 
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

gti_lcthr_hist: gti_lcthr_hist.o  arg_gti_lcthr_hist.o 
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

gti_lcthr_evt: gti_lcthr_evt.o  arg_gti_lcthr_evt.o 
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

gti_margin: gti_margin.o  arg_gti_margin.o 
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

plot_gti: plot_gti.o  arg_plot_gti.o 
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

gti_index: gti_index.o  arg_gti_index.o
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

gti_index_list: gti_index_list.o  arg_gti_index_list.o
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@

gti_is_ordered: gti_is_ordered.o  arg_gti_is_ordered.o
	$(CXXN) $@.o arg_$@.o  ${LDLIBS} -o $@


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
