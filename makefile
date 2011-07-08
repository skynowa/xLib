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
cBIN_TYPE_TEST			:= test	#TODO: not implemented


##################################################
# Settings
BUILD_TYPE				:= $(cBUILD_TYPE_RELEASE)
BIN_TYPE                := $(cBIN_TYPE_LIB)


##################################################
# xLib
PROGRAM_NAME			:= libxlib.a

ROOT_INCLUDE_DIR		:= Include Source
ROOT_SOURCE_DIR			:= Source

OTHER_INCLUDE_DIR		:=	/usr/include \
							/usr/local/include \
							/usr/local/crystal_trader2.5/include

SOURCE_SUBDIRS			:=	.\
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
							Common \

BINARY_DIR				:= Library/G++_linux/Release
INSTALL_DIR				:= /usr/local/crystal_trader2.5/lib/xLib
PROGRAM_PATH			:= ../../../$(BINARY_DIR)/$(PROGRAM_NAME)

COMPILER				:= g++
ARCHIVER                := ar
COMPILE_FLAGS      		:= -Wall -MD -pipe
LINK_FLAGS              := -s -pipe
LIBRARIES               := -ldl -lmysqlclient -lm -lpthread -lcrypt -lz -lssl -lGeoIP

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
						$(COMPILER) -o $@ $(OBJECTS) $(LINK_FLAGS) $(LIBRARIES)		
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
						@echo "* Program name:    " $(PROGRAM_NAME)							
						@echo "* Bin type:        " $(cBIN_TYPE_LIB)						
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
						
						@echo "[Install ...]"
						mkdir -p $(INSTALL_DIR)
						cp ./$(BINARY_DIR)/$(PROGRAM_NAME) $(INSTALL_DIR)
						@echo ""

						@echo "[Finish ...]"
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
