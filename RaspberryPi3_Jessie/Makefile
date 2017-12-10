include Makefile.vars.pi

# send these to all the sub-Makefiles

# name of the executable
EXE = ./TCPSClient.bin

# Platform specific cflags defined in the Makefile.vars file
export CFLAGS = ${PFLAGS} -Wall

OBJS = main.o 

LOCAL_OBJS = main.o 

.SUFFIXES:	.cpp

all:	${LOCAL_OBJS} sub
	${CXX} ${DFLAGS} ${OBJS} -o ${EXE} -L./ -lTL_INetSyphonSDK ${LIBS} 

sub:

include $(LOCAL_OBJS:.o=.d)

.cpp.o:
	${CXX} ${CFLAGS} -c $< -o $@

clean_deps:
	find . -name "*.d" -exec rm {} \;

clean:	clean_deps
	find . -name "*.o" -exec rm {} \;
	rm -f ${EXE}

%.d : %.cpp
	set -e; $(CXX) -MM $(CFLAGS) $< \
                | sed 's^\($*\)\.o[ :]*^\1.o $@ : ^g' > $@; \
                [ -s $@ ] || rm -f $@
