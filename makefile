.SUFFIXES : .cpp .o .c .y

CPP=g++
CC=gcc
AR=ar
YACPP=yacc

DEFINES_CPP=

#============================================================================
# Optimized Code - Requires more virtual memory.
OPTCPPFLAGS=-O3
#----------------------
# Not optimized
#OPTCPPFLAGS=
#============================================================================

# gcc < 2.8.x 
#DEFINES_CPP=-D_G_NO_EXTERN_TEMPLATES
#CPPFLAGS=-fhandle-exceptions 


#============================================================================
# gcc 2.8.x (y superiores):
# -------------------------
# Ver warnings:
CPPFLAGS += -Wall
# Ignorar warnings:
#CPPFLAGS += -w

# Include information for GDB:
#CPPFLAGS += -g

# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# The next flag must be actived ONLY if we are compiling under Windows 95 !!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# CPPFLAGS += -D__WINDOWS__
#============================================================================



DEFINES_C=


# If we are compiling for Unix
INCLUDES_CPP=-I/usr/include -I/home/R/cd3++ -I.
# or if we are compiling for Windows 95
#INCLUDES_CPP=


INCLUDES_C=
CFLAGS=
DEBUGFLAGS=
LDFLAGS += -L. -L/home/R/cd3++ -g 


EXAMPLESOBJS=step10.o step9.o step8.o step7.o step6.o step5.o step4.o step3.o step2.o step1.o register.o /home/R/cd3++/linpack.o /home/R/cd3++/com.o main.o
# main.o generat.o trafico.o distri.o com.o linpack.o debug.o register.o
LIBNAME=simu
LIBS=-lsimu
ALLOBJS=${EXAMPLESOBJS} ${SIMOBJS} 
INIOBJS=initest.o ini.o
ALLSRCS=${ALLOBJS:.o=.cpp} gram.y 

all: libs simu 

libs: libsimu.a
	cp /home/R/cd3++/libsimu.a .

simu: ${ALLOBJS} libsimu.a
	g++ ${LDFLAGS} -o $@ ${EXAMPLESOBJS} ${LIBS}

initest: ${INIOBJS} 
	${CPP} ${LDFLAGS} -o $@ ${INIOBJS} 

drawlog: drawlog.o libsimu.a
	g++ ${LDFLAGS} -o $@ drawlog.o ${LIBS}

makerand: makerand.o libsimu.a
	g++ ${LDFLAGS} -o $@ makerand.o ${LIBS}

toMap: toMap.o libsimu.a
	g++ ${LDFLAGS} -o $@ toMap.o ${LIBS}

toCDPP: toCDPP.o libsimu.a
	g++ ${LDFLAGS} -o $@ toCDPP.o ${LIBS}

randEvent: randEvent.o libsimu.a
	g++ ${LDFLAGS} -o $@ randEvent.o ${EXAMPLESOBJS} ${LIBS}

exptest: synnode.o
	g++ ${LDFLAGS} -o $@ synnode.o
	
parser: parser.o gram.o
	g++ ${LDFLAGS} -o $@ parser.o gram.o

libsimu.a: ${SIMOBJS}
	${AR} crs lib${LIBNAME}.a ${SIMOBJS}

clean:
	- rm -f *.o *.a simu core drawlog initest exptest parser makerand toMap

depend:
	makedepend -Y ${ALLSRCS}

backup:
	tar -cvf simu.tar *.cpp *.h *.c *.y makefile* *.ma *.ev *.vpj *.bat *.txt *.val *.inc *.map; gzip simu.tar; mv simu.tar.gz simu.tgz

# Uncomment these lines only for Windows
#macroexp.o: macroexp.cpp
#	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<
#
#flatcoup.o: flatcoup.cpp
#	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<
########################

.cpp.o:
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} ${OPTCPPFLAGS} $<

.c.o:
	${CC} -c ${INCLUDES_C} ${DEFINES_C}  ${DEBUGFLAGS} ${CFLAGS} ${OPTCPPFLAGS} $<

.y.o:
	bison -d -v -o gram.c gram.y
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} ${OPTCPPFLAGS} ${@:.o=.c} 
	rm $*.c
	
