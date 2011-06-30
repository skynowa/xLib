######################################################################################################
# Class name:  
# Description: make file for Linux
# File name:   makefile
# Author:      skynowa
# E-mail:      skynowa@gmail.com
# Created:     30.06.2011
#
######################################################################################################


BINS              = xLib_static_lib
OBJS              = Test.o

CXX               = g++
CXXFLAGS          = -Wall -O3 -pthread -g0 -s #-g   -static

INCLUDES          = -I. -I.. -I/usr/local/include -I/usr/include -I/home/sergey/Libs/xLib/Include/ -I/home/sergey/Libs/xLib/Source/
LDFLAGS           = -L/usr/local/lib -L/usr/lib -L/usr/lib/mysql -L/usr/local/lib/mysql

LIBS              = -lssl -lGeoIP -lmysqlclient


all:             $(BINS)
			@echo "\n\n---------- $@ ----------\n"
				
xLib_static_lib: $(OBJS)
			@echo "\n\n---------- $@ ----------\n"
			$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

.cpp.o:
			@echo "\n[$@]"
			$(CXX) $(INCLUDES) $(CXXFLAGS) $? -c $<

clean:		
			rm -f *.d *.o $(BINS)
