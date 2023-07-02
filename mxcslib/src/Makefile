include ../../Makefile.in
include ../../mxcslib/Makefile.in

INCLUDE := $(MXCSLIB_INC)

TARGET := libmxcslib.a

OBJ := base.o  str.o  iolib.o  time.o
 
all: $(TARGET)

LIB_DEST := ../lib
libmxcslib.a: ${OBJ}
	$(AR) -r $@ $(OBJ)
	ranlib $@
	if [ ! -d $(LIB_DEST) ]; then mkdir $(LIB_DEST); fi
	cp $@ ${LIB_DEST}
	ranlib ${LIB_DEST}/$@

libmxcslib.so: ${OBJ}
	$(CC) -shared -g -O2 -o $@ ${OBJ}
	if [ ! -d $(LIB_DEST) ]; then mkdir $(LIB_DEST); fi
	cp $@ ${LIB_DEST}

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
	-rm -f *.o *.a *.so

cleaner: clean
	-rm -f ${TARGET} *% *~ core
	-rm -R $(LIB_DEST)
