# Makefile pour EZ-Draw++ : version pour UNIX
#
# 05/04/2017 - Eric.Remy@univ-amu.fr

# Variables pour Unix/X11
SHELL    = /bin/bash

ifeq ($(CXX),)
CXX=g++
endif
CFLAGS   = -g -Wall -W -ansi -pedantic -O2
CXXFLAGS = $(CFLAGS) -std=c++11
LIBS     = -L/usr/X11R6/lib -lX11 -lXext
RM       = rm -f

# Rajoutez vos executables C++ a la fin de EXECSPP =
#
EXECSPP = GrayImage

all :: $(EXECSPP)

.cpp.o :
	$(CXX) -c $(CXXFLAGS) $*.cpp


GrayImage : main.o GrayImage.o
	$(CXX) -o $@ $^ $(LIBS)

depends :
	$(CXX) -MM $(CXXFLAGS) *.cpp >depends

clean ::
	$(RM) *.o core

distclean :: clean
	$(RM) *% *~ .*.swp $(EXECSPP)

include depends

