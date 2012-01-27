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
# Constants
cOS							:=	$(shell uname -s)
cOS_BIT						:=	$(shell getconf LONG_BIT)
cOS_ARCH 					:=	$(shell gcc -dumpmachine) #$(shell uname -m)
cOS_INFO 					:=	$(shell uname -a)
cGCC_INFO					:=	$(shell gcc -dumpversion)
cGLIBC_INFO					:=	n/a	##$(shell ldd --version)	#TODO: not implemented
cBINUTILS_INFO				:=	n/a

cBUILD_TYPE_DEBUG			:=	debug
cBUILD_TYPE_RELEASE			:=	release

cBIN_TYPE_LIB				:=	static library
cBIN_TYPE_TESTS				:=	tests

cDESCRIPTION 				:=	tests for xLib \(C++ class library\)

cCOMPILER					:=	$(CXX)
cARCHIVER					:=	$(AR)


##################################################
# Settings
#BUILD_TYPE					:=	$(cBUILD_TYPE_DEBUG)
BUILD_TYPE					:=	$(cBUILD_TYPE_RELEASE)


##################################################
# xLib
PROGRAM_PREFIX				:=
PROGRAM_SHORT_NAME	    	:=	xlib

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
PROGRAM_POSTFIX				:=	_d
else
PROGRAM_POSTFIX				:=	_r
endif

PROGRAM_EXT  				:=
PROGRAM_NAME				:=	$(PROGRAM_PREFIX)$(PROGRAM_SHORT_NAME)$(PROGRAM_POSTFIX)$(PROGRAM_EXT)
PROGRAM_PATH				:=	$(PROGRAM_NAME)
PROGRAM_SIZE				:=	$(stat --printf="%s" $(PROGRAM_NAME))

PATH_PREFIX					:=	../../../
VPATH 						:=	$(PATH_PREFIX)

ROOT_INCLUDE_DIR			:=	Include Source
ROOT_SOURCE_DIR				:=	Source
TESTS_ROOT_INCLUDE_DIR		:=	Tests/Include
TESTS_ROOT_SOURCE_DIR		:=	Tests/Source

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
BINARY_DIR					:=	./Contrib/G++_linux/Debug
else
BINARY_DIR					:=	./Contrib/G++_linux/Release
endif

INSTALL_DIR					:=	/usr/local/lib/xLib

SOURCE_SUBDIRS				:= 	. \
								Common \
								Common/Win \
								Crypt \
								Crypt/OpenSSL \
								Crypt/Pkcs11/Win \
								Db \
								Debug \
								Filesystem \
								Filesystem/Win \
								Gui \
								Gui/Dialogs \
								Gui/Win \
								Gui/Win/Dialogs \
								Gui/Win/GDI+ \
								Log \
								Net \
								Patterns \
								Sync \
								Sync/Win \
								Units \
								Units/Win

TESTS_SOURCE_SUBDIRS		:= 	. \
								Common \
								Common/Win \
								Crypt \
								Crypt/Pkcs11/Win \
								Db \
								Debug \
								Filesystem \
								Filesystem/Win \
								Gui \
								Gui/Dialogs \
								Gui/Win \
								Gui/Win/Dialogs \
								Gui/Win/GDI+ \
								Log \
								Net \
								Patterns \
								Sync/Win \
								Units \
								Units/Win

OTHER_INCLUDE_DIR			:=	/usr/local/include \
                    			/usr/include

LIB_DIRS					:=	/usr/local/lib \
                    			/usr/lib \
                    			/usr/local/lib/mysql \
                    			/usr/lib/mysql

COMPILE_FLAGS				:=	-Wall -pipe
LINK_FLAGS					:=	-pthread -s -pipe -rdynamic	#-static

ifeq ($(cOS), Linux)
LIBRARIES               	:=	-ldl -lmysqlclient -lm -lcrypto -lz -lssl
else
LIBRARIES               	:=	-lmysqlclient -lm -lcrypto -lz -lssl	# -lc only with out -static
endif

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
BUILD_FLAGS     			:=	-O0 -g3 -g
else
BUILD_FLAGS     			:=	-O3 -g0 -fomit-frame-pointer
endif

RELATIVE_INCLUDE_DIRS		:=	$(addprefix $(PATH_PREFIX), $(ROOT_INCLUDE_DIR))
RELATIVE_SOURCE_DIRS		:=	$(addprefix $(PATH_PREFIX)$(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS_DIRS				:=	$(addprefix $(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS						:=	$(patsubst $(PATH_PREFIX)%, %, $(wildcard $(addsuffix /*.c*, $(RELATIVE_SOURCE_DIRS))))
OBJECTS						:=	$(OBJECTS:.cpp=.o)
OBJECTS						:=	$(OBJECTS:.c=.o)

TESTS_RELATIVE_INCLUDE_DIRS	:=	$(addprefix $(PATH_PREFIX), $(TESTS_ROOT_INCLUDE_DIR))
TESTS_RELATIVE_SOURCE_DIRS	:=	$(addprefix $(PATH_PREFIX)$(TESTS_ROOT_SOURCE_DIR)/, $(TESTS_SOURCE_SUBDIRS))
TESTS_OBJECTS_DIRS			:=	$(addprefix $(TESTS_ROOT_SOURCE_DIR)/, $(TESTS_SOURCE_SUBDIRS))
TESTS_OBJECTS				:=	$(patsubst $(PATH_PREFIX)%, %, $(wildcard $(addsuffix /*.c*, $(TESTS_RELATIVE_SOURCE_DIRS))))
TESTS_OBJECTS				:=	$(TESTS_OBJECTS:.cpp=.o)
TESTS_OBJECTS				:=	$(TESTS_OBJECTS:.c=.o)



all: 							$(PROGRAM_PATH)

$(PROGRAM_PATH): 				OBJ_DIRS $(OBJECTS) $(TESTS_OBJECTS) $(RELATIVE_INCLUDE_DIRS)
								$(cCOMPILER) $(OBJECTS) $(TESTS_OBJECTS) $(addprefix -L, $(LIB_DIRS)) $(LINK_FLAGS) $(LIBRARIES) -o $@

OBJ_DIRS:
#								clear
#
#								@echo "************************************************************"
#								@echo "* Description:     " $(cDESCRIPTION)
#								@echo "*"
#								@echo "* OS info:         " $(cOS_INFO)
#								@echo "* OS architecture: " $(cOS_BIT)
#								@echo "* GCC info:        " $(cGCC_INFO)
#								@echo "* GLIBC info:      " $(cGLIBC_INFO)
#								@echo "* Binutils info:   " $(cBINUTILS_INFO)
#								@echo "*"
#								@echo "* Program name:    " $(PROGRAM_NAME)	" ("$(BINARY_DIR)")"
#								@echo "* File size:       " $(PROGRAM_SIZE)
#								@echo "* Build type:      " $(BUILD_TYPE)
#								@echo "*"
#								@echo "************************************************************"
#								@echo ""

								mkdir -p $(OBJECTS_DIRS) $(TESTS_OBJECTS_DIRS)

#%.o:							%.h
#								$(cCOMPILER) -c -o $@ $< $(COMPILE_FLAGS) $(BUILD_FLAGS) $(addprefix -I, $(RELATIVE_INCLUDE_DIRS) $(TESTS_RELATIVE_INCLUDE_DIRS) $(OTHER_INCLUDE_DIR))

%.o:							%.cpp
								$(cCOMPILER) $(COMPILE_FLAGS) $(BUILD_FLAGS) -c $(addprefix -I, $(RELATIVE_INCLUDE_DIRS) $(TESTS_RELATIVE_INCLUDE_DIRS) $(OTHER_INCLUDE_DIR)) -o $@ $<

.PHONY: 						clean

install:
#								@echo "[Install ...]"
								mkdir -p $(INSTALL_DIR)
								cp $(BINARY_DIR)/$(PROGRAM_PREFIX)$(PROGRAM_SHORT_NAME)$(PROGRAM_EXT) $(INSTALL_DIR)
#								@echo ""

clean:
								rm -rf $(BINARY_DIR)

help:
								#TODO: help

include $(wildcard $(addsuffix /*.d, $(OBJECTS_DIRS)))
include $(wildcard $(addsuffix /*.d, $(TESTS_OBJECTS_DIRS)))
