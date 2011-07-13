######################################################################################################
# Class name:  
# Description: make file (static library, Linux, release)
# File name:   makefile
# Author:      skynowa
# E-mail:      skynowa@gmail.com
# Created:     30.06.2011
#
######################################################################################################


##################################################
# constants
cOS						:= $(shell uname -s)
cOS_BIT					:= $(shell getconf LONG_BIT)
cOS_ARCH 				:= $(shell gcc -dumpmachine) #$(shell uname -m)
cOS_INFO 				:= $(shell uname -a)
cGCC_INFO				:= $(shell gcc -dumpversion) 
cGLIBC_INFO				:= ##$(shell ldd --version)	#TODO: not implemented
cBINUTILS_INFO			:= n/a

cBUILD_TYPE_DEBUG		:= debug
cBUILD_TYPE_RELEASE		:= release

cBIN_TYPE_LIB			:= static library
cBIN_TYPE_TESTS			:= tests

cDESCRIPTION 			:= C++ class library


##################################################
# Settings
BUILD_TYPE				:= $(cBUILD_TYPE_RELEASE)
BIN_TYPE                := $(cBIN_TYPE_LIB)


##################################################
# xLib
ifeq ($(BIN_TYPE), $(cBIN_TYPE_LIB))
PROGRAM_PREFIX			:= lib
PROGRAM_EXT  			:= .a
else						
PROGRAM_PREFIX			:=
PROGRAM_EXT  			:=
endif

PROGRAM_NAME			:= $(PROGRAM_PREFIX)xlib$(PROGRAM_EXT)

ROOT_INCLUDE_DIR		:= Include Source
ROOT_SOURCE_DIR			:= Source

OTHER_INCLUDE_DIR		:=	/usr/local/crystal_trader2.5/include \
							/usr/local/include \
							/usr/include

SOURCE_SUBDIRS			:=	.\
							Common \
							Compress/Linux \
							Crypt \
							Crypt/OpenSSL \
							Debug \
							Db \
							Filesystem \
							Log \
							Net \
							Patterns \
							Sync \
							Units
							
LIB_DIRS           		:= 	/usr/local/crystal_trader2.5/lib \
							/usr/local/crystal_trader2.5/lib/mysql \
							/usr/local/lib \
							/usr/lib \
							/usr/local/lib/mysql \
							/usr/lib/mysql

ifeq ($(BIN_TYPE), $(cBIN_TYPE_LIB))
BINARY_DIR				:= Library/G++_linux/Release
else						
BINARY_DIR				:= Contrib/G++_linux/Release
endif

INSTALL_DIR				:= /usr/local/crystal_trader2.5/lib/xLib
PROGRAM_PATH			:= ../../../$(BINARY_DIR)/$(PROGRAM_NAME)

COMPILER				:= $(CXX)
ARCHIVER                := $(AR)
COMPILE_FLAGS      		:= -Wall -MD
LINK_FLAGS              := -s -pipe

ifeq ($(cOS), $(Linux))
LIBRARIES               := -lpthread -ldl -lmysqlclient -lm -lcrypt -lz -lssl -lGeoIP
else
LIBRARIES               := -pthread  -lc  -lmysqlclient -lm -lcrypt -lz -lssl -lGeoIP
endif

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
BUILD_FLAGS     		:= -O0 -pthread -g3 -g
else
BUILD_FLAGS     		:= -O3 -pthread -fomit-frame-pointer -g0
endif

PARANOID_FLAGS			:= -pedantic -Wall -Wextra -Wformat=2 -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wsync-nand -Wstrict-overflow=1 -Wstrict-overflow=2 -Wstrict-overflow=3 -Wstrict-overflow=4 -Wstrict-overflow=5 -Wfloat-equal -Wtraditional -Wtraditional-conversion -Wdeclaration-after-statement -Wundef -Wshadow -Wunsafe-loop-optimizations -Wtype-limits -Wbad-function-cast -Wc++-compat -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wlogical-op -Waggregate-return -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-prototypes  -Wmissing-declarations  -Wmissing-field-initializers -Wmissing-format-attribute -Wpacked -Wpadded -Wredundant-decls -Wnested-externs -Winline -Winvalid-pch -Wvariadic-macros -Wvla -Wvolatile-register-var -Wdisabled-optimization -Wpointer-sign -Wstack-protector

RELATIVE_INCLUDE_DIRS	:= $(addprefix ../../../, $(ROOT_INCLUDE_DIR))
RELATIVE_SOURCE_DIRS	:= $(addprefix ../../../$(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS_DIRS			:= $(addprefix $(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS					:= $(patsubst ../../../%, %, $(wildcard $(addsuffix /*.c*, $(RELATIVE_SOURCE_DIRS))))
OBJECTS					:= $(OBJECTS:.cpp=.o)
OBJECTS					:= $(OBJECTS:.c=.o)

ifeq ($(BIN_TYPE), $(cBIN_TYPE_LIB))
$(PROGRAM_PATH):		obj_dirs $(OBJECTS)
						$(ARCHIVER) rc $@ $(OBJECTS)
else						
$(PROGRAM_PATH): 		obj_dirs $(OBJECTS)
						$(COMPILER) -o $@ $(OBJECTS) $(addprefix -L, $(LIB_DIRS)) $(LINK_FLAGS) $(LIBRARIES) 		
endif

obj_dirs:	        
						mkdir -p $(OBJECTS_DIRS)

VPATH					:= ../../../

%.o: 					%.cpp
						$(COMPILER) -o $@ -c $< $(COMPILE_FLAGS) $(BUILD_FLAGS) $(addprefix -I, $(RELATIVE_INCLUDE_DIRS) $(OTHER_INCLUDE_DIR))

%.o: 					%.c
						$(COMPILER) -o $@ -c $< $(COMPILE_FLAGS) $(BUILD_FLAGS) $(addprefix -I, $(RELATIVE_INCLUDE_DIRS) $(OTHER_INCLUDE_DIR))

.PHONY:					clean

all:
						clear	
						
						@echo "************************************************************"
						@echo "* OS info:         " $(cOS_INFO)
						@echo "* OS architecture: " $(cOS_BIT)
						@echo "* GCC info:        " $(cGCC_INFO)
						@echo "* GLIBC info:      " #$(cGLIBC_INFO)
						@echo "* Binutils info:   " $(cBINUTILS_INFO)
						@echo "*"
						@echo "* Program name:    " $(PROGRAM_NAME)	" ("$(BINARY_DIR)")"
						@echo "* Bin type:        " $(BIN_TYPE)						
						@echo "* Build type:      " $(BUILD_TYPE)
						@echo "*"
						@echo "************************************************************"
						@echo ""

						@echo "[Prepare ...]"
						mkdir -p $(BINARY_DIR)
						@echo ""

						@echo "[Build ...]"
						$(MAKE) --directory=./$(BINARY_DIR) --makefile=../../../makefile
						@echo ""
						
						@echo "[Finish ...]"
						@echo ""
						
install:				
						@echo "[Install ...]"
						mkdir -p $(INSTALL_DIR)
						cp ./$(BINARY_DIR)/$(PROGRAM_NAME) $(INSTALL_DIR)
						@echo ""						

clean:
						@echo "[Clean ...]"
						rm -rf $(BINARY_DIR)
						
						@echo "[Finish ...]"
						@echo ""

include $(wildcard $(addsuffix /*.d, $(OBJECTS_DIRS)))


# gcc -dumpversion
# gcc -dumpmachine

# OS   := $(shell uname -s)
# ARCH := $(shell uname -m)
# KERN := $(shell uname -r | cut -d. -f 1,2)
# BDIR := $(OS)_$(KERN).$(ARCH)
