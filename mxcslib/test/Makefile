include ../../Makefile.in
include ../../mxcslib/Makefile.in
include ../../mxcsfitslib/Makefile.in


#HEADAS_LIB = -L/soft/heasoft/6.30.1/x86_64-pc-linux-gnu-libc2.17/lib -lhdinit_6.30 -lhdutils_6.30 -lape_2.9 -lcfitsio -lreadline -lhdio_6.30 -lfftw3 -lrandom

#HEADAS_INC = -I/soft/heasoft/6.30.1/x86_64-pc-linux-gnu-libc2.17/include

#HEADAS_LIB = -L/soft/heasoft/6.30.1/x86_64-pc-linux-gnu-libc2.17/lib -lhdutils_6.30  -lape_2.9 -lcfitsio -lreadline -lhdio_6.30 -lfftw3 

INCLUDE = $(MXCSLIB_INC) $(HEADAS_INC)
LDLIBS  = $(MXCSLIB_LIB) $(HEADAS_LIB)  $(LIB)

TARGET = test_base  test_iolib \
	test_sort  test_str  test_time  test_rand

all: $(TARGET) 

test_base: test_base.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_iolib: test_iolib.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_sort: test_sort.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_str: test_str.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_time: test_time.o
	$(CXXN) $@.o ${LDLIBS} -o $@
test_rand: test_rand.o
	$(CXXN) $@.o ${LDLIBS} -o $@

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
