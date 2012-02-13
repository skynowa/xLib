######################################################################################################
# Class name:
# Description: make file (static library, Linux, release)
# File name:   Lib.mk
# Author:      skynowa
# E-mail:      skynowa@gmail.com
# Created:     30.06.2011
#
######################################################################################################


##################################################
# constants
cOS						:=	$(shell uname -s)
cOS_BIT					:=	$(shell getconf LONG_BIT)
cOS_ARCH 				:=	$(shell gcc -dumpmachine)	#$(shell uname -m)
cOS_INFO 				:=	$(shell uname -a)
cGCC_INFO				:=	$(shell gcc -dumpversion)
cGLIBC_INFO				:=	##$(shell ldd --version)	#TODO: not implemented
cBINUTILS_INFO			:=	n/a

cBUILD_TYPE_DEBUG		:=	debug
cBUILD_TYPE_RELEASE		:=	release

cBIN_TYPE_LIB			:=	static library
cBIN_TYPE_TESTS			:=	tests

cDESCRIPTION 			:=	C++ class library


##################################################
# Settings
BUILD_TYPE				:=	$(cBUILD_TYPE_RELEASE)
BIN_TYPE				:=	$(cBIN_TYPE_LIB)


##################################################
# xLib
ifeq ($(BIN_TYPE), $(cBIN_TYPE_LIB))
PROGRAM_PREFIX			:=	lib
PROGRAM_EXT  			:=	.a
else
PROGRAM_PREFIX			:=
PROGRAM_EXT  			:=
endif

PROGRAM_NAME			:=	$(PROGRAM_PREFIX)xlib$(PROGRAM_EXT)

ROOT_INCLUDE_DIR		:=	./Include
ROOT_SOURCE_DIR			:=	./Source

OTHER_INCLUDE_DIR		:=	/usr/include \
							/usr/local/include

SOURCE_SUBDIRS			:=	 . \
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

LIB_DIRS				:=	/usr/lib64 \
                    		/usr/lib \
                    		/usr/lib64/mysql \
                    		/usr/lib/mysql \
                    		/usr/local/lib64 \
							/usr/local/lib \
							/usr/local/lib64/mysql \
							/usr/local/lib/mysql							

BINARY_DIR				:=	./Library/G++_linux/Release
INSTALL_INCLUDE_DIR		:=	/usr/local/include/xLib
INSTALL_DIR				:=	/usr/local/lib/xLib
PROGRAM_PATH			:=	../../../$(BINARY_DIR)/$(PROGRAM_NAME)

COMPILER				:=	$(CXX)
ARCHIVER				:=	$(AR)
COMPILE_FLAGS			:=	-Wall -pipe
LINK_FLAGS				:=	-pthread -s -pipe

ifeq ($(BUILD_TYPE), $(cBUILD_TYPE_DEBUG))
BUILD_FLAGS				:=	-O0 -g3 -g
else
BUILD_FLAGS				:=	-O3 -g0
endif

PARANOID_FLAGS			:=	-pedantic -Wall -Wextra -Wformat=2 -Winit-self -Wmissing-include-dirs -Wswitch-default \
							-Wswitch-enum -Wsync-nand -Wstrict-overflow=1 -Wstrict-overflow=2 -Wstrict-overflow=3 \
							-Wstrict-overflow=4 -Wstrict-overflow=5 -Wfloat-equal -Wtraditional -Wtraditional-conversion \
							-Wdeclaration-after-statement -Wundef -Wshadow -Wunsafe-loop-optimizations -Wtype-limits \
							-Wbad-function-cast -Wc++-compat -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion \
							-Wlogical-op -Waggregate-return -Wstrict-prototypes -Wold-style-declaration \
							-Wold-style-definition -Wmissing-prototypes  -Wmissing-declarations \
							-Wmissing-field-initializers -Wmissing-format-attribute -Wpacked -Wpadded \
							-Wredundant-decls -Wnested-externs -Winline -Winvalid-pch -Wvariadic-macros -Wvla \
							-Wvolatile-register-var -Wdisabled-optimization -Wpointer-sign -Wstack-protector

RELATIVE_INCLUDE_DIRS	:=	$(addprefix ../../../, $(ROOT_INCLUDE_DIR))
RELATIVE_SOURCE_DIRS	:=	$(addprefix ../../../$(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS_DIRS			:=	$(addprefix $(ROOT_SOURCE_DIR)/, $(SOURCE_SUBDIRS))
OBJECTS					:=	$(patsubst ../../../%, %, $(wildcard $(addsuffix /*.c*, $(RELATIVE_SOURCE_DIRS))))
OBJECTS					:=	$(OBJECTS:.cpp=.o)
OBJECTS					:=	$(OBJECTS:.c=.o)



$(PROGRAM_PATH):		obj_dirs $(OBJECTS)
						$(ARCHIVER) rc $@ $(OBJECTS)

obj_dirs:
						mkdir -p $(OBJECTS_DIRS)

VPATH					:= ../../../

%.o:					%.cpp
						$(COMPILER) $(COMPILE_FLAGS) $(BUILD_FLAGS) -c $(addprefix -I, $(RELATIVE_INCLUDE_DIRS) $(OTHER_INCLUDE_DIR)) -o $@ $<

.PHONY:					clean

all:
#						clear

#						@echo "************************************************************"
#						@echo "* OS info:         " $(cOS_INFO)
#						@echo "* OS architecture: " $(cOS_BIT)
#						@echo "* GCC info:        " $(cGCC_INFO)
#						@echo "* GLIBC info:      " #$(cGLIBC_INFO)
#						@echo "* Binutils info:   " $(cBINUTILS_INFO)
#						@echo "*"
#						@echo "* Program name:    " $(PROGRAM_NAME)	" ("$(BINARY_DIR)")"
#						@echo "* Bin type:        " $(BIN_TYPE)
#						@echo "* Build type:      " $(BUILD_TYPE)
#						@echo "*"
#						@echo "************************************************************"
#						@echo ""

#						@echo "[Prepare ...]"
						mkdir -p $(BINARY_DIR)
#						@echo ""

#						@echo "[Build ...]"
						$(MAKE) --directory=./$(BINARY_DIR) --makefile=../../../Lib.mk
#						@echo ""

#						@echo "[Finish ...]"
#						@echo ""

install:
#						@echo "[Install ...]"
						mkdir -p $(INSTALL_DIR)
						cp    ./$(BINARY_DIR)/$(PROGRAM_NAME) $(INSTALL_DIR)

						mkdir -p $(INSTALL_INCLUDE_DIR)
						cp -r ./$(ROOT_INCLUDE_DIR) $(INSTALL_INCLUDE_DIR)
#						@echo ""

clean:
#						@echo "[Clean ...]"
						rm -rf $(BINARY_DIR)

#						@echo "[Finish ...]"
#						@echo ""

include $(wildcard $(addsuffix /*.d, $(OBJECTS_DIRS)))


# gcc -dumpversion
# gcc -dumpmachine

# OS   := $(shell uname -s)
# ARCH := $(shell uname -m)
# KERN := $(shell uname -r | cut -d. -f 1,2)
# BDIR := $(OS)_$(KERN).$(ARCH)
