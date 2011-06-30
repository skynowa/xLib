######################################################################################################
# Class name:  
# Description: make file for Linux
# File name:   makefile
# Author:      skynowa
# E-mail:      skynowa@gmail.com
# Created:     30.06.2011
#
######################################################################################################


#  BINS              = xLib_static_lib
#  OBJS              = Test.o
#  
#  CXX               = g++
#  CXXFLAGS          = -Wall -O3 -pthread -g0 -s #-g   -static
#  
#  INCLUDES          = -I. -I.. -I/usr/local/include -I/usr/include -I/home/sergey/Libs/xLib/Include/ -I/home/sergey/Libs/xLib/Source/
#  LDFLAGS           = -L/usr/local/lib -L/usr/lib -L/usr/lib/mysql -L/usr/local/lib/mysql
#  
#  LIBS              = -lssl -lGeoIP -lmysqlclient
#  
#  
#  all:             $(BINS)
#  			@echo "\n\n---------- $@ ----------\n"
#  				
#  xLib_static_lib: $(OBJS)
#  			@echo "\n\n---------- $@ ----------\n"
#  			$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $@
#  
#  .cpp.o:
#  			@echo "\n[$@]"
#  			$(CXX) $(INCLUDES) $(CXXFLAGS) $? -c $<
#  
#  clean:		
#  			rm -f *.d *.o $(BINS)


root_include_dir   	:= Include/xLib
root_source_dir    	:= Source
source_subdirs     	:= 	.\
				Units \
				Sync \
				Patterns \
				Net \
				Log \
				Filesystem \
				Debug \
				Db \
				Crypt/OpenSSL \
				Crypt \
				Compress/Linux \
				Common

compile_flags      	:= -Wall -MD -pipe
link_flags         	:= -s -pipe
libraries          	:= -ldl -lssl -lGeoIP -lmysqlclient

relative_include_dirs	:= $(addprefix ../../, $(root_include_dir))
relative_source_dirs   	:= $(addprefix ../../$(root_source_dir)/, $(source_subdirs))
objects_dirs            := $(addprefix $(root_source_dir)/, $(source_subdirs))
objects                 := $(patsubst ../../%, %, $(wildcard $(addsuffix /*.c*, $(relative_source_dirs))))
objects                 := $(objects:.cpp=.o)
objects                 := $(objects:.c=.o)

all: 			$(program_name)

$(program_name):	obj_dirs $(objects)
			g++ -o $@ $(objects) $(link_flags) $(libraries)

obj_dirs:	        mkdir -p $(objects_dirs)

VPATH			:= ../../

%.o: 			%.cpp
			g++ -o $@ -c $< $(compile_flags) $(build_flags) $(addprefix -I, $(relative_include_dirs))

%.o: 			%.c
			g++ -o $@ -c $< $(compile_flags) $(build_flags) $(addprefix -I, $(relative_include_dirs))

.PHONY:			clean

clean:
			rm -rf bin obj

include $(wildcard $(addsuffix /*.d, $(objects_dirs)))
