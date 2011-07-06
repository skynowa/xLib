######################################################################################################
# Class name:  
# Description: make file (Linux, release)
# File name:   makefile
# Author:      skynowa
# E-mail:      skynowa@gmail.com
# Created:     30.06.2011
#
######################################################################################################


##################################################
# constants
cOS				:= $(shell uname -s)
cOS_BIT				:= $(shell getconf LONG_BIT)
cOS_ARCH 			:= $(shell uname -m)
cOS_INFO 			:= $(shell uname -a)
cGCC_INFO			:= $(shell gcc -dumpversion)
cGLIBC_INFO			:= $(shell ldd --version)
cBINUTILS_INFO			:= n/a

cBUILD_TYPE_DEBUG		:= debug
cBUILD_TYPE_RELEASE		:= release


# OS   := $(shell uname -s)
# ARCH := $(shell uname -m)
# KERN := $(shell uname -r | cut -d. -f 1,2)
# BDIR := $(OS)_$(KERN).$(ARCH)

OS   := $(shell uname -s)
ARCH := $(shell uname -m)
KERN := $(shell uname -r | cut -d. -f 1,2)
BDIR := $(OS)_$(KERN).$(ARCH)


##################################################
# Settings
BUILD_TYPE			:= $(cBUILD_TYPE_RELEASE)


##################################################
# xLib
PROGRAM_NAME			:= xLib.a

ROOT_INCLUDE_DIR		:= Include Source
ROOT_SOURCE_DIR			:= Source

ifeq ($(cOS), Linux)
	OTHER_INCLUDE_DIR	:=	/usr/include \
					/usr/local/include \
					/usr/local/crystal_trader2.5/include
else ifeq ($(cOS), FreeBSD)
	OTHER_INCLUDE_DIR	:=	/usr/include \
					/usr/local/include \
					/usr/local/crystal_trader/include
else
	OTHER_INCLUDE_DIR	:=
endif

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

BINARY_DIR			:= Library/G++_linux/Release
INSTALL_DIR			:= .
PROGRAM_PATH			:= ../../../$(BINARY_DIR)/$(PROGRAM_NAME)

COMPILER			:= g++
COMPILE_FLAGS      		:= -Wall -MD -pipe

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
	BUILD_FLAGS     	:= -O3 -fomit-frame-pointer -pthread -g0 -s -g
else
	BUILD_FLAGS     	:= -O3 -fomit-frame-pointer -pthread -g0 -s
endif


RELATIVE_INCLUDE_DIRS		:= $(addprefix ../../../, $(ROOT_INCLUDE_DIR))
RELATIVE_SOURCE_DIRS		:= $(addprefix ../../../$(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS_DIRS			:= $(addprefix $(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS				:= $(patsubst ../../../%, %, $(wildcard $(addsuffix /*.c*, $(RELATIVE_SOURCE_DIRS))))
OBJECTS				:= $(OBJECTS:.cpp=.o)
OBJECTS				:= $(OBJECTS:.c=.o)


$(PROGRAM_PATH):		obj_dirs $(OBJECTS)
				ar rcs $@ $(OBJECTS)

obj_dirs:	        
				mkdir -p $(OBJECTS_DIRS)

VPATH				:= ../../../

%.o: 				%.cpp
				$(COMPILER) -o $@ -c $< $(COMPILE_FLAGS) $(BUILD_FLAGS) $(addprefix -I, $(RELATIVE_INCLUDE_DIRS) $(OTHER_INCLUDE_DIR))

%.o: 				%.c
				$(COMPILER) -o $@ -c $< $(COMPILE_FLAGS) $(BUILD_FLAGS) $(addprefix -I, $(RELATIVE_INCLUDE_DIRS) $(OTHER_INCLUDE_DIR))

.PHONY:				clean


all:
				clear
				@echo ""
				@echo "************************************************************"
				@echo "* OS info:       " $(cOS_INFO)
				@echo "* GCC info:      " $(cGCC_INFO)
				@echo "* GLIBC info:    " #$(cGLIBC_INFO)
				@echo "* Binutils info: " $(cBINUTILS_INFO)
				@echo "* Build type:    " $(BUILD_TYPE)
				@echo "*"
				@echo "************************************************************"
            
				@echo ""
				@echo "[Prepare ...]"
				mkdir -p $(BINARY_DIR)
            
				@echo ""
				@echo "[Build ...]"
				$(MAKE) --directory=./$(BINARY_DIR) --makefile=../../../makefile

install:
				@echo ""
				@echo "[Install ...]"
				cp ./$(BINARY_DIR)/$(PROGRAM_NAME) $(INSTALL_DIR)/$(PROGRAM_NAME)

clean:
				@echo ""
				@echo "[Clean ...]"
				rm -rf $(BINARY_DIR)


include $(wildcard $(addsuffix /*.d, $(OBJECTS_DIRS)))


# gcc -dumpversion
# gcc -dumpmachine

# OS   := $(shell uname -s)
# ARCH := $(shell uname -m)
# KERN := $(shell uname -r | cut -d. -f 1,2)
# BDIR := $(OS)_$(KERN).$(ARCH)
